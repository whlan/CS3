#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    char coeff;
    string line, token;
    stringstream ss;
    cin>>line;
    ss<<line;
    ss>>token>>coeff;
    cout<<"this is token: "<<token<<"this is coeff: "<<coeff<<endl;
    return 0;
}

