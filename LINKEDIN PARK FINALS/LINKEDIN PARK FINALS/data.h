#pragma once

#include <string>
#include <queue>
#include <stack>

using namespace std;

void inputData(string userInput, string userInput2);

struct movieData {

    string vidID;
    string title;
    string genre;
    string production;
    string numOfCopies;
    
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
    
};

class RentedManager {
private:
    CustomerManager cm;
public:

    void appendToRentalFile(string customerId, string movieId);
    bool movieAlreadyRented(string customerId, string movieId);
};

using namespace std;

class CustomerMaintenance {
private:
    struct Customer {
        string cosID;
        string cosName;
        string cosAdd;
    };
public:
    void newCustomers();
    void saveToNotepad(const stack<Customer>& customers, const string& filename);
    string generateID(int id);
    
};


