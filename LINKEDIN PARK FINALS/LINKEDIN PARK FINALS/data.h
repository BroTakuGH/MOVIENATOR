#pragma once

#include <string>

using std::string;

string inputData(string userInput);

struct movieData {

    string vidID;
    string title;
    string genre;
    string production;

};

struct costumerData {
    
    string cosId;
    string cosName;
    string cosAdd;

    struct costumerRent {
        string cosRent;
    };
};
