#pragma once

#include <string>
#include <queue>
#include <stack>

using namespace std;



struct movieData {

    string vidID;
    string title;
    string genre;
    string production;
    string numOfCopies;

    void saveToNotepad(const queue<movieData>& videoQueue, const string& filename);
    string generateID(int id);
    void newVideo(queue<movieData>& videoQueue, int& videoCount);
    void inputData(string userInput, string userInput2);

};

class CustomerManager {
private:
     

public:
    struct Customer {
        string cosID;
        string cosName;
        string cosAdd;
    };

    queue <Customer> customers;// Queue to store customers

    void writeCustomersToFile();
    void readCustomers();
    void cosPrintDetails(const std::string& userInput);
    void rentMovie();
    void returnRentedVideo();
    void videoRentedByCustomer();
    string generateID(int id);
    void newCustomers();
    void printCustomers();
    
};

class RentedManager {
private:
    CustomerManager cm;
public:

    void appendToRentalFile(string customerId, string movieId);
    bool movieAlreadyRented(string customerId, string movieId);
};





