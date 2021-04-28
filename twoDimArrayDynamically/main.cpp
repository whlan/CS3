#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

void initialize(int** &rolls, int rows, int cols);
void cleanUp(int** &rows, int row, int col);
void rollDice(int **rolls,int rows, int cols, int rollNum );
/*
  A two dimensional array of integers is actually
  an array of integer pointers wherein each integer
  pointer in the array points to an array of integers
*/
void display(int **rolls, int numRolls);
bool getInput(int &numRolls);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(time(NULL));
    int **rolls, numRolls;
    while(getInput(numRolls))
    {
        initialize(rolls, numRolls+1, 11);
        rollDice(rolls, 10,11,numRolls);
        display(rolls, numRolls);
    }
    return a.exec();
}


void display(int **rolls, int numRolls)
{
   int colWidth = 1 + numRolls + 2;
   cout<<endl<<endl
      <<setw(3)<<"|";
   for(int i = 2; i < 13; i++)
       cout<<setw(colWidth)<<i;
   cout<<endl<<setw(3+ 12*colWidth)
       <<setfill('-')
       <<"-"<<setfill(' ')<<endl;
   for(int i = 0; i <= numRolls; i++)
   {
       cout<<setw(2)<<i<<"|";
       for(int j = 0; j < 11; j++)
           cout<<setw(colWidth)<<(*(*(rolls+i)+j));
       cout<<endl;
   }
}

bool getInput(int &numRolls)
{
    cout<<"In powers of ten, how many times would you like to roll the dice? ";
    cin>>numRolls;
    return numRolls >= 1;
    /*
      The above is exactly the same as:
      if(numRolls >= 1)
        return true;
      else
        return false;
    */
}

void rollDice(int **rolls,int rows, int cols, int rollNum )
{
    int diceValue;
    if(rollNum >= rows)
    {
        cout<<"Cannot do that many rolls of the dice!"<<endl;
        return;
    }
    for(int i = 0; i < rollNum; i++)
    {
        int diceRoll = (int)pow(10., i);
        for(int j = 0; j < diceRoll; j++ )
        {

            diceValue =(1 + rand()%6) + (1 + rand()%6) - 2;
            (*(*(rolls + i ) + diceValue))++;
            /*
              The above is the same as:
              rolls[rollNum][diceValue]++;
            */
        }
    }
}

void initialize(int** &rolls, int rows, int cols)
{
    rolls = new int*[rows];
    for(int i = 0; i < rows; i++)
        rolls[i] = new int[cols];
    cout<<"Initializing....."<<endl;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            (*(*(rolls + i) + j)) = 0;
    cout<<"Finished initializing...."<<endl;
}

void cleanUp(int** &rows, int row, int col)
{
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            rows[i][j] = 0;
    for(int i = 0; i < row; i++)
    {
        delete [] rows[i];
        rows[i] = NULL;
    }
    delete [] rows;
    rows = NULL;
}
