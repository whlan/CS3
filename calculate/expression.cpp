#include "expression.h"
#include <vector>
#include "term.h"
#include "mixednumber.h"

expression::expression()
{
    exp;
}

expression::expression(const string &e)
{
    copy(e);
}

expression& expression::operator=(const expression &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

expression& expression::operator=(const string &e)
{

}

expression& expression::operator=(const term &t)
{

}

expression::~expression()
{
    nukem();
}

string expression::theExpression()
{

}

mixedNumber expression::eval(const mixedNumber &x)
{

}

mixedNumber expression::operator()(const mixedNumber &x)
{
    return eval(x);
}

expression& expression::operator<<(const string &e)
{
     convertFromString(e);
}

expression& expression::operator>>(string &e)
{
    e = convertToString();
}

expression& expression::operator+=(const expression &y)
{
}

void expression::copy(const expression& other)
{
    exp = other.exp;
}

void expression::nukem()
{
    exp.clear();
}

void expression::convertFromString(const string &t)
{
    stringstream ss;
    term temp;
    cout<<"this is string"<<t;
    ss<<t;
    cout<<"WTF";
    while(ss >>temp)
    {
        exp.push_back(temp);
    }
    for(int i = 0; i<exp.size(); i++)
        cout<<exp[i]<<endl;
}

string expression::convertToString()
{

}

void expression::sort()
{
    int size = exp.size();

    for(int i = 0; i < size; i++)

           for(int j = 0; j < size; j++)

               if(exp[i] < exp[j])

                  swap(exp[i],exp[j]);
}
