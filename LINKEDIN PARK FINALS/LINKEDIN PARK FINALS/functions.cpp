#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"
using namespace std;

void movPrintables(string id, string title, string genre, string production, string copies);

void inputData(string userInput, string userInput2)
{

    int characters;

    string input;
    string movies;
    string chars;

    string data1;

    movieData data;
    ifstream file("movies.txt");

    input = userInput;


    while (getline(file, movies)) {
        int numberOfDetection = 0;
        characters = movies.length();

        for (int i = 0; i < characters; i++) {
            chars = movies[i];
            if (chars == "|") {
                numberOfDetection++;
            }
            if (chars != "0" && numberOfDetection == 0) {
               
                data.vidID = chars;
            }
            

            if (input == data.vidID && chars != "|") {

                switch (numberOfDetection) {
                case 1:
                    data.title += chars;
                    break;
                case 2:
                    data.genre += chars;
                    break;
                case 3:
                    data.production += chars;
                    break;
                case 4:
                    data.numOfCopies += chars;
                    break;
                }
            }
           
        }
        if (data.vidID != "1") {
            int realID = stoi(data.vidID) - 1;
            data.vidID = to_string(realID);
        }
    }
    if (userInput2 == "4") {
        movPrintables(data.vidID, data.title, data.genre, data.production, data.numOfCopies);
    }
    
}

void movPrintables(string id, string title, string genre, string production, string copies) {
    cout << "Video ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Production: " << production << endl;
    cout << "Number of Copies: " << copies << endl;
}