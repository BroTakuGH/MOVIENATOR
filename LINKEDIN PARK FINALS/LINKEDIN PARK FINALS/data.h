#pragma once

#include <string>

using std::string;
void costumerPrintables(string ID, string Name, string Address);
void rentMovie();
void movInputData(string userInput, string userInput2);
void cosPrintDetails(string userInput);




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
    string cosRentedMov;
};
