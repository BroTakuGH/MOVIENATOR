#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"
using namespace std;

string inputData(string userInput)
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
                }
            }
        }
        
    }
    cout << "Video ID: " << input << endl;
    cout << "Title: " << data.title << endl;
    cout << "Genre: " << data.genre << endl;
    cout << "Production: " << data.production << endl;

    return 0;
}