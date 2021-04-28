#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct mixedNumber
{
    int whole, num, denom;

    void output();

};

void mixedNumber::output()
{
    if(whole == 0)
        if(num == 0)
            cout<<0;
        else
            cout<<num<<"/"<<denom;
   else
        if(num == 0)
            cout<<whole;
        else
            cout<<whole<<" "<<num<<"/"<<denom;
}

bool input(string &line);
void process(string line);
int gcd(int p, int q);
void reduce(mixedNumber &number);
mixedNumber add(mixedNumber x, mixedNumber y);
mixedNumber mult(mixedNumber x, mixedNumber y);
mixedNumber divide(mixedNumber x, mixedNumber y);
mixedNumber subtract(mixedNumber x, mixedNumber y);
mixedNumber power(mixedNumber x, mixedNumber y);
char getOperator(string line, int &pos);
void getOperands(const string &line, mixedNumber &x, mixedNumber &y, int pos);
mixedNumber convertToMixedNumber(string line);
void trim(string &line);

int main()
{
    string line;
    while(input(line))
        process(line);
    return 0;
}

bool input(string &line)
{
    cout<<"Input: ";
    getline(cin,line);
    return line != "";
    /*
      The above is identical, in result, to:

      if(line != "")
        return true;
      else
        return false;

      which is also the same result of:

      return line != "" ? true : false;
    */
}

void getOperands(const string &line, mixedNumber &x, mixedNumber &y, int pos)
{
    string first, second;
    first = line.substr(0, pos);
    second = line.substr(pos+3);
    x = convertToMixedNumber(first);
    y = convertToMixedNumber(second);
}

void trim(string &line)
{
    while(line[0] == ' ')
        line.erase(0,1);
}

mixedNumber convertToMixedNumber(string line)
{
    stringstream ss;
    char junk;
    mixedNumber answer;
    trim(line);
    int pos = line.find(' '),
        pos2 = line.find('/');
    if(pos < string::npos && pos2 < string::npos) //have a true mixed number!
    {
        ss << line;
        ss>> answer.whole>>answer.num>>junk>>answer.denom;
    }
    else
        if(pos2 >= string::npos)
        {
            ss<<line;
            ss>>answer.whole;
            answer.num = 0;
            answer.denom = 1;
        }
        else
        {
            ss<<line;
            ss>>answer.num>>junk>>answer.denom;
            answer.whole = 0;
        }
    return answer;
}


char getOperator(string line, int &pos)
{
    string choices[5] = {" + ", " - ", " * ", " / ", " ^ "};
    for(int i = 0; i < 5; i++)
        if( (pos = line.find(choices[i])) < string::npos)
            break;
    return pos < string::npos ? line[pos+1] : '\0';
}


void process(string line)
{
    mixedNumber one, two, answer;
    int pos;
    char op = getOperator(line, pos);
    if(op == '\0')
    {
        cout<<"No operator found! Please re-etner"<<endl;
        return;
    }
    getOperands(line, one, two, pos);
    switch(op)
    {
        case '+' : answer = add(one, two);
                   break;

        case '-' : answer = subtract(one,two);
                   break;

        case '*' : answer = mult(one,two);
                   break;

        case '/' : answer = divide(one,two);
                   break;
        case '^' : answer = power(one,two);
                   break;
    }
    cout<<line<<" = ";
    answer.output();
    cout<<endl;
}

int gcd(int p, int q)
{
    return q==0 ? p : gcd(q, p%q);
}

void reduce(mixedNumber &number)
{
    int newNum = number.denom*number.whole + number.num,
        newDenom = number.denom,
        divisor = gcd(newNum,newDenom );
    newNum /= divisor;
    newDenom /= divisor;
    number.whole = newNum/newDenom;
    number.num = newNum %newDenom;
    number.denom = newDenom;
}

mixedNumber add(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;

    answer.whole = 0;
    if(x.whole < 0 && y.whole < 0)
    answer.num = y.denom*(x.denom*x.whole - x.num) +  x.denom*(y.denom*y.whole - y.num);
    else if(x.whole < 0)
    answer.num = y.denom*(x.denom*x.whole - x.num) +  x.denom*(y.denom*y.whole + y.num);
    else if(y.whole < 0)
    answer.num = y.denom*(x.denom*x.whole + x.num) +  x.denom*(y.denom*y.whole - y.num);
    else
    answer.num = y.denom*(x.denom*x.whole + x.num) +  x.denom*(y.denom*y.whole + y.num);

    answer.denom = x.denom * y.denom;
    reduce(answer);
    if(answer.whole < 0 )
        {
            answer.num = abs(answer.num);
            answer.denom = abs(answer.denom);
        }
    else if(answer.denom < 0 )
    {
        answer.num = -(answer.num);
        answer.denom = abs(answer.denom);
    }
    return answer;
}

mixedNumber mult(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    answer.whole = 0;
    if(x.whole < 0 && y.whole < 0)
    answer.num = (x.denom*x.whole - x.num) * (y.denom*y.whole - y.num);
    else if(x.whole < 0)
    answer.num = (x.denom*x.whole - x.num) * (y.denom*y.whole + y.num);
    else if(y.whole < 0)
    answer.num = (x.denom*x.whole + x.num) * (y.denom*y.whole - y.num);
    else
    answer.num = (x.denom*x.whole + x.num) * (y.denom*y.whole + y.num);

    answer.denom = x.denom * y.denom;
    reduce(answer);

    if(answer.whole < 0 )
        {
            answer.num = abs(answer.num);
            answer.denom = abs(answer.denom);
        }
    else if(answer.denom < 0 )
    {
        answer.num = -(answer.num);
        answer.denom = abs(answer.denom);
    }
    return answer;
}


mixedNumber divide(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    answer.whole = 0;
    answer.num = ((x.whole)> -1) ? (x.denom*x.whole + x.num) * y.denom : (x.denom*x.whole - x.num) ;
    answer.denom = ((y.whole)> -1) ? x.denom * (y.denom*y.whole + y.num) : x.denom * (y.denom*y.whole - y.num);

    reduce(answer);

    if(answer.whole < 0 )
        {
            answer.num = abs(answer.num);
            answer.denom = abs(answer.denom);
        }
    else if(answer.denom < 0 )
    {
        answer.num = -(answer.num);
        answer.denom = abs(answer.denom);
    }

    return answer;
}

mixedNumber subtract(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    answer.whole = 0;
    if(x.whole < 0 && y.whole < 0)
    answer.num = y.denom*(x.denom*x.whole - x.num) -  x.denom*(y.denom*y.whole - y.num);
    else if(x.whole < 0)
    answer.num = y.denom*(x.denom*x.whole - x.num) -  x.denom*(y.denom*y.whole + y.num);
    else if(y.whole < 0)
    answer.num = y.denom*(x.denom*x.whole + x.num) -  x.denom*(y.denom*y.whole - y.num);
    else
    answer.num = y.denom*(x.denom*x.whole + x.num) -  x.denom*(y.denom*y.whole + y.num);

    answer.denom = x.denom * y.denom;
    reduce(answer);
    if(answer.whole < 0 )
        {
            answer.num = abs(answer.num);
            answer.denom = abs(answer.denom);
        }
    else if(answer.denom < 0 )
    {
        answer.num = -(answer.num);
        answer.denom = abs(answer.denom);
    }

    return answer;
}

mixedNumber power(mixedNumber x, mixedNumber y)
{
    mixedNumber answer;
    double temp, temp2, dec;
    int hold;

    temp = pow(((x.denom*x.whole + x.num)),(y.denom*y.whole + y.num));
    temp2 = pow(x.denom, (y.denom*y.whole + y.num));
    dec = temp/temp2;
    hold = dec;
    dec = dec - hold;
    answer.whole = hold;
    answer.num = dec*pow(10,8);
    answer.denom = pow(10,8);
    reduce(answer);
    return answer;
}
