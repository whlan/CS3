#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int* create2DArray(int rows, int columns);
void set(int* arr, int rows, int columns, int desired_row, int desired_column, int value);
int get(int* arr, int rows, int columns, int desired_row, int desired_column);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int* ptr = create2DArray(2,3);
    int desired_row, desired_column, choice,value;
    char comma,ans;

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
        cout<<ptr[3*i+j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    do
    {
       cout<<"Enter (1) value to 2D array (2) get number from the array " << endl;
       cin>>choice;
       while(choice < 1 || choice > 2)
       {
           cout<<"The number you enter is not from the choice; Please re-enter:" << endl;
           cin>>choice;
       }
        switch(choice)
        {
            case 1:
                cout<<"Enter your desired row and column and value as row,colmn,value"<<endl;
                cin>>desired_row>>comma>>desired_column>>comma>>value;
                set(ptr, 2, 3, desired_row, desired_column, value);
                for(int i=0; i<2; i++)
                {
                    for(int j=0; j<3; j++)
                    {
                    cout<<ptr[3*i+j]<<" ";
                    }
                    cout<<endl;
                }
                break;

            case 2:
                cout<<"Enter your desired row and column as row,colmn"<<endl;
                cin>>desired_row>>comma>>desired_column;
                cout<<get(ptr, 2, 3, desired_row, desired_column);

            break;
        }
        cout<<"Do you want to continue? (y/n) : " << endl;
        cin>>ans;
    }while(ans == 'y' || ans =='Y');
    exit(0);
    return a.exec();
}

int* create2DArray(int rows, int columns)
{
    int* new1DArray = new int[rows*columns];
    for(int i=0; i<rows; i++)
        for(int j=0; j<columns; j++)
        new1DArray[columns*i+j] = 0;

    return new1DArray;
}

void set(int* arr, int rows, int columns, int desired_row, int desired_column, int value)
{
   if(desired_row >= rows || desired_column >= columns)
   {
       cout<<"ERROR: DESIRED INDICES ARE INVALID"<<endl;
       exit(1);
   }
   else
   {
       arr[columns*desired_row+desired_column] = value;
   }
}

int get(int* arr, int rows, int columns, int desired_row, int desired_column)
{
    if(desired_row >= rows || desired_column >= columns)
    {
        cout<<"ERROR: DESIRED INDICES ARE INVALID"<<endl;
        exit(1);
    }
    else
    {
        return arr[columns*desired_row+desired_column];
    }
}
