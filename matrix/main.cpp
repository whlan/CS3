#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>


using namespace std;

struct mixedNumber
{
    int whole, num, denom;

    void output(ostream &out = cout);
    mixedNumber operator=(const mixedNumber& other);
};


mixedNumber mixedNumber::operator=(const mixedNumber& other)
{
    whole = other.whole;
    num = other.num;
    denom = other.denom;
}

void mixedNumber::output(ostream &out)
{
    if(whole == 0)
        if(num == 0)
            out<<0;
        else
            out<<num<<"/"<<denom;
   else
        if(num == 0)
            out<<whole;
        else
            out<<whole<<" "<<num<<"/"<<denom;
}

int gcd(int p, int q);
void reduce(mixedNumber &number);
mixedNumber add(mixedNumber x, mixedNumber y);
mixedNumber mult(mixedNumber x, mixedNumber y);
mixedNumber convertToMixedNumber(string line);
void trim(string &line);
void output(ostream &out, string line, mixedNumber answer);
void parseCommandLine(int argc, char* argv[], ifstream &in, ofstream &out);
mixedNumber** getMatrix(char* filename, ifstream &in,ofstream &out, int row, int col);
void getDimension(char* filename, int &row, int &col, ifstream &in);
mixedNumber** Operator(char* op,mixedNumber** one, mixedNumber** two, int row1, int col1, int row2, int col2, int &row, int &col);
void deleteMatrix(mixedNumber** mat, int row);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ifstream in;
    ofstream out;
    parseCommandLine(argc, argv, in, out);
    exit(0);
    return a.exec();
}

void output(ostream &out, string line, mixedNumber answer)
{
    out<<line<<" = ";
    answer.output(out);
    out<<endl;
}

void trim(string &line)
{
    while(line[0] == ' ')
        line.erase(0,1);
}

mixedNumber convertToMixedNumber(string line)
{
    stringstream ss;
    char junk;
    mixedNumber answer;
    trim(line);
    int pos = line.find(' '),
        pos2 = line.find('/');
    if(pos < string::npos && pos2 < string::npos) //have a true mixed number!
    {
        ss << line;
        ss>> answer.whole>>answer.num>>junk>>answer.denom;
    }
    else
        if(pos2 >= string::npos)
        {
            ss<<line;
            ss>>answer.whole;
            answer.num = 0;
            answer.denom = 1;
        }
        else
        {
            ss<<line;
            ss>>answer.num>>junk>>answer.denom;
            answer.whole = 0;
        }
    return answer;
}

int gcd(int p, int q)
{
    return q==0 ? p : gcd(q, p%q);
}

void reduce(mixedNumber &number)
{
    int newNum = number.denom*number.whole + number.num,
        newDenom = number.denom,
        divisor = gcd(newNum,newDenom );
    newNum /= divisor;
    newDenom /= divisor;
    number.whole = newNum/newDenom;
    number.num = newNum %newDenom;
    number.denom = newDenom;
}

mixedNumber add(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;

    answer.whole = 0;
    if(x.whole < 0 && y.whole < 0)
    answer.num = y.denom*(x.denom*x.whole - x.num) +  x.denom*(y.denom*y.whole - y.num);
    else if(x.whole < 0)
    answer.num = y.denom*(x.denom*x.whole - x.num) +  x.denom*(y.denom*y.whole + y.num);
    else if(y.whole < 0)
    answer.num = y.denom*(x.denom*x.whole + x.num) +  x.denom*(y.denom*y.whole - y.num);
    else
    answer.num = y.denom*(x.denom*x.whole + x.num) +  x.denom*(y.denom*y.whole + y.num);

    answer.denom = x.denom * y.denom;
    reduce(answer);
    if(answer.whole < 0 )
    {
        answer.num = abs(answer.num);
        answer.denom = abs(answer.denom);
    }
    else if(answer.denom < 0 )
    {
        answer.num = -(answer.num);
        answer.denom = abs(answer.denom);
    }
    return answer;
}

mixedNumber mult(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    answer.whole = 0;
    if(x.whole < 0 && y.whole < 0)
    answer.num = (x.denom*x.whole - x.num) * (y.denom*y.whole - y.num);
    else if(x.whole < 0)
    answer.num = (x.denom*x.whole - x.num) * (y.denom*y.whole + y.num);
    else if(y.whole < 0)
    answer.num = (x.denom*x.whole + x.num) * (y.denom*y.whole - y.num);
    else
    answer.num = (x.denom*x.whole + x.num) * (y.denom*y.whole + y.num);

    answer.denom = x.denom * y.denom;
    reduce(answer);

    if(answer.whole < 0 )
        {
            answer.num = abs(answer.num);
            answer.denom = abs(answer.denom);
        }
    else if(answer.denom < 0 )
    {
        answer.num = -(answer.num);
        answer.denom = abs(answer.denom);
    }
    return answer;
}

void parseCommandLine(int argc, char* argv[], ifstream &in, ofstream &out)
{
    int row1, row2, col1, col2, row, col, desired_row, desired_col;
    char ans;
    string value;
    char comma;
    mixedNumber** one;
    mixedNumber** two;
    mixedNumber** result;

    switch(argc)
    {
        case 2:
            getDimension(argv[1], row, col, in);

            in.open(argv[1]);
            if(in.fail())
            {

              cout<<"File does not exist and new file created"<<endl;
              out.open(argv[1]);
              exit(1);
            }
            else
            {
                in.close();
               do
               {
                one = getMatrix(argv[1],in,out, row, col);
                for(int i = 0; i < row; i++)
                {
                    for(int j=0; j < col; j++)
                    {
                        cout<<"\t";
                        (*(*(one + i) + j)).output();

                    }
                    cout<<endl<<endl;
                }
                    cout<<"Enter row and column to edit the matrix (ex. row,col): ";
                    cin>>desired_row >> comma >> desired_col;
                    cin.ignore();
                    cout<<"Enter desired value: ";
                    getline(cin,value);
                    (*(*(one + desired_row) + desired_col)) = convertToMixedNumber(value);
                    reduce((*(*(one + desired_row) + desired_col)));
                    out.open(argv[1]);
                    out<<row<<"X"<<col<<"\n";
                    for(int i = 0; i < row; i++)
                    {
                        for(int j=0; j < col; j++)
                        {

                            if(j == col-1)
                            {
                               (*(*(one + i) + j)).output(out);
                            }
                            else
                            {
                                (*(*(one + i) + j)).output(out);
                                out<<",";
                            }
                        }
                        out<<"\n";
                    }
                    out.close();
                    cout<<"continue to edit?(y/n):";
                    cin>>ans;
                }while(ans == 'y' || ans == 'Y' );
            }
        break;
        case 3:
          cout<<"Useage: matrix [filename] [operator(add/multiply)] [filename]"<<endl;
        break;
        case 4:
             if(stricmp(argv[2],"add") == 0 ||stricmp(argv[2],"multiply") == 0 )
             {
                    getDimension(argv[1], row1, col1, in);
                    getDimension(argv[3], row2, col2, in);
                    one = getMatrix(argv[1],in,out, row1, col1);
                    two = getMatrix(argv[3],in,out, row2, col2);
                    result = Operator(argv[2], one, two, row1, col1, row2, col2, row, col);
                    for(int i = 0; i < row; i++)
                    {
                        for(int j=0; j < col; j++)
                        {
                            (*(*(result + i) + j)).output();
                            cout<<" ";
                        }
                        cout<<endl;
                    }
                    deleteMatrix(one, row1);
                    deleteMatrix(two, row2);
                    deleteMatrix(result, row);
             }
             else
             {
                 cout<<"Useage: matrix [filename] [operator(add/multiply)] [filename]"<<endl;
             }
        break;

        case 5:
        if(stricmp(argv[2],"add") == 0 ||stricmp(argv[2],"multiply") == 0 )
        {
            getDimension(argv[1], row1, col1, in);
            getDimension(argv[3], row2, col2, in);
            one = getMatrix(argv[1],in,out, row1, col1);
            two = getMatrix(argv[3],in,out, row2, col2);
            result = Operator(argv[2], one, two, row1, col1, row2, col2, row, col);
            for(int i = 0; i < row; i++)
            {
                for(int j=0; j < col; j++)
                {
                    (*(*(result + i) + j)).output();
                    cout<<" ";
                }
                cout<<endl;
            }

            in.open(strcat(argv[4],".mat"));
                if(in.fail())
                {
                  in.close();
                  cout<<"file does not exist and new file created"<<endl;
                  out.open(argv[4]);
                  exit(1);
                }
                else
                {
                    in.close();
                    char choice;
                    cout<<"You want to create a new file(n) or overwrite(e)"<<endl;
                    cin>>choice;
                    if(choice == 'n')
                    {
                        string newFile;
                        cout<<"Enter new file name: ";
                        cin>>newFile;
                        newFile.append(".mat");
                        out.open(newFile.c_str());
                        out<<row<<"X"<<col<<"\n";
                        for(int i = 0; i < row; i++)
                        {
                            for(int j=0; j < col; j++)
                            {

                                if(j == col-1)
                                {
                                   (*(*(result + i) + j)).output(out);
                                }
                                else
                                {
                                    (*(*(result + i) + j)).output(out);
                                    out<<",";
                                }
                            }
                            out<<"\n";
                        }

                        out.close();
                    }
                    else if(choice == 'e')
                    {
                        cout<<"overwriting......."<<endl;
                        out.open(argv[4]);
                        out<<row<<"X"<<col<<"\n";
                        for(int i = 0; i < row; i++)
                        {
                            for(int j=0; j < col; j++)
                            {

                                if(j == col-1)
                                {
                                   (*(*(result + i) + j)).output(out);
                                }
                                else
                                {
                                    (*(*(result + i) + j)).output(out);
                                    out<<",";
                                }
                            }
                            out<<"\n";
                        }
                        out.close();
                        cout<<"FINISH."<<endl;
                    }
                }
        }
        else
        {
         cout<<"Useage: matrix [filename] [operator(add/multiply)] [filename] [filename]"<<endl;
        }
        break;

        case 6:

              if(stricmp(argv[5],"/f") == 0)
              {
                  getDimension(argv[1], row1, col1, in);
                  getDimension(argv[3], row2, col2, in);
                  one = getMatrix(argv[1],in,out, row1, col1);
                  two = getMatrix(argv[3],in,out, row2, col2);
                  result = Operator(argv[2], one, two, row1, col1, row2, col2, row, col);
                  in.open(strcat(argv[4],".mat"));
                  out.open(argv[4]);

                  for(int i = 0; i < row; i++)
                  {
                      for(int j=0; j < col; j++)
                      {
                          (*(*(result + i) + j)).output();
                          cout<<" ";
                      }
                      cout<<endl;
                  }

                  out<<row<<"X"<<col<<"\n";
                  for(int i = 0; i < row; i++)
                  {
                      for(int j=0; j < col; j++)
                      {

                          if(j == col-1)
                          {
                             (*(*(result + i) + j)).output(out);
                          }
                          else
                          {
                              (*(*(result + i) + j)).output(out);
                              out<<",";
                          }
                      }
                      out<<"\n";
                  }
                  out.close();
              }
              else
              {
                  cout<<"Useage: matrix [filename] [operator] [filename] [filename] [/f]"<<endl;
              }
              break;
    }

}

mixedNumber** getMatrix(char* filename, ifstream &in,ofstream &out, int rows, int cols)
{

    in.open(filename);
    //cout<<"this is filename: "<<filename;
    if(in.fail())
    {
        in.close();
      cout<<"Output file does not exist and new file created"<<endl;
      out.open(filename);
      exit(1);
    }
    else
    {
        string line, token;
        stringstream iss;
        int row = 0, col = 0;
        mixedNumber** mat;
        mat = new mixedNumber* [rows];
        for(int i = 0; i < rows; i++)
          mat[i] = new mixedNumber [cols];
        getline(in,line);
        while(getline(in, line))
        {

            iss << line;
            while(getline(iss, token, ','))
            {
               (*(*(mat + row) + col)) = convertToMixedNumber(token);
               reduce((*(*(mat + row) + col)));
               //(*(*(mat + row) + col)).output();
                col++;
            }
            col = 0;
            row++;
            iss.clear();
        }
        in.close();
        return mat;


    }
}

void getDimension(char* filename, int &row, int &col, ifstream &in)
{
    string line, token;
    stringstream iss;

        in.open(strcat(filename,".mat"));
        getline(in,line);
        iss << line;
        getline(iss, token, 'X');;
        row = atoi(token.c_str());
        getline(iss, token);
        col = atoi(token.c_str());
        in.close();
}

mixedNumber** Operator(char* op, mixedNumber** one, mixedNumber** two, int row1, int col1, int row2, int col2, int &row, int &col)
{


    if(stricmp(op,"add") == 0)
        {
            if(row1 == row2 && col1 == col2)
            {
                mixedNumber** result;
                result = new mixedNumber* [row1];
                for(int i = 0; i < row1; i++)
                  result[i] = new mixedNumber [col1];

                for(int i = 0; i < row1; i++)
                    for(int j=0; j < col1; j++)
                        (*(*(result + i) + j)) = add((*(*(one + i) + j)),(*(*(two + i) + j)));

                    row = row1;
                    col = col1;
               return result;
            }
        }
    else if(stricmp(op,"multiply") == 0)
    {

        if(col1 == row2)
            {
                cout<<"Multiplying"<<endl<<endl<<endl;
                mixedNumber** result;
                result = new mixedNumber* [row1];
                for(int i = 0; i < row1; i++)
                  result[i] = new mixedNumber [col2];

                mixedNumber product;

                for(int i=0;i<row1;i++)
                {
                    for(int j=0;j<col1;j++)
                    {
                        (*(*(result + i) + j)) = convertToMixedNumber("0");
                        for(int k=0;k<row2;k++)
                        {
                             product =mult((*(*(one + i) + k)),(*(*(two + k) + j)));
                             (*(*(result + i) + j)) = add((*(*(result + i) + j)), product);
                        }
                    }
                }

                    row = row1;
                    col = col2;
                return result;
            }
    }

}

void deleteMatrix(mixedNumber** mat, int row)
{
    for(int i = 0; i < row; i++)
    {
        delete [] mat[i];
        mat[i] = NULL;
    }
    delete [] mat;
    mat = NULL;
}

