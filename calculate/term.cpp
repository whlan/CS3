#include "term.h"
#include "mixednumber.h"
#include <string>
#include <sstream>
#include <string.h>

term::term()
{
    coeff;
    power;
}

term::term(const string &t)
{
    copy(t);
}

term& term::operator=(const term &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

term& term::operator=(const string &t)
{
}

term::~term()
{
    nukem();
}

mixedNumber& term::theCoeff()
{
    return coeff;
}

mixedNumber& term::thePower()
{
    return power;
}

string term::theTerm()
{
    stringstream ss;
    ss<<coeff<<"x"<<"^"<<power;
    return ss.str();
}

term& term::operator<<(const string &t)
{
    convertFromString(t);
}

term& term::operator>>(string &t)
{
    t = convertToString();
}

term& term::operator+=(const term &y)
{
    *this = *this + y;
    return *this;
}

void term::copy(const term& other)
{
    coeff = other.coeff;
    power = other.power;
}

void term::nukem()
{
    coeff = 0;
    power = 0;
}

void term::convertFromString(const string &t)
{
    stringstream ss;
    char junk;
    ss<<t;
    if(ss.peek() == 'X')
    {
        coeff = 1;
        ss>>junk;
        if(ss.peek() == '^')
        {
            ss>>junk>>power;
        }
        else
        power = 1;
    }
    else
    {
        ss>>coeff;
        if(ss.peek() == 'X')
        {
            ss>>junk;
            if(ss.peek() == '^')
                ss>>junk>>power;
            else
                power = 1;
        }
        else
            power = 0;
    }

    cout<<"THIS IS COEFF: "<<coeff<<endl;
    cout<<"THIS IS power: "<<power<<endl;
}

string term::convertToString()
{
    stringstream ss;
    string s;
    cout<<"CONVERT TO STRING"<<endl;
    if(coeff == 0)
            return 0;
    else
    {
        if(power == 0)
            {
                ss<<coeff;
                ss>>s;
                return s;
            }
        else
            {
                ss<<coeff<<"x"<<"^"<<power;
                ss>>s;
                return s;
            }
    }
}
