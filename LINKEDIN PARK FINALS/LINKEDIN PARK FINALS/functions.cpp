#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <stack>

using namespace std;

//functions
void newVideo();
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
        else  if (userInput2 == "4" && input == data->vidID || userInput2 == "6" && input == data->vidID) {
           // cout << input << " INPUT";
            movPrintables(data->vidID, data->title, data->genre, data->production, data->numOfCopies);
           // cout << data->vidID << " INPUT VID ID";
            if (userInput2 == "6") {
                if (checkVideoAvailability(data->numOfCopies)) {
                    cout << "Availability: Available" << endl;
                }
                else {
                    cout << "Availability: Unavailable" << endl;
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
        else if (userInput2 == "7" && input == data->vidID) {
           
            cout << data->title << endl;

        }
        else if (userInput2 == "3" && input == data->vidID) {
            data->numOfCopies = to_string(stoi(data->numOfCopies) + 1);
            updateMovieData(data->vidID, data->title, data->genre, data->production, data->numOfCopies, userInput2);
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
            string temp = to_string(10000 + stoi(id)).substr(1);
            line = temp + "|" + title + "|" + genre + "|" + production + "|" + copies;
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
void CustomerManager::readCustomers() {
    string filename = "customers.txt";
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Customer cust;
            stringstream ss(line);
            string token;

            // Read ID (assumed to be the first token before '|')
            getline(ss, token, '|');
            cust.cosID = token; 
            cust.cosID.erase(0, min(cust.cosID.find_first_not_of('0'), cust.cosID.size() - 1));
            // Read rest of the line as name (after '|')
            getline(ss, cust.cosName, '|');

            getline(ss, cust.cosAdd, '|');

            customers.push(cust);
        }
        file.close();
        
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}

void CustomerManager::writeCustomersToFile() {
    string filename = "customers.txt";
    ofstream file(filename, ios::trunc); // Ensures that all data is deleted before inserting the contents of the queue
    if (file.is_open()) {
        while (!customers.empty()) {
            Customer cust = customers.front();

            // Format cosID with leading zeros
            file << setw(4) << setfill('0') << cust.cosID << "|"
                << cust.cosName << "|"
                << cust.cosAdd << endl;

            customers.pop();
        }
        file.close();
        cout << "Customer data successfully saved to file." << endl;
    }
    else {
        cout << "Unable to open file " << filename << " for writing." << endl;
    }
}

void CustomerManager::cosPrintDetails(const std::string& userInput) {
    
    cout << "Searching for customer with ID: " << userInput << endl;

    queue<Customer> temp = customers;
    while (!temp.empty()) {
        Customer customer = temp.front();

        
        string strippedStoredID = to_string(stoi(customer.cosID));

        
        string strippedInput = to_string(stoi(userInput));

        if (strippedInput == strippedStoredID) {
            cout << "Customer ID: " << strippedStoredID << endl;
            cout << "Customer Name: " << customer.cosName << endl;
            cout << "Customer Address: " << customer.cosAdd << endl<<endl;
            return;
        }
        temp.pop();
    }
    cerr << "Customer not found." << endl;
}


void RentedManager::appendToRentalFile(string customerId, string movieId) {

    string rentalFilename = "rental.txt";
    fstream file(rentalFilename, ios::in | ios::out);
    vector<string> lines;
    string line;

    if (!file) {
        cerr << "Unable to open rental file." << endl;
        return;
    }

    bool customerFound = false;
    bool movieAlreadyRented = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string fileCustomerId;
        getline(ss, fileCustomerId, '|');

        if (fileCustomerId == customerId) {
            customerFound = true;

            // Check if movieId is already rented by the customer
            string token;
            while (getline(ss, token, '|')) {
                if (token == movieId) {
                    movieAlreadyRented = true;
                    break;
                }
            }

            if (!movieAlreadyRented) {
                // Append movieId to the existing line if not already rented
                line += "|" + movieId;
            }
        }
        lines.push_back(line); // Store line in vector
    }

    file.close();

    if (!customerFound) {
        // Append new line if customerId was not found
        lines.push_back(customerId + "|" + movieId);
    }
    else if (movieAlreadyRented) {
        cerr << "Movie already rented by this customer." << endl;
        return;
    }

    // Write updated content back to the file
    ofstream outFile(rentalFilename);
    for (const string& updatedLine : lines) {
        outFile << updatedLine << endl;
    }
    outFile.close();
}




void CustomerManager::rentMovie() {
    RentedManager rm;
    string inputCos, inputMov, recur;
    
    cout << "Enter Customer ID: ";
    cin >> inputCos;
    CustomerManager::cosPrintDetails(inputCos);

    jump:
    cout << "Enter Movie ID: ";
    cin >> inputMov;
    if (rm.movieAlreadyRented(inputCos, inputMov)==false) {
        try {
            inputData(inputMov, "2");
            rm.appendToRentalFile(inputCos, inputMov);
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }
    else {
        inputData(inputMov, "4");
        cout << "movie is already rented!!" << endl;
    }
    //For Function Recursion
    invalid:
    cout << "do you want to rent another movie?(Y/N)";
    cin >> recur;

    if (recur == "Y" || recur == "y") {
        goto jump;
    }
    else if(recur == "N" || recur == "n") {
        cout << "Thank you for renting from us!!"<<endl;
    }else {
        cout << "Invalid Option!!" << endl;
        goto invalid;
    }
}

bool RentedManager::movieAlreadyRented(string customerId, string movieId) {
    string line;
    ifstream file("rental.txt");
    while (getline(file, line)) {
        stringstream ss(line);
        string fileCustomerId;
        getline(ss, fileCustomerId, '|');
        if (fileCustomerId == customerId) {
            string token;
            while (getline(ss, token, '|')) {
                if (token == movieId) {
                    return true;
                }
            }
        }
    }
    return false;
}

void CustomerManager::videoRentedByCustomer() {
    ifstream file("rental.txt");

    int characters;

    string input;
    string rentedMovies;
    string chars;
    string data1;
    string idRentedByCustomer;
    
    
    cout << "Enter Customer ID: ";
    cin >> input;
    cosPrintDetails(input);


    cout << "List of Videos Rented: " << endl;

    while (getline(file, rentedMovies)) {
        int numberOfDetection = 0;
        
        int temp;
        string tempID;
        
       
        characters = rentedMovies.length();
        movieData* data = new movieData;

         

        for (int i = 0; i < characters; i++) {

            chars = rentedMovies[i];

            if (chars == "|") {
                numberOfDetection++;
            }
            if (chars != "0" && numberOfDetection == 0) {
                //add the id from chars
                tempID = chars;
                }
                
            //check Customer ID
            if (input == tempID && numberOfDetection != 0 && chars != "|") {
                //detect if Movie ID was repeated
                if (idRentedByCustomer == chars) {
                    temp++;
                }
                else if (idRentedByCustomer != chars) {
                    temp = 0;
                }
                idRentedByCustomer = chars;
                
                if (temp == 0) {
                    inputData(idRentedByCustomer, "7");
                }
                
            }
        }
    }
}

void CustomerManager::returnRentedVideo() {
    string userInput;
    

    cout << "Enter Customer ID: ";
    cin >> userInput;
    cosPrintDetails(userInput);

    ifstream file("rental.txt");
    if (!file) {
        cerr << "Unable to open rental file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    vector<string> rentedMovies;
    bool customerFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string segment;
        vector<string> segments;
        while (getline(ss, segment, '|')) {
            segments.push_back(segment);
        }

        if (segments[0] == userInput) {
            customerFound = true;
            for (size_t i = 1; i < segments.size(); ++i) {
                rentedMovies.push_back(segments[i]);
            }
            // Do not add this line to the lines vector to effectively remove it
            continue;
        }

        lines.push_back(line);
    }
    file.close();

    if (!customerFound) {
        cerr << "No movies found for the given Customer ID." << endl;
        return;
    }

    // Process each movie ID and call inputData
    for (const string& movieId : rentedMovies) {
        cout << "Returned movie: " << movieId << endl;
        inputData(movieId, "3");
    }

    // Write updated content back to the file without the customer's record
    ofstream outFile("rental.txt");
    for (const string& updatedLine : lines) {
        outFile << updatedLine << endl;
    }
    outFile.close();
}

string CustomerMaintenance::generateID(int id) {
    return to_string(10000 + id).substr(1);
}

void CustomerMaintenance::saveToNotepad(const stack<Customer>& customers, const string& filename) {
    ofstream file(filename);
    stack<Customer> tempStack = customers;

    while (!tempStack.empty()) {
        Customer cust = tempStack.top();
        file << cust.cosID << "|" << cust.cosName << "|" << cust.cosAdd << endl;
        tempStack.pop();
    }

    file.close();
}

void CustomerMaintenance::newCustomers() {
    stack<Customer> customerStack;
    int custCount = 0;
    char choice;

    do {
        Customer newCustomer;
        newCustomer.cosID = generateID(++custCount);

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, newCustomer.cosName);
        cout << "Enter Address: ";
        getline(cin, newCustomer.cosAdd);

        customerStack.push(newCustomer);

        cout << "Customer Added: "
            << newCustomer.cosID << "|"
            << newCustomer.cosName << "|"
            << newCustomer.cosAdd << endl;

        cout << "Do you want to add another customer? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "All customers in the stack: " << endl;
    saveToNotepad(customerStack, "deets.txt");

    while (!customerStack.empty()) {
        Customer cust = customerStack.top();
        customerStack.pop();
        cout << cust.cosID << "|" << cust.cosName << "|" << cust.cosAdd << endl;
    }
}
         

                

               
            

