#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include "mixednumber.h"
#include "term.h"
using namespace std;

term operator^(const term &x, const mixedNumber &y)
{

}

term operator%(const term &x, const mixedNumber &y)
{
    term answer;
    answer.coeff = x.coeff*y;
    answer.power -= 1;
    return answer;
}

bool operator<(const term &x, const term &y)
{
    return x < y;
}

bool operator>(const term &x, const term &y)
{
    return x > y;
}

bool operator<=(const term &x, const term &y)
{
    return x == y || x < y;
}

bool operator>=(const term &x, const term &y)
{
    return x == y || x > y;
}

bool operator==(const term &x, const term &y)
{
    return x.coeff == y.coeff && x.power == y.power;
}

bool operator!=(const term &x, const term &y)
{
    return x != y;
}

bool operator |=(const term &x, const term &y) // compare power
{
    return x.power == y.power;
}

mixedNumber eval(const mixedNumber &x)
{
}


term operator+(const term &x, const term &y)
{
    stringstream ss;
    term answer;
    if(x.power == y.power)
    {
       answer.coeff = x.coeff+y.coeff;
       answer.power = x.power;
       return answer;
    }     
}


term operator*(const term &x, const term &y)
{
    term answer;
    stringstream ss;
    answer.coeff = x.coeff*y.coeff;
    answer.power = x.power*y.power;

    return answer;
}


term operator*(const term &x, const mixedNumber &y)
{
    term answer;
    stringstream ss;
    answer.coeff = x.coeff*y;
    answer.power = x.power;

    return answer;
}


term operator*(const mixedNumber &x, const term &y)
{
    term answer;
    stringstream ss;
    answer.coeff = x*y.coeff;
    answer.power = y.power;

    return answer;
}

ostream& operator<<(ostream &out, const term& t)
{
    if(t.coeff == 0)
        out<<0;
    else
        if(t.power == 0)
        out<<t.coeff;
        else
            out<<t.coeff<<"X"<<"^"<<t.power;

    return out;
}

istream& operator>>(istream &in, term& t)
{
    stringstream ss;
    string s;
    cout<<"this is t:"<<t<<endl;
    if(in == cin)
    {
        in>>t;
    }
    else if(ss<<t)
    {
        ss>>s;
        cout<<s<<endl;
        getline(in,s);
    }
    else
    {
        cout<<"Please enter coefficient: "<<endl;
              cout<<t.coeff;
        cout<<"Please enter power: "<<endl;
              cout<<t.power;
    }

    return in;
}
