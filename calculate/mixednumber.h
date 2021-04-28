#ifndef MIXEDNUMBER_H
#define MIXEDNUMBER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

class mixedNumber
{
    public:
        mixedNumber();//default constructor
        mixedNumber(double w, double n = 0, double d = 1); //constructor with parameters
        mixedNumber(const mixedNumber &other); //copy constructor

        ~mixedNumber(); //destructor


        //Assignment operators
        mixedNumber& operator=(const mixedNumber &other);//assignment operator
        mixedNumber& operator+=(const mixedNumber &other);
        mixedNumber& operator-=(const mixedNumber &other);
        mixedNumber& operator*=(const mixedNumber &other);
        mixedNumber& operator/=(const mixedNumber &other);

        mixedNumber& operator+=(const double &other);
        mixedNumber& operator-=(const double &other);
        mixedNumber& operator*=(const double &other);
        mixedNumber& operator/=(const double &other);

        //Accessor functions
        double getWhole();
        double getNum();
        double getDenom();

        //Mutator functions
        void setWhole(double w);
        void setNum(double n);
        void setDenom(double d);

        string toString();

        //Friends that can take two mixed numbers and create a third mixed number

        friend
        mixedNumber operator*(const mixedNumber &x, const mixedNumber &y);

        friend
        mixedNumber operator/(const mixedNumber &x, const mixedNumber &y);

        friend
        mixedNumber operator-(const mixedNumber &x, const mixedNumber &y);

        friend
        mixedNumber operator+(const mixedNumber &x, const mixedNumber &y);

        //friends that take an doubles and a mixed number
        friend
        mixedNumber operator*(const mixedNumber &x, const double &y);

        friend
        mixedNumber operator/(const mixedNumber &x, const double &y);

        friend
        mixedNumber operator-(const mixedNumber &x, const double &y);

        friend
        mixedNumber operator+(const mixedNumber &x, const double &y);

        friend
        mixedNumber operator*(const double &x, const mixedNumber &y);

        friend
        mixedNumber operator/(const double &x, const mixedNumber &y);

        friend
        mixedNumber operator-(const double &x, const mixedNumber &y);

        friend
        mixedNumber operator+(const double &x, const mixedNumber &y);


        //input / output friends

        friend
        ostream& operator<<(ostream &out, const mixedNumber &x);

        friend
        istream& operator>>(istream &in, mixedNumber &x);

        //Comparision operator friends
        friend
        bool operator==(const mixedNumber &x, const mixedNumber &y);

        friend
        bool operator!=(const mixedNumber &x, const mixedNumber &y);

        friend
        bool operator>=(const mixedNumber &x, const mixedNumber &y);

        friend
        bool operator<=(const mixedNumber &x, const mixedNumber &y);

        friend
        bool operator>(const mixedNumber &x, const mixedNumber &y);

        friend
        bool operator<(const mixedNumber &x, const mixedNumber &y);

        //Comparision operators for mixedNumbers and doubles
        friend
        bool operator==(const mixedNumber &x, const double &y);

        friend
        bool operator!=(const mixedNumber &x, const double &y);

        friend
        bool operator>=(const mixedNumber &x, const double &y);

        friend
        bool operator<=(const mixedNumber &x, const double &y);

        friend
        bool operator>(const mixedNumber &x, const double &y);

        friend
        bool operator<(const mixedNumber &x, const double &y);

        friend
        bool operator==(const double &x, const mixedNumber &y);

        friend
        bool operator!=(const double &x, const mixedNumber &y);

        friend
        bool operator>=(const double &x, const mixedNumber &y);

        friend
        bool operator<=(const double &x, const mixedNumber &y);

        friend
        bool operator>(const double &x, const mixedNumber &y);

        friend
        bool operator<(const double &x, const mixedNumber &y);


    private:
        double whole, num, denom;

        void copy(const mixedNumber &other);
        void reduce();
        int gcd(double p , double q);
};

#endif // MIXEDNUMBER_H
