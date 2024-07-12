#pragma once

#include <string>
#include <queue>

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
    
};

class RentedManager {
private:
    CustomerManager cm;
public:
    void returnRentedVideo();
    void videoRentedByCustomer();
    bool movieAlreadyRented(string customerId, string movieId);
};

