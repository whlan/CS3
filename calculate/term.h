#ifndef TERM_H
#define TERM_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "mixednumber.h"

using namespace std;

class term
{
    public:
        term();
        term(const string &t);
        term& operator=(const term &other);
        term& operator=(const string &t);
        ~term();

        mixedNumber& theCoeff();
        mixedNumber& thePower();
        string theTerm();
        term& operator<<(const string &t);
        term& operator>>(string &t);
        term& operator+=(const term &y);

        friend
        term operator^(const term &x, const mixedNumber &y);

        friend
        term operator%(const term &x, const mixedNumber &y);

        friend
        bool operator<(const term &x, const term &y);

        friend
        bool operator>(const term &x, const term &y);

        friend
        bool operator<=(const term &x, const term &y);

        friend
        bool operator>=(const term &x, const term &y);

        friend
        bool operator==(const term &x, const term &y);

        friend
        bool operator!=(const term &x, const term &y);

        friend
        bool operator|=(const term &x, const term &y); // compare power

        friend
        mixedNumber eval(const mixedNumber &x);

        friend
        term operator+(const term &x, const term &y);

        friend
        term operator*(const term &x, const term &y);

        friend
        term operator*(const term &x, const mixedNumber &y);

        friend
        term operator*(const mixedNumber &x, const term &y);

        friend
        ostream& operator<<(ostream &out, const term& t);

        friend
        istream& operator>>(istream &in, term& t);

    private:
        mixedNumber coeff, power;

        void copy(const term& other);
        void nukem();
        void convertFromString(const string &t);
        string convertToString();
};

#endif // TERM_H
