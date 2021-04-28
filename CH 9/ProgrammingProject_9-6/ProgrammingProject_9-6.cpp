#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

string* addEntry(string *dynamicArray, int &size, string newEntry);
string* deleteEntry(string *dynamicArray, int &size, string entryToDelete);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int size=5;
    string *stringPtr=new string[size];
    int i=0, choice;
    string name;

    stringPtr[i++] = "Jefferson";
    stringPtr[i++] = "Reagan";
    stringPtr[i++] = "Johnson";
    stringPtr[i++] = "Kennedy";
    stringPtr[i++] = "Roosevelt";

    cout<<"Initial List:"<<endl;
    for(i=0; i < size; i++)
        cout << i << ": " << stringPtr[i] << endl;



    do
    {
        cout<<"\nAdding an Entry(1), Deleting an Entry(2), Quit(0):"<<endl;
        cin>>choice;
        while(choice <0 || choice > 2)
        {
            cout<<"ERROR: your choice is not in the list; Please re-enter your choice again: "<<endl;
            cin>>choice;
        }
        switch(choice)
        {
            case 1:
                cout<<"Enter a name to add in the entry:"<<endl;
                cin>>name;
                cout<<endl;
                stringPtr=addEntry(stringPtr, size,name);
                for(i=0; i < size; i++)
                cout << i << ": " << stringPtr[i] << endl;
                break;
            case 2:
                cout<<"Enter a name to delete in the entry:"<<endl;
                cin>>name;
                cout<<endl;
                stringPtr=deleteEntry(stringPtr, size, name);
                for(i=0; i < size; i++)
                   cout << i << ": " << stringPtr[i] << endl;
                break;
        }
    }while(choice != 0);

    exit(0);
    return a.exec();
}


string *addEntry(string *dynamicArray, int &size, string newEntry)
{
   string *newArray = new string[size + 1];

   for(int i = 0; i < size; i++)
   {
       newArray[i] = dynamicArray[i];
   }

   newArray[size] = newEntry;

   size++;

   delete [] dynamicArray;

   return newArray;
}

string* deleteEntry(string* dynamicArray, int& size, string entryToDelete)
{
    int stop, flag = 0;
    string* newArray = new string[size -1];


    for (int i = 0; i < size; i++)
    {
        if (dynamicArray[i] != entryToDelete)
            newArray[i] = dynamicArray[i];
        else
        {
            stop=i;
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
    for (int i = stop; i < size - 1; i++)
        newArray[i] = dynamicArray[i + 1];

    size--;

    delete [] dynamicArray;

    return newArray;
    }
    else
    {
        delete [] newArray;

        return dynamicArray;
    }
}
