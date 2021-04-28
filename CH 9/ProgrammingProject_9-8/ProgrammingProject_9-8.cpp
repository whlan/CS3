#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void sort(vector<int> &grade, int size);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector<int> grade;
    int* ptr ;
    int input, size ;

    cout<<"Enter grades of the student(-1 to exit): "<< endl;
    cin>>input;

    while(input>=0)
    {
        grade.push_back(input);
        cin>>input;
    }

    sort(grade, grade.size());

    ptr = new int[size];
    size = grade[grade.size()-1];
    for(int i =0; i<= size; i++)
    {
        ptr[i] = 0;
    }

    for(int i =0; i< grade.size(); i++)
    {
        ptr[grade[i]]++;
    }

    for(int i =0; i<= size; i++)
    {
        if(ptr[i] != 0)
            cout << "Number of " << i << "'s: " << ptr[i] << endl;
    }

    delete [] ptr;

    exit(0);
    return a.exec();
}

void sort(vector<int> &grade, int size)

{
    int bflag = 0, temp;
         do
            {
                bflag = 0;
                for(int i = 0; i <= size-2; i++)
                    if(grade[i] > grade[i+1])
                {
                    temp = grade[i];
                    grade[i] = grade[i+1];
                    grade[i+1] = temp;
                    bflag = 1;
                }
            }
            while(bflag == 1);

}

