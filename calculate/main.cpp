#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include "term.h"
#include "mixednumber.h"
#include "expression.h"

using namespace std;

int main()
{
    string A = "3X^2";
    expression b;
    b<<A;

    return 0;
}

