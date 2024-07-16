#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <stack>
#include <algorithm>

using namespace std;

//functions
bool checkIfMovieExist(string movID);
void movPrintables(string id, string title, string genre, string production, string copies);
void displayAllVideos(string id, string title, string genre, string production, string copies);
void updateMovieData(string id, string title, string genre, string production, string copies, string userInputId);
bool checkVideoAvailability(string numOfCopies);

void movieData::inputData(string userInput, string userInput2)
{
    queue<movieData> videoQueue;
    movieData data;

    int characters;
    int LastID = 0;

    string input;
    string movies;
    string chars;
    string data1;

    ifstream file("movies.txt");

    input = userInput;


    while (getline(file, movies)) {
        

        int numberOfDetection = 0;//counts the detector of the "|" separator
        int tempID = 9;
        characters = movies.length();

        movieData* data = new movieData;

        for (int i = 0; i < characters; i++) {
            
            chars = movies[i];
            if (chars == "|") {
                numberOfDetection++;
            }
            if (numberOfDetection == 0) {

                data->vidID += chars;

            }
            

            if (input == data->vidID && chars != "|") {

                switch (numberOfDetection) {
                case 1:
                    data->title += chars;//retrieves the title of the movie
                    break;
                case 2:
                    data->genre += chars;//retrieves the genre of the movie
                    break;
                case 3:
                    data->production += chars;//retrieves the production of the movie
                    break;
                case 4:
                    data->numOfCopies += chars;//retrieves the number of copies of the movie
                    
                    break;
                }
            }
            
        }
        
        if (userInput2 == "5") {//OPTION 5
            displayAllVideos(data->vidID, data->title, data->genre, data->production, data->numOfCopies);
            int inputToString = stoi(input) + 1;
            input = to_string(inputToString);
        
        }
        else  if (userInput2 == "4" && input == data->vidID || userInput2 == "6" && input == data->vidID) {//OPTION 4 AND 6
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
        here:
            cout << "Enter (Y) to continue: ";
            cin >> input;
            if (input == "Y" || input == "y") {
                return;
            }
            else {
                cout << "INVALID INPUT" << endl;
                goto here;
            }
        }
        else if (userInput2 == "2" && input == data->vidID) {//OPTION 2

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
        else if (userInput2 == "7" && input == data->vidID) {//OPTION 7
           
            cout << data->title << endl;

        }
        else if (userInput2 == "3" && input == data->vidID && numberOfDetection !=0) {//OPTION 3

            data->numOfCopies = to_string(stoi(data->numOfCopies) + 1);
            
            updateMovieData(data->vidID, data->title, data->genre, data->production, data->numOfCopies, userInput2);
            
        }
       
        
        
        if (data->vidID != "1") {
            int realID = stoi(data->vidID) - 1;
            data->vidID = to_string(realID);
        }
        LastID++;
        delete data;
    }
    
    if (userInput2 == "1") {//OPTION 1
       
        data.newVideo(videoQueue, LastID);
    }
}


//returns true of the video is available
bool checkVideoAvailability(string numOfCopies) {
    if (numOfCopies != "0") {
        return true;
    }
    else {
        return false;
    }
}
//PRINTS THE MOVIE DATA IN DETAILED FORM
void movPrintables(string id, string title, string genre, string production, string copies) {

    cout << "Video ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Production: " << production << endl;
    cout << "Number of Copies: " << copies << endl;

}
// DISPLAYS ALL VIDEOS
void displayAllVideos(string id, string title, string genre, string production, string copies) {

    cout << "Video ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Production: " << production << endl;
    cout << "Number of Copies: " << copies << endl;

}

//UPDATES THE NUMBER OF COPIES OF THE MOVIES IN THE TEXT FILE
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
            if (numberOfDetection == 0) {
                tempID += chars;
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



bool isInteger(const string& s) {
    try {
        size_t pos;
        int num = stoi(s, &pos);
        // Ensure that the whole string was used to convert to an integer
        return pos == s.length();
    }
    catch (invalid_argument& e) {
        // Catch invalid_argument exception if conversion is not possible
        return false;
    }
    catch (out_of_range& e) {
        // Catch out_of_range exception if the number is too large to fit in an int
        return false;
    }
}

//CHECKS IF THE USER EXIST AND PRINTS THE CUSTOMER DETAILS
void CustomerManager::cosPrintDetails(const string& userInput) {
    int lastID = 0;

    string tempInput = userInput;
    if (userInput != "findLastID") {
        cout << "Searching for customer with ID: " << userInput << endl;
    }
    queue<Customer> temp = customers;
    while (!temp.empty()) {

     if (userInput != "findLastID") {
        Customer customer = temp.front();


        string strippedStoredID = to_string(stoi(customer.cosID));


        string strippedInput = to_string(stoi(userInput));

        if (strippedInput == strippedStoredID) {
            cout << "Customer ID: " << strippedStoredID << endl;
            cout << "Customer Name: " << customer.cosName << endl;
            cout << "Customer Address: " << customer.cosAdd << endl << endl;
            return;
        }
        
     }
     else {
         lastID++;
     }
     temp.pop();
    }

    if (userInput == "findLastID") {
        newCustomers(lastID);
    }
    else if (userInput != "findLastID") {
        cerr << "Customer not found." << endl;
    }


}

string CustomerManager::generateID(int id) {
    return to_string(10000 + id).substr(1);
}

void CustomerManager::newCustomers1() {  
    cosPrintDetails("findLastID");
}

void CustomerManager::newCustomers(int custCount) {
    char choice;

    do {
        Customer newCustomer;
        newCustomer.cosID = generateID(++custCount);

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, newCustomer.cosName);
        cout << "Enter Address: ";
        getline(cin, newCustomer.cosAdd);

        customers.push(newCustomer);  // Add the new customer to the queue

        cout << "Customer Added: "<< newCustomer.cosID << "|" << newCustomer.cosName << "|" << newCustomer.cosAdd << endl;

        cout << "Do you want to add another customer? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}
         
// Function to save movie data to a text file
void movieData::saveToNotepad(const queue<movieData>& videoQueue, const string& filename) {
    ofstream file(filename, ios::app); // Open the file in append mode
    queue<movieData> tempQueue = videoQueue; // Create a copy of the queue

    // Write each movie data to the file
    while (!tempQueue.empty()) {
        movieData video = tempQueue.front();
        file << video.vidID << "|" << video.title << "|" << video.genre << "|"
            << video.production << "|" << video.numOfCopies << endl;
        tempQueue.pop();
    }
    file.close(); // Close the file
}

// Function to generate a unique ID for each movie
string movieData::generateID(int id) {
    return to_string(id); // Generate ID starting from 0001
}

// Function to add a new movie to the queue
void movieData::newVideo(queue<movieData>& videoQueue, int& videoCount) {
    char choice;
    
    do {
        movieData newVideo;
        newVideo.vidID = generateID(++videoCount); // Increment and assign video ID

        // Get movie details from the user
        cout << "Enter title: ";
        cin.ignore();
        getline(cin, newVideo.title);
        cout << "Enter genre: ";
        getline(cin, newVideo.genre);
        cout << "Enter production: ";
        getline(cin, newVideo.production);
        cout << "Enter number of copies: ";
        getline(cin, newVideo.numOfCopies);

        videoQueue.push(newVideo); // Add the new movie to the queue

        // Display the added movie details
        cout << "New Video Added: "
            << newVideo.vidID << "|"
            << newVideo.title << "|"
            << newVideo.genre << "|"
            << newVideo.production << "|"
            << newVideo.numOfCopies << endl;

        // Ask if the user wants to add another movie
        cout << "Do you want to add another video? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Save all movies in the queue to 'movies.txt'
    cout << "All videos in the queue saved to 'movies.txt': " << endl;
    saveToNotepad(videoQueue, "movies.txt");

    // Display all movies in the queue and clear it
    while (!videoQueue.empty()) {
        movieData video = videoQueue.front();
        videoQueue.pop();
        cout << video.vidID << "|" << video.title << "|" << video.genre << "|"
            << video.production << "|" << video.numOfCopies << endl;
    }
}
                
void CustomerManager::showCostumerDetails() {
    string input;
    cout << "Enter Costumer ID: ";
    cin >> input;
    cosPrintDetails(input);
    here:
    cout << "Enter (Y) to continue: ";
    cin >> input;
    if (input == "Y" || input == "y") {
        return;
    }
    else {
        cout << "INVALID INPUT" << endl;
        goto here;
    }
}
//SUBMENU
void CustomerManager::customerMaintenanceMenu() {

    int subMenu;
    do {
    here:
        cout << "===========================================\n";
        cout << "\t Customer Maintenance\n";
        cout << "===========================================\n";
        cout << "[1] Add New Customer\n";
        cout << "[2] Show Customer Details\n";
        cout << "[3] List of Videos Rented by a Customer\n";
        cout << "[4] Exit to Main Menu\n";
        cout << "===========================================\n";

        cin >> subMenu;

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid selection. Please enter a number between 1 and 4." << endl;
            continue; // Skip to the next iteration of the loop
        }


        switch (subMenu) {
        case 1:
            newCustomers1();
            break;
        case 2:
            showCostumerDetails();
            break;
        case 3:
            videoRentedByCustomer();
            break;
        case 4:
            cout << "Exiting to Main Menu..." << endl;
            break;
        default:
            cout << "Invalid selection. Please try again." << endl;
            break;
        }
    } while (subMenu != 4);
}

//READS CUSTOMER TEXT FILE AND INPUTS THE DATA INTO A QUEUE
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

//WRITES THE DATA FROM CUSTOMER QUEUE BACK TO THE CUSTOMER TEXT FILE
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

//APPENDS THE MOVIE ID NEXT TO THE CUSTOMER ID THAT ALREADY RENTING OR CREATE NEW LINE IN THE STACK
void CustomerManager::appendToRentalStack(string customerId, string movieId) {

    vector<string> lines;
    bool customerFound = false;
    bool movieAlreadyRented = false;

    // Copy stack to a vector for easier manipulation
    stack<string> tempStack = customerRental;
    while (!tempStack.empty()) {
        std::string line = tempStack.top();
        tempStack.pop();

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

    if (!customerFound) {
        // Append new line if customerId was not found
        lines.push_back(customerId + "|" + movieId);
    }
    else if (movieAlreadyRented) {
        cerr << "Movie already rented by this customer." << endl;
        return;
    }

    // Update the stack with the new contents
    customerRental = stack<string>();
    for (const string& updatedLine : lines) {
        customerRental.push(updatedLine);
    }
}

//CHECKS IF THE MOVIE EXIST
bool checkIfMovieExist(string movID) {
    ifstream file("movies.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << "movies/txt" << std::endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        // Extract the movID part from the line
        size_t delimiterPos = line.find('|');
        if (delimiterPos != std::string::npos) {
            string currentMovID = line.substr(0, delimiterPos);
            if (currentMovID == movID) {
                return true;
            }
        }
    }

    return false;


}

//LETS THE CUSTOMER RENT A MOVIE
void CustomerManager::rentMovie() {
    movieData md;

    string inputCos, inputMov, recur;

    cout << "Enter Customer ID: ";
    cin >> inputCos;
    cosPrintDetails(inputCos);

jump:
    cout << "Enter Movie ID: ";
    cin >> inputMov;
    if (movieAlreadyRented(inputCos, inputMov) == false) {

        try {
            if (checkIfMovieExist(inputMov)) {
                md.inputData(inputMov, "2");
                appendToRentalStack(inputCos, inputMov);
            }
            else {
                cout << "movie does not exist//or not availablle!!!" << endl<<endl;
                goto jump;
            }
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }
    else {
        md.inputData(inputMov, "4");
        cout << "movie is already rented!!" << endl;
    }
    //For Function Recursion
invalid:
    cout << "do you want to rent another movie?(Y/N)";
    cin >> recur;

    if (recur == "Y" || recur == "y") {
        goto jump;
    }
    else if (recur == "N" || recur == "n") {
        cout << "Thank you for renting from us!!" << endl;
    }
    else {
        cout << "Invalid Option!!" << endl;
        goto invalid;
    }
}

//CHECKS IF THE CUSTOMER ALREADY RENTED THE MOVIE
bool CustomerManager::movieAlreadyRented(string customerId, string movieId) {
    stack<string> tempStack = customerRental; // Using temporary stack to avoid modifying the original stack

    while (!tempStack.empty()) {
        string line = tempStack.top();
        tempStack.pop();

        stringstream ss(line);
        string fileCustomerId;
        getline(ss, fileCustomerId, '|');

        if (fileCustomerId == customerId) {
            string token;
            while (getline(ss, token, '|')) {
                if (token == movieId) {
                    return true; // Movie is rented by this customer
                }
            }
        }
    }
    return false;
}

//SHOWS LITS OF VIDEOS RENTED
void CustomerManager::videoRentedByCustomer() {
    movieData md; // Assuming movieData class is available and has inputData method

    string input;
    string rentedMovies;
    string chars;
    string idRentedByCustomer;

    cout << "Enter Customer ID: ";
    cin >> input;

    cosPrintDetails(input);

    cout << "List of Videos Rented: " << endl;

    stack<string> tempStack = customerRental; // Using temporary stack to read data

    while (!tempStack.empty()) {
        rentedMovies = tempStack.top();
        tempStack.pop();

        stringstream ss(rentedMovies);
        string fileCustomerId;
        getline(ss, fileCustomerId, '|');

        if (fileCustomerId == input) {
            string token;
            while (getline(ss, token, '|')) {
                if (idRentedByCustomer != token) {
                    md.inputData(token, "7"); // Add movie ID to movieData
                    idRentedByCustomer = token; // Update last rented movie ID
                }
            }
        }
    }
}

//RETURNS THE MOVIE RENTED BY CUSTOMER
void CustomerManager::returnRentedVideo() {
    movieData md;

    string userInput;
    cout << "Enter Customer ID: ";
    cin >> userInput;

    if (!isInteger(userInput)) { //checks if its convertible to int
        cout << "Please input a valid number!" << endl;
        returnRentedVideo();
    }
    else {
        cosPrintDetails(userInput);
    }
    

    stack<string> tempStack = customerRental; // Use a temporary stack to process data
    vector<string> updatedLines; // To store the lines for the updated stack
    vector<string> rentedMovies; // To store rented movies for processing
    bool customerFound = false;

    while (!tempStack.empty()) {
        string line = tempStack.top();
        tempStack.pop();

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
            // Do not add this line to the updatedLines vector to effectively remove it
            continue;
        }

        updatedLines.push_back(line);
    }

    if (!customerFound) {
        cerr << "No movies found for the given Customer ID." << endl;
        return;
    }

    // Process each movie ID and call inputData
    for (const string& movieId : rentedMovies) {
        cout << "Returned movie: " << movieId << endl;
        md.inputData(movieId, "3");
    }

    // Clear the stack and re-populate it with updated lines
    customerRental = stack<string>();
    for (const string& updatedLine : updatedLines) {
        customerRental.push(updatedLine);
    }
}

bool compareByCustomerId(const string& line1, const string& line2) {
    stringstream ss1(line1);
    stringstream ss2(line2);
    string customerId1, customerId2;
    getline(ss1, customerId1, '|');
    getline(ss2, customerId2, '|');
    return customerId1 < customerId2;
}

void quicksortMovieIds(vector<string>& movieIds, int left, int right) {
    if (left < right) {
        // Partitioning
        string pivot = movieIds[left + (right - left) / 2];
        int i = left - 1;
        int j = right + 1;

        while (true) {
            do {
                i++;
            } while (movieIds[i] < pivot);

            do {
                j--;
            } while (pivot < movieIds[j]);

            if (i >= j)
                break;

            swap(movieIds[i], movieIds[j]);
        }

        // Recursively sort two partitions
        quicksortMovieIds(movieIds, left, j);
        quicksortMovieIds(movieIds, j + 1, right);
    }
}

void quicksort(vector<string>& lines, int left, int right) {
    if (left < right) {
        // Partitioning
        string pivot = lines[left + (right - left) / 2];
        int i = left - 1;
        int j = right + 1;

        while (true) {
            do {
                i++;
            } while (compareByCustomerId(lines[i], pivot));

            do {
                j--;
            } while (compareByCustomerId(pivot, lines[j]));

            if (i >= j)
                break;

            swap(lines[i], lines[j]);
        }

        // Recursively sort two partitions
        quicksort(lines, left, j);
        quicksort(lines, j + 1, right);
    }
}


//Reads the rental.txt file and feeds the data into a stack
void CustomerManager::readCustomerRental() {
    string line;
    ifstream file("rental.txt");

    if (!file.is_open()) {
        cerr << "Error: Could not open file rental.txt" << endl;
        return;
    }

    while (std::getline(file, line)) {
        customerRental.push(line);
    }
    file.close();
}

//writes the customer rental stack back into the text file
void CustomerManager::writeCustomerRental() {
    ofstream file("rental.txt");

    if (!file.is_open()) {
        cerr << "Error: Could not open file rental.txt for writing" << endl;
        return;
    }

    // Collect lines from the stack into a vector
    stack<string> tempStack = customerRental;
    vector<string> lines;

    while (!tempStack.empty()) {
        lines.push_back(tempStack.top());
        tempStack.pop();
    }

    // Process each line to sort movie IDs and sort lines based on customer ID
    vector<string> processedLines;

    for (string& line : lines) {
        stringstream ss(line);
        string customerId;
        getline(ss, customerId, '|'); // Extract customer ID

        vector<string> movieIds;
        string movieId;
        while (getline(ss, movieId, '|')) {
            movieIds.push_back(movieId);
        }

        // Sort movie IDs using quicksort
        quicksortMovieIds(movieIds, 0, movieIds.size() - 1);

        // Reconstruct the line
        stringstream newLine;
        newLine << customerId;
        for (const string& sortedMovieId : movieIds) {
            newLine << "|" << sortedMovieId;
        }
        processedLines.push_back(newLine.str());
    }

    // Sort lines based on customer ID using quicksort
    quicksort(processedLines, 0, processedLines.size() - 1);

    // Write sorted and updated lines back to the file
    for (const string& line : processedLines) {
        file << line << endl;
    }

    file.close();
}

