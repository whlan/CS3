#include "mixednumber.h"
#include <math.h>
#include <string>
#include <sstream>
using namespace std;

//Constructos and destructor
mixedNumber::mixedNumber()//default constructor
{
    whole = 0;
    num = 0;
    denom = 1;
}

mixedNumber::mixedNumber(double w, double n, double d) //constructor with parameters
{
    whole = w;
    num = n;
    denom = d;
    reduce();
}

mixedNumber::mixedNumber(const mixedNumber &other) //copy constructor
{
    copy(other);
}


mixedNumber::~mixedNumber() //destructor
{
    whole = 0;
    num = 0;
    denom = 0;
}

//Assignment operators
mixedNumber& mixedNumber::operator=(const mixedNumber &other)//assignment operator
{
    if(this != &other)
        copy(other);
    return *this;
}


mixedNumber& mixedNumber::operator+=(const mixedNumber &other)
{
    *this = *this + other;
    return *this;
}

mixedNumber& mixedNumber::operator-=(const mixedNumber &other)
{
    *this = *this - other;
    return *this;
}

mixedNumber& mixedNumber::operator*=(const mixedNumber &other)
{
    *this = *this * other;
    return *this;
}

mixedNumber& mixedNumber::operator/=(const mixedNumber &other)
{
    *this = *this / other;
    return *this;
}


mixedNumber& mixedNumber::operator+=(const double &other)
{
    *this = *this + other;
    return *this;
}

mixedNumber& mixedNumber::operator-=(const double &other)
{
    *this = *this - other;
    return *this;
}

mixedNumber& mixedNumber::operator*=(const double &other)
{
    *this = *this * other;
    return *this;
}

mixedNumber& mixedNumber::operator/=(const double &other)
{
    *this = *this / other;
    return *this;
}

//Accessor functions
double mixedNumber::getWhole()
{
    return whole;
}

double mixedNumber::getNum()
{
    return num;
}

double mixedNumber::getDenom()
{
    return denom;
}

//Mutator functions
void mixedNumber::setWhole(double w)
{
    whole = w;
    reduce();
}

void mixedNumber::setNum(double n)
{
    num = n;
    reduce();
}

void mixedNumber::setDenom(double d)
{
    if(d == 0)
        cout<<"Illegal denominator!"<<endl;
    else
    {
        denom = d;
        reduce();
    }
}



void mixedNumber::copy(const mixedNumber &other)
{
    whole = other.whole;
    num = other.num;
    denom = other.denom;
}

void mixedNumber::reduce()
{
    bool wholeNeg = whole < 0,
         numNeg = num < 0,
         denomNeg = denom < 0;
    double newNum = abs(denom)*abs(whole) + abs(num),
        newDenom =abs(denom), divisor = gcd(newNum,newDenom ), temp;   
    newNum /= divisor;
    newDenom /= divisor;   
    whole = (int) newNum/(int) newDenom;
    if(whole == 0)
    {
        num = newNum;
    }
    else
    {
    temp = newNum - (int) newNum ;
    num = ((int) newNum % (int)newDenom)+temp;
    }
    denom = newDenom;
    if(denom == 1)
    {
         whole = (denom*whole + num);
         num = 0;
    }
    if(whole == 0)
    {
        if(numNeg || denomNeg)
            num*=-1;
    }
    else
        if((wholeNeg && denomNeg && numNeg)   ||
           (wholeNeg && !denomNeg && !numNeg) ||
           (!wholeNeg && !numNeg && denomNeg) ||
           (!wholeNeg && numNeg && !denomNeg))
            whole*=-1;
}

int mixedNumber::gcd(double p , double q)
{
    p = (int)p;
    q = (int)q;
    return q==0 ? p : gcd(q, fmod(p,q));
}

string mixedNumber::toString()
{
    stringstream ss;
    string s;
    if(whole == 0)
    {
        if(num == 0)
            return 0;

        else
        {
            ss<<num<<"/"<<denom;
            ss>>s;
            return ss.str();
        }
    }
    else
    {
        if(num == 0)
        {
            ss<<whole;
            return ss.str();
        }
        else
         {
            ss<<whole<<" "<<num<<"/"<<denom;
            return ss.str();
        }
    }
}
