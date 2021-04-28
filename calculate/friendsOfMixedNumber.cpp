#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "mixednumber.h"

using namespace std;


//s that can take two mixed numbers and create a third mixed number



mixedNumber operator*(const mixedNumber &x, const mixedNumber &y)
{
    double num, denom;
    num = (x.whole*x.denom+x.num) * (y.whole*y.denom+y.num);
    denom = x.denom * y.denom;
    return mixedNumber(0,num, denom);
}


mixedNumber operator/(const mixedNumber &x, const mixedNumber &y)
{
    double num, denom;
    num = (x.whole*x.denom+x.num) * y.denom;
    denom = x.denom * (y.whole*y.denom+y.num);
    return mixedNumber(0,num, denom);
}


mixedNumber operator-(const mixedNumber &x, const mixedNumber &y)
{
    double num, denom;
    num = y.denom*(x.denom*x.whole + x.num) -  x.denom*(y.denom*y.whole + y.num);
    denom = x.denom * y.denom;
    return mixedNumber(0,num, denom);
}


mixedNumber operator+(const mixedNumber &x, const mixedNumber &y)
{
    double num, denom;
    num = y.denom*(x.denom*x.whole + x.num) +  x.denom*(y.denom*y.whole + y.num);
    denom = x.denom * y.denom;
    return mixedNumber(0,num, denom);
}

//s that take an doubleeger and a mixed number

mixedNumber operator*(const mixedNumber &x, const double &y)
{
    mixedNumber mixedY(y), answer = x * mixedY;
    return answer;
}


mixedNumber operator/(const mixedNumber &x, const double &y)
{
    mixedNumber mixedY(y), answer = x / mixedY;
    return answer;
}

mixedNumber operator-(const mixedNumber &x, const double &y)
{
    mixedNumber mixedY(y), answer = x - mixedY;
    return answer;
}


mixedNumber operator+(const mixedNumber &x, const double &y)
{
    mixedNumber mixedY(y), answer = x + mixedY;
    return answer;
}


mixedNumber operator*(const double &x, const mixedNumber &y)
{
    mixedNumber mixedX(x), answer =  mixedX * y;
    return answer;
}


mixedNumber operator/(const double &x, const mixedNumber &y)
{
    mixedNumber mixedX(x), answer =  mixedX / y;
    return answer;
}


mixedNumber operator-(const double &x, const mixedNumber &y)
{
    mixedNumber mixedX(x), answer =  mixedX - y;
    return answer;
}


mixedNumber operator+(const double &x, const mixedNumber &y)
{
    mixedNumber mixedX(x), answer =  mixedX + y;
    return answer;
}


//Comparision operator s

bool operator==(const mixedNumber &x, const mixedNumber &y)
{
    double xNeg = x.whole < 0 ? -1 : x.whole == 0 && x.num < 0 ? -1 : 1,
        yNeg = y.whole < 0 ? -1 : y.whole == 0 && y.num < 0 ? -1 : 1;
    return xNeg*(abs(x.whole)*abs(x.denom) + x.num )*y.denom == yNeg*(abs(y.whole)*abs(y.denom)+y.num)*x.denom;
}


bool operator!=(const mixedNumber &x, const mixedNumber &y)
{
    double xNeg = x.whole < 0 ? -1 : x.whole == 0 && x.num < 0 ? -1 : 1,
        yNeg = y.whole < 0 ? -1 : y.whole == 0 && y.num < 0 ? -1 : 1;
    return xNeg*(abs(x.whole)*abs(x.denom) + x.num )*y.denom != yNeg*(abs(y.whole)*abs(y.denom)+y.num)*x.denom;
}


bool operator>=(const mixedNumber &x, const mixedNumber &y)
{
    return x == y || x > y;
}


bool operator<=(const mixedNumber &x, const mixedNumber &y)
{
    return x == y || x < y;
}


bool operator>(const mixedNumber &x, const mixedNumber &y)
{
    double xNeg = x.whole < 0 ? -1 : x.whole == 0 && x.num < 0 ? -1 : 1,
        yNeg = y.whole < 0 ? -1 : y.whole == 0 && y.num < 0 ? -1 : 1;
    return xNeg*(abs(x.whole)*abs(x.denom) + x.num )*y.denom > yNeg*(abs(y.whole)*abs(y.denom)+y.num)*x.denom;
}


bool operator<(const mixedNumber &x, const mixedNumber &y)
{
    double xNeg = x.whole < 0 ? -1 : x.whole == 0 && x.num < 0 ? -1 : 1,
        yNeg = y.whole < 0 ? -1 : y.whole == 0 && y.num < 0 ? -1 : 1;
    return xNeg*(abs(x.whole)*abs(x.denom) + x.num )*y.denom < yNeg*(abs(y.whole)*abs(y.denom)+y.num)*x.denom;
}

//Comparision operators for mixedNumbers and doubleegers

bool operator==(const mixedNumber &x, const double &y)
{
    return x == mixedNumber(y);
}


bool operator!=(const mixedNumber &x, const double &y)
{
    return x != mixedNumber(y);
}


bool operator>=(const mixedNumber &x, const double &y)
{
    return x >= mixedNumber(y);
}


bool operator<=(const mixedNumber &x, const double &y)
{
    return x <= mixedNumber(y);
}



bool operator>(const mixedNumber &x, const double &y)
{
    return x > mixedNumber(y);
}



bool operator<(const mixedNumber &x, const double &y)
{
    return x < mixedNumber(y);
}



bool operator==(const double &x, const mixedNumber &y)
{
    return mixedNumber(x) != y;
}



bool operator!=(const double &x, const mixedNumber &y)
{
    return mixedNumber(x) != y;
}


bool operator>=(const double &x, const mixedNumber &y)
{
    return mixedNumber(x) >= y;
}


bool operator<=(const double &x, const mixedNumber &y)
{
    return mixedNumber(x) <= y;
}


bool operator>(const double &x, const mixedNumber &y)
{
    return mixedNumber(x) > y;
}


bool operator<(const double &x, const mixedNumber &y)
{
    return mixedNumber(x) < y;
}


//input / output friends


ostream& operator<<(ostream &out, const mixedNumber &x)
{
    if(x.whole == 0)
        if(x.num == 0)
            out<<0;
        else
            out<<x.num<<"/"<<x.denom;
    else
        if(x.num == 0)
            out<<x.whole;
        else
            out<<x.whole<<" "<<x.num<<"/"<<x.denom;

    return out;
}


istream& operator>>(istream &in, mixedNumber &x)
{
    double whole = 0, num = 0, denom = 1;
    char junk;
    in>>whole;
    if(in.peek() == '/')
    {
        num = whole;
        whole = 0;
        in>>junk>>denom;
    }
    else
    {
        char space = in.get();
        if(space != ' ')
            in.unget();
        else
            if(in.peek() >='0' && in.peek() <= '9')
            {
                in >>num>>junk>>denom;
            }
            else
                in.unget();
    }
    x.whole = whole;
    x.num = num;
    x.denom = denom;
    x.reduce();
    return in;
}
