#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"

using namespace std;

int main()
{
    CustomerManager cm;
    cm.readCustomerRental();
    cm.readCustomers();
    int videoCount = 0;
    int choice;
    int input;

    string input1;
    string input2;
    movieData data;

    here:

    cout << "===========================================\n";
    cout << "\t\t TITLE\n";
    cout << "===========================================\n";
    cout << "[1] New Video\n";
    cout << "[2] Rent a Video\n";
    cout << "[3] Return a Video\n";
    cout << "[4] Show Video Details\n";
    cout << "[5] Display all Videos\n";
    cout << "[6] Check Video Availability\n";
    cout << "[7] Customer Maintenance\n";
    cout << "[8] Exit Program\n";
    cout << "===========================================\n";

    cin >> input;

    switch (input) {
    case 1:
        data.inputData("1", "1");
        goto here;
        break;
    case 2:
        cm.rentMovie();
        goto here;
        break;
    case 3:
        cm.returnRentedVideo();
        goto here;
        break;
    case 4:
        cout << "Enter Movie ID: ";
        cin >> input2;

        data.inputData(input2, to_string(input));

        goto here;
        break;
    case 5:
            
        data.inputData("1", to_string(input));
    here1:
        cout << "Enter (Y) to continue: ";
        cin >> input1;
        if (input1 == "Y" || input1 == "y") {
            goto here;
        }
        else {
            cout << "INVALID INPUT" << endl;
            goto here1;
        }
        break;
    case 6:
        cout << "Enter Movie ID: ";
        cin >> input2;
        data.inputData(input2, to_string(input));
        goto here;
        break;
    case 7:
        cm.customerMaintenanceMenu();
        goto here;
        break;
    case 8:
        cm.writeCustomersToFile();
        cm.writeCustomerRental();
        break;
    default:cout<<"INVALID INPUT" << endl;
        goto here;
    }
}



