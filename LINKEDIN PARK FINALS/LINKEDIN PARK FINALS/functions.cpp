#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"
#include <vector>
using namespace std;

void movPrintables(string id, string title, string genre, string production, string copies);
void displayAllVideos(string id, string title, string genre, string production, string copies);
void updateMovieData(string id, string title, string genre, string production, string copies, string userInputId);
bool checkVideoAvailability(string numOfCopies);

void inputData(string userInput, string userInput2)
{

    int characters;

    string input;
    string movies;
    string chars;
    string data1;

    ifstream file("movies.txt");

    input = userInput;


    while (getline(file, movies)) {
        int numberOfDetection = 0;
        characters = movies.length();
        movieData* data = new movieData;

        for (int i = 0; i < characters; i++) {
            
            chars = movies[i];
            if (chars == "|") {
                numberOfDetection++;
            }
            if (chars != "0" && numberOfDetection == 0) {
               
                data->vidID = chars;
            }
            

            if (input == data->vidID && chars != "|") {

                switch (numberOfDetection) {
                case 1:
                    data->title += chars;
                    break;
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
            }
            
        }
        if (userInput2 == "5") {
            displayAllVideos(data->vidID, data->title, data->genre, data->production, data->numOfCopies);
            int inputToString = stoi(input) + 1;
            input = to_string(inputToString);
        }
        else  if (userInput2 == "4" || userInput2 == "6" && input == data->vidID) {
            movPrintables(data->vidID, data->title, data->genre, data->production, data->numOfCopies);
            
            if (userInput2 == "6") {
                if (checkVideoAvailability(data->numOfCopies)) {
                    cout << "Availability: Available";
                }
                else {
                    cout << "Availability: Unavailable";
                }
            }
        }
        else if (userInput2 == "2" && input == data->vidID) {

      
            
            if (stoi(data->numOfCopies) != 0)
            {
                
                data->numOfCopies = to_string(stoi(data->numOfCopies) - 1);
                updateMovieData(data->vidID, data->title, data->genre, data->production, data->numOfCopies, userInput2);
               
                movPrintables(data->vidID, data->title, data->genre, data->production, data->numOfCopies);
            }
            else {
                cout << "Movie Not Available";
            }
        }
        if (data->vidID != "1") {
            int realID = stoi(data->vidID) - 1;
            data->vidID = to_string(realID);
        }
        
        delete data;
    }
   
  
}

bool checkVideoAvailability(string numOfCopies) {
    if (numOfCopies != "0") {
        return true;
    }
    else {
        return false;
    }
}

void movPrintables(string id, string title, string genre, string production, string copies) {
    cout << "Video ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Production: " << production << endl;
    cout << "Number of Copies: " << copies << endl;
}

void displayAllVideos(string id, string title, string genre, string production, string copies) {
    cout << "Video ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Production: " << production << endl;
    cout << "Number of Copies: " << copies << endl;
}

void costumerPrintables(string ID, string Name, string Address) {
    cout << "ID: " << ID << endl;
    cout << "Name: " << Name << endl;
    cout << "Address: " << Address << endl;
}

void updateMovieData(string id, string title, string genre, string production, string copies, string userInputId) {
    ifstream file("movies.txt");
    vector<string> lines;
    string movies;
    string chars;
    string line;
    while (getline(file, movies)) {
        int characters = movies.length();
        int numberOfDetection = 0;

        string tempID;

        for (int i = 0; i < characters; i++) {
            chars = movies[i];
            if (chars == "|") {
                numberOfDetection++;
            }
            if (chars != "0" && numberOfDetection == 0) {
                tempID = chars;
            }
                line += chars;
        }
        
        if (id == tempID) {
            line = id + "|" + title + "|" + genre + "|" + production + "|" + copies;
        }
        lines.push_back(line);
        line = {""};
        }
    
    

    ofstream outFile("movies.txt");
    for (const auto& l : lines) {
        outFile << l << endl;
    }

            file.close();

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

void appendToRentalFile(string customerId, string movieId) {
    string rentalFilename = "rental.txt";
    fstream file(rentalFilename, ios::in | ios::out);

    if (!file) {
        cerr << "Unable to open rental file." << endl;
        return;
    }

    string line;
    streampos prevPos = file.tellg();
    bool customerFound = false;

    while (getline(file, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos) {
            string fileCustomerId = to_string(stoi(line.substr(0, delimiterPos)));
            if (fileCustomerId == customerId) {
                file.seekp(prevPos + streamoff(line.size()));
                file << "|" << movieId;
                customerFound = true;
                break;
            }
        }

        prevPos = file.tellg();
    }

    if (!customerFound) {
        file.clear();
        file.seekp(0, ios::end);
        file << customerId << "|" << movieId << endl;
    }

    file.close();
}

void rentMovie() {
    string inputCos, inputMov, recur;
    

    cout << "Enter Customer ID: ";
    cin >> inputCos;
    cosPrintDetails(inputCos);
    jump:
    cout << "Enter Movie ID: ";
    cin >> inputMov;

    try {
        inputData(inputMov, "2");
        appendToRentalFile(inputCos, inputMov);
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    //For Function Recursion
    cout << "do you want to rent another movie?(Y/N)";
    cin >> recur;

    if (recur == "Y") {
        goto jump;
    }
    else {
        cout << "Thank you for renting from us!!";
    }
}

