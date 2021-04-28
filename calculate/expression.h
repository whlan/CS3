#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "expression.h"
#include "term.h"

using namespace std;

class expression
{
    public:
        expression();
        expression(const string &e);
        expression& operator=(const expression &other);
        expression& operator=(const string &e);
        expression& operator=(const term &t);
        ~expression();

        string theExpression();
        mixedNumber eval(const mixedNumber &x);
        mixedNumber operator()(const mixedNumber &x);
        expression& operator<<(const string &e);
        expression& operator>>(string &e);
        expression& operator+=(const expression &y);

        friend
        expression operator^(const mixedNumber &x, const string &y);

        friend
        expression operator%(const expression &x, const string &y);

        friend
        bool operator==(const expression &x, const expression &y);

        friend
        expression operator+(const expression &x, const expression &y);

        friend
        expression operator*(const expression &x, const expression &y);

        friend
        expression operator*(const expression &x, const mixedNumber &y);

        friend
        expression operator*(const term &x, const expression &y);

        friend
        expression operator*(const expression &x, const term &y);

        friend
        expression operator*(const mixedNumber &x, const expression &y);

        friend
        ostream& operator<<(ostream &out, const expression& t);

        friend
        istream& operator>>(istream &in, expression& t);

    private:
        vector<term> exp;

        void copy(const expression& other);
        void nukem();
        void convertFromString(const string &t);
        string convertToString();
        void sort();
};
#endif // EXPRESSION_H
