#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

void initialize(int** &rolls);
void display(int **rolls);
void login(int** &rolls);
void search(int** rolls, int &labs, int &stations);
void logoff(int** &rolls, int &labs, int &stations);
void Delete(int** &rolls);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int **rolls, choice;

    initialize(rolls);
    while (choice != 0)
        {
            int labs , stations ;
            cout << endl;
            display(rolls);
            cout << "MAIN MENU" << endl;
            cout << "0) Quit" << endl;
            cout << "1) Simulate login" << endl;
            cout << "2) Simulate logoff" << endl;
            cout << "3) Search" << endl;
            cin >> choice;
            switch(choice)
            {
                case 1:
                login(rolls);
                break;
                case 2:
                cout<<"Enter the ID number to log off: ";
                logoff(rolls, labs, stations);
                break;
                case 3:
                cout<<"Enter the ID number to search: ";
                search(rolls, labs, stations);
                cout<< "Lab Number: " <<labs << "  Computer Station: " << stations << endl << endl;
                break;
            }
        }
    Delete(rolls);
    return a.exec();
}

void initialize(int** &rolls)
{
    rolls = new int*[3];
    rolls[0] = new int[5];
    rolls[1] = new int[6];
    rolls[2] = new int[4];
    rolls[3] = new int[3];

    for(int i = 0; i < 5; i++)
    {
        (*(*(rolls + 0) + i)) = 0;
    }

    for(int i = 0; i < 6; i++)
    {
        (*(*(rolls + 1) + i)) = 0;
    }

    for(int i = 0; i < 4; i++)
    {
        (*(*(rolls + 2) + i)) = 0;
    }

    for(int i = 0; i < 3; i++)
    {
        (*(*(rolls + 3) + i)) = 0;
    }

}

void display(int **rolls)
{
    cout<< "Lab Number Computer Stations"<< endl;

    cout<<"1      ";
    for(int i = 0; i < 5; i++)
    {
        if((*(*(rolls+0)+i)) == 0)
        {
          cout<< setw(5)<< i+1 << ": empty";
        }
        else
        {
        cout<< setw(5)<< i+1 << ": "<< (*(*(rolls+0)+i));
        }
    }
    cout<<endl;
    cout<<"2      ";
    for(int i = 0; i < 6; i++)
    {
        if((*(*(rolls+1)+i)) == 0)
        {
          cout<< setw(5)<< i+1 << ": empty";
        }
        else
        {
        cout<< setw(5)<< i+1 << ": "<< (*(*(rolls+1)+i));
        }
    }
    cout<<endl;
    cout<<"3      ";
    for(int i = 0; i < 4; i++)
    {
        if((*(*(rolls+2)+i)) == 0)
        {
          cout<< setw(5)<< i+1 << ": empty";
        }
        else
        {
        cout<< setw(5)<< i+1 << ": "<< (*(*(rolls+2)+i));
        }
    }
    cout<<endl;
    cout<<"4      ";
    for(int i = 0; i < 3; i++)
    {
        if((*(*(rolls+3)+i)) == 0)
        {
          cout<< setw(5)<< i+1 << ": empty";
        }
        else
        {
        cout<< setw(5)<< i+1 << ": "<< (*(*(rolls+3)+i));
        }
    }
    cout<<endl<<endl;
}

void login(int** &rolls)
{
    int labs, stations, ID;
    cout<<"Select a Lab between 1 to 4: ";
    cin>>labs;
    while(labs < 1 || labs > 4)
    {
        cout<<"Lab is out of range; re-enter the lab number: ";
              cin>>labs;
    }
    cout<<"Select a computer station: ";
    switch(labs)
    {
        case 1:
            cin>>stations;
            while(stations < 1 || stations > 5)
            {
                cout<<"Station is out of range; re-enter the number: ";
                      cin>>stations;
            }
            break;
        case 2:
            cin>>stations;
            while(stations < 1 || stations > 6)
            {
                cout<<"Station is out of range; re-enter the number: ";
                      cin>>stations;
            }
            break;
        case 3:
            cin>>stations;
            while(stations < 1 || stations > 4)
            {
                cout<<"Station is out of range; re-enter the number: ";
                      cin>>stations;
            }
            break;
        case 4:
            cin>>stations;
            while(stations < 1 || stations > 3)
            {
                cout<<"Station is out of range; re-enter the number: ";
                      cin>>stations;
            }
            break;
    }

    while((*(*(rolls+(labs-1))+(stations-1))) != 0)
    {
        cout<<"Station is in use right now; Please reselect";
        cout<<"Lab: ";
        cin>>labs;
        cout<<"Computer station: ";
        cin>>stations;
    }

    cout<<"Station avaliable; Please enter your five-digit ID number: ";
    cin>>ID;
    while(ID < 10000 || ID > 99999)
    {
        cout<<"ID number have to be five-digit :" << endl;
        cin>> ID;
    }
    (*(*(rolls+(labs-1))+(stations-1))) = ID;

}

void search(int** rolls, int &labs, int &stations)
{
    int track = 0, ID;
    cout<<"Enter the ID number to search: ";
    cin>> ID;
    while(ID < 10000 || ID > 99999)
    {
        cout<<"ID number have to be five-digit :" << endl;
        cin>> ID;
    }

    for(int i = 0; i < 5; i++)
    {
        if((*(*(rolls + 0) + i)) == ID)
        {
            labs = 1;
            stations = i+1;
            track = 1;
        }
    }

    for(int i = 0; i < 6; i++)
    {
        if((*(*(rolls + 1) + i)) == ID)
        {
            labs = 2;
            stations = i+1;
            track = 1;
        }
    }

    for(int i = 0; i < 4; i++)
    {
        if((*(*(rolls + 2) + i)) == ID)
        {
            labs = 3;
            stations = i+1;
            track = 1;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        if((*(*(rolls + 3) + i)) == ID)
        {
            labs = 4;
            stations = i+1;
            track = 1;
        }
    }

 if(track == 0)
 {
     cout<<"None";
 }

}

void logoff(int** &rolls, int &labs, int &stations)
{
    search(rolls, labs, stations);
    if(labs-1 != 0 && stations-1 != 0)
    (*(*(rolls + (labs-1)) + (stations-1))) = 0;
    else
        cout<<"ERROR: NO ID FOUND"<< endl;
}

void Delete(int** &rolls)
{
    for(int i = 0; i < 3; i++)
    {
        delete [] rolls[i];
    }
    delete []rolls;
}
