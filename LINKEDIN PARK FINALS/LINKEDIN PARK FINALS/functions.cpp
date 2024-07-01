#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"
using namespace std;

void movPrintables(string id, string title, string genre, string production);

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
            if (chars != "0" && numberOfDetection == 0 && chars == input) {
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
                }
            }
        }
        
    }
    if (userInput2 == "4") {
        movPrintables(data.vidID, data.title, data.genre, data.production);
    }
    
}

void movPrintables(string id, string title, string genre, string production) {
    cout << "Video ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Production: " << production << endl;
}