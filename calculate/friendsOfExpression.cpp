#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "mixednumber.h"
#include "expression.h"
#include "term.h"

expression operator^(const mixedNumber &x, const string &y)
{

}

expression operator%(const expression &x, const string &y)
{

}

bool operator==(const expression &x, const expression &y)
{

}


expression operator+(const expression &x, const expression &y)
{
}


expression operator*(const expression &x, const expression &y)
{

}

expression operator*(const expression &x, const mixedNumber &y)
{

}

expression operator*(const term &x, const expression &y)
{

}

expression operator*(const expression &x, const term &y)
{

}

expression operator*(const mixedNumber &x, const expression &y)
{

}

ostream& operator<<(ostream &out, const expression& t)
{

}

istream& operator>>(istream &in, expression& t)
{

}
