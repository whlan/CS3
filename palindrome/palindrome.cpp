#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>

using namespace std;

void makeUpper(char *word);
void delChar(char word[]);
void getInput(char *title, char word[]);
void getReverse(char word1[], char word2[]);
char* find(char* start, char what);
bool palindrome(char *word1, char *word2);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char word1[30], word2[30];
    bool again = true;
    while(again)
    {
        getInput("Please enter a word: ", word1);
        if(*word1 == '\0')
            again = false;
        else
        {
            makeUpper(word1);
            delChar(word1);
            getReverse(word1,word2);
            cout << "Lowercase removed is " << word1 << endl;
            cout << "In reversed order is " << word2<< endl;
            if(palindrome(word1,word2))
                cout<<"you have a palindrome!"<<endl;
            else
                cout<<"You do not have a palindrome!"<<endl;
        }
    }
    cout<<"The end!"<<endl;
    exit(0);
    return a.exec();
}

void getInput(char *title, char word[30])
{
    cout<<title;
    cin.getline(word,30);
}

void makeUpper(char *word)
{
    while(*word != '\0')
    {
        if(*word >= 'a' && *word <= 'z')
            *word -= 32;
        // *word = *word - 32
        word++;
    }
}

void delChar(char word[])
{
        char temp[30];
        int j = 0;

        for(int i = 0; i < 30; i++){
            if(word[i] >= 'A' && word[i] <= 'Z')
            {
                    temp[j] = word[i];
                    j++;
            }
        }
        temp[j] = '\0';

        for(int i = 0; i < 30; i++)
        {
            word[i] = temp[i];
        }
}


void getReverse(char word1[], char word2[])
{
    char *end = find(word1,'\0');
    end--;
    while(end != word1)
    {
        *word2 = *end;
        word2++;
        end--;
    }
    *word2 = *word1;
    word2++;
    *word2 = '\0';
}


char* find(char* start, char what)
{
    while(*start != what && *start != '\0')
        start++;
    return *start == what ? start : NULL ;
    /*
      if(*start == what)
        return start;
      else
        return NULL;
    */
}


bool palindrome(char *word1, char *word2)
{
    bool same = true;
    while(*word1 != '\0')
        if(*word1 != *word2)
        {
            same = false;
            break;
        }
        else
        {
            word1++;
            word2++;
        }
    return same;
}
