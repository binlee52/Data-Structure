#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// split string
vector<string> split(string str, char delimiter) 
{
    vector<string> internal;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, delimiter)) 
        internal.push_back(temp);

    return internal;
}