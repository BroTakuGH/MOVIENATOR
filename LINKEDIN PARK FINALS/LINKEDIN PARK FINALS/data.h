#pragma once

#include <string>

using std::string;

void inputData(string userInput, string userInput2);
void rentMovie();
struct movieData {

    string vidID;
    string title;
    string genre;
    string production;
    string numOfCopies;
    
};

struct costumerData {

    string cosID;
    string cosName;
    string cosAddress;

};

