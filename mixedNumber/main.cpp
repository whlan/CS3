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
    if(out == cout)
        out<<"       ";
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

bool input(string &line);
bool process(string line, mixedNumber &answer);
int gcd(int p, int q);
void reduce(mixedNumber &number);
mixedNumber add(mixedNumber x, mixedNumber y);
mixedNumber mult(mixedNumber x, mixedNumber y);
mixedNumber divide(mixedNumber x, mixedNumber y);
mixedNumber subtract(mixedNumber x, mixedNumber y);
char getOperator(string line, int &pos);
void getOperands(const string &line, mixedNumber &x, mixedNumber &y, int pos);
mixedNumber convertToMixedNumber(string line);
void trim(string &line);
void output(ostream &out, string line, mixedNumber answer);
void parseCommandLine(int argc, char* argv[], ifstream &in, ofstream &out);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string line;
    mixedNumber answer;
    ifstream in;
    ofstream out;
    parseCommandLine(argc, argv, in, out);
    out.open("junk.dat");
    input(line);
    cout<<line[0];
    exit(0);
    while(input(line))
       if(process(line, answer))
       {
         output(cout,line,answer);
         output(out,line,answer);
       }
    out.close();
    return a.exec();
}

void output(ostream &out, string line, mixedNumber answer)
{
    out<<line<<" = ";
    answer.output(out);
    out<<endl;
}

bool input(string &line)
{
    cout<<"Input: ";
    getline(cin,line);
    return line != "";
    /*
      The above is identical, in result, to:

      if(line != "")
        return true;
      else
        return false;

      which is also the same result of:

      return line != "" ? true : false;
    */
}

void getOperands(const string &line, mixedNumber &x, mixedNumber &y, int pos)
{
    string first, second;
    first = line.substr(0, pos);
    second = line.substr(pos+3);
    x = convertToMixedNumber(first);
    y = convertToMixedNumber(second);
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


char getOperator(string line, int &pos)
{
    string choices[4] = {" + ", " - ", " * ", " / "};
    for(int i = 0; i < 4; i++)
        if( (pos = line.find(choices[i])) < string::npos)
            break;
    return pos < string::npos ? line[pos+1] : '\0';
}


bool process(string line, mixedNumber &answer)
{
    mixedNumber one, two;
    int pos;
    char op = getOperator(line, pos);
    if(op == '\0')
    {
        cout<<"No operator found! Please re-etner"<<endl;
        return false;
    }
    getOperands(line, one, two, pos);
    switch(op)
    {
        case '+' : answer = add(one, two);
                   break;

        case '-' : answer = subtract(one,two);
                   break;

        case '*' : answer = mult(one,two);
                   break;

        case '/' : answer = divide(one,two);
    }
    return true;
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
    answer.num = y.denom*(x.denom*x.whole + x.num) +  x.denom*(y.denom*y.whole + y.num);
    answer.denom = x.denom * y.denom;
    reduce(answer);
    return answer;
}

mixedNumber mult(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    answer.whole = 0;
    answer.num = (x.denom*x.whole + x.num) * (y.denom*y.whole + y.num);
    answer.denom = x.denom * y.denom;
    reduce(answer);
    return answer;
}


mixedNumber divide(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    answer.whole = 0;
    answer.num = (x.denom*x.whole + x.num) * y.denom ;
    answer.denom = x.denom * (y.denom*y.whole + y.num);
    reduce(answer);
    return answer;
}

mixedNumber subtract(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    answer.whole = 0;
    answer.num = y.denom*(x.denom*x.whole - x.num) +  x.denom*(y.denom*y.whole + y.num);
    answer.denom = x.denom * y.denom;
    reduce(answer);
    return answer;
}

void parseCommandLine(int argc, char* argv[], ifstream &in, ofstream &out)
{
    char* pointer;

    if( argc > 1)
    {
        cout<<"Useage: argvArgc [filename] [/i=filename]"<<endl;
    }
    for(int i = 1; i < argc; i++)
    {
    pointer = &argv[i][0];
    in.open(strcat(pointer,".mat"));
        if(in.fail())
        {
            in.close();
          cout<<"Output file does not exist and new file created"<<endl;
          out.open(pointer);
          exit(1);
        }
        else
        {   char ch;

            out.open(pointer);
            out << "10 20 30 40 50";
            out.close();
            while(in)
            {
             in.get(ch);
             if(in) cout << ch;
            }
              in.close();
        }
    }
}
