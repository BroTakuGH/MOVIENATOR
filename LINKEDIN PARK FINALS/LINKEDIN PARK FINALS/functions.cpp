#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "data.h"
using namespace std;

void movPrintables(string id, string title, string genre, string production, string copies);
void displayAllVideos(string id, string title, string genre, string production, string copies);


void costumerPrintables(string ID, string Name, string Address) {
    cout << "ID: " << ID << endl;
    cout << "Name: " << Name << endl;
    cout << "Address: " << Address << endl;
}

void movPrintables(string id, string title, string genre, string production, string copies) {
    cout << "Video ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Production: " << production << endl;
    cout << "Number of Copies: " << copies << endl;
}

movieData getMovieDataById(const string& userInput) {
    int characters;
    string movies;
    string chars;
    string data1;


    movieData data;
    ifstream file("movies.txt");

    while (getline(file, movies)) {
        movieData* data = new movieData;
        int numberOfDetection = 0;
        characters = movies.length();

        for (int i = 0; i < characters; i++) {
            
            chars = movies[i];
            if (chars == "|") {
                numberOfDetection++;
            if (chars != "0" && numberOfDetection == 0) {
               
                data->vidID = chars;
               
            

            if (input == data->vidID && chars != "|") {

            

                    
                case 1:
                    data->title += chars;
                    
                case 2:
                    data->genre += chars;
                    break;
                case 3:
                    data->production += chars;
                    break;
                case 4:
                    data->numOfCopies += chars;
                    break;
            
            
    }

    throw invalid_argument("Movie ID not found.");
}

void updateMovieData(const movieData& updatedData) {
    ifstream file("movies.txt");
    vector<string> lines;
    string movies;
    string chars;

    while (getline(file, movies)) {
        int characters = movies.length();
        int numberOfDetection = 0;
        string line;
        movieData data;

        for (int i = 0; i < characters; i++) {
            chars = movies[i];
            if (chars == "|") {
                numberOfDetection++;
                line += chars;
                continue;
            }

            if (numberOfDetection == 0) {
                data.vidID += chars;
            }
            else if (numberOfDetection == 1) {
                data.title += chars;
            }
            else if (numberOfDetection == 2) {
                data.genre += chars;
            }
            else if (numberOfDetection == 3) {
                data.production += chars;
            }
            else if (numberOfDetection == 4) {
                data.numOfCopies += chars;
            }

            line += chars;
        }

        if (data.vidID == updatedData.vidID) {
            line = updatedData.vidID + "|" + updatedData.title + "|" + updatedData.genre + "|" + updatedData.production + "|" + updatedData.numOfCopies;
        }
        lines.push_back(line);
    }

    ofstream outFile("movies.txt");
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    file.close();
}

void movInputData(string userInput, string userInput2) {
    try {
        movieData data = getMovieDataById(userInput);

        if (userInput2 == "2" || userInput2 == "4") {
            movPrintables(data.vidID, data.title, data.genre, data.production, data.numOfCopies);
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}

void cosPrintDetails(string userInput) {
    int characters;
    string costumer;
    string chars;
    costumerData data;
    ifstream file("costumers.txt");

    while (getline(file, costumer)) {
        int numberOfDetection = 0;
        characters = costumer.length();
        data = {};  // Reset data for each costumer line

        for (int i = 0; i < characters; i++) {
            chars = costumer[i];
            if (chars == "|") {
                numberOfDetection++;
                continue;
            }

            if (chars != "0" && numberOfDetection == 0) {
                data.cosID += chars;
            }

            if (userInput == data.cosID && chars != "|") {
                switch (numberOfDetection) {
                case 1:
                    data.cosName += chars;
                    break;
                case 2:
                    data.cosAddress += chars;
                    break;
                }
            }
        }

        if (data.cosID == userInput) {
            costumerPrintables(data.cosID, data.cosName, data.cosAddress);
            return;
        }
    }
    }
    
void rentMovie() {
    string userInput, input2;

    cout << "Enter Customer ID: ";
    cin >> userInput;
    cosPrintDetails(userInput);

    cout << "Enter Movie ID: ";
    cin >> input2;

    try {
        movieData data = getMovieDataById(input2);

        // Print movie details before update
        cout << "Movie details before update:" << endl;
        movPrintables(data.vidID, data.title, data.genre, data.production, data.numOfCopies);

        if (stoi(data.numOfCopies) > 0) {
            data.numOfCopies = to_string(stoi(data.numOfCopies) - 1);

            // Print updated movie details
            cout << "Movie rented successfully. Updated details:" << endl;
            movPrintables(data.vidID, data.title, data.genre, data.production, data.numOfCopies);

            // Update the movie data in the file
            updateMovieData(data);
        }
        else {
            cout << "No copies available for rent." << endl;
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}


    cout << "Number of Copies: " << copies << endl;
}