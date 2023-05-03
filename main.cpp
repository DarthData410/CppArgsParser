/// file: main.cpp
/// author: J. Brandon George | darth.data410@gmail.com | @pyfryday
/// This file showcases the ability to detect arguments passed into a C/C++ app
/// and convert them to a specific C-Type for usage.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdlib>

using namespace std;

bool is_bool(string str)
{
    bool b = false;
    transform(str.begin(), str.end(), str.begin(),
    [](unsigned char c){ return tolower(c); });
    if (str.rfind("true", 0) == 0 || str.rfind("false", 0) == 0) {
        b = true;
    }

    return b;
}

template<typename Numeric>
bool is_numeric(const std::string& str)
{
    Numeric n;
    return((istringstream(str) >> n >> ws).eof());
}

bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

int main(int argc, const char* argv[])
{
    vector<string> argvs;
    string sarg;

    if(argc<=2) {
        cout << " exepected usage: " << argv[0] << " --arg arg_value" << endl;
        return 1;
    }
    else {
        for(int i=0;i<argc;i++) {
            sarg = argv[i];
            if(sarg.find("--",0)==0) {
                sarg = sarg.substr(2, string::npos);
            }
            argvs.push_back(sarg);
        }
    }

    for (size_t idx = 1; idx < argvs.size(); idx += 2)
    {
        // arg: idx
        cout << "Processing: " << argvs[idx] << endl;

        // arg value: idx+1
        string v = argvs[idx+1];
        if(std::isalpha(v[0])) {
            // string or bool:
            if(is_bool(v)) {
                bool bv = to_bool(v);
                cout << "bool value of: " << bv << endl;
            }
            else {
                
                // pure string value for passed argument
                cout << "pure string of: " << v << endl;
            }
        }
        else {
            // int,float,double:
            if(is_numeric<int>(v))
            {
                cout << "is int: " << v << endl;
            }
            else if(is_numeric<float>(v))
            {
                cout << "is float: " << v << endl;
            }
            else {
                // catch all base node / string:
                cout << "is base string: " << v << endl;
            }
        }
    }

    return 0;
}