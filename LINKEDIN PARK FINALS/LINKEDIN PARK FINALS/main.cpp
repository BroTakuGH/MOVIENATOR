#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "data.h"


void customerMaintenanceMenu();

using namespace std;



int main()
{
    CustomerManager cm;
   
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
        //data.newVideo(videoQueue, videoCount);
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
        cout << endl << "Continue? (Y/N)";
        cin >> input;
        if (input1 == "Y" || input1 == "y") {
            main();
        }
        else if (input1 == "N" || input1 == "n") {
            cm.writeCustomersToFile();
        }
        goto here;
        break;
    case 6:
        cout << "Enter Movie ID: ";
        cin >> input2;
        data.inputData(input2, to_string(input));
        goto here;
        break;
    case 7:
        customerMaintenanceMenu();
        goto here;
        break;
    case 8:
        cm.writeCustomersToFile();
        break;
    }
}

void customerMaintenanceMenu() {
    CustomerManager cm;

    int subMenu;
    do {
        cout << "===========================================\n";
        cout << "\t Customer Maintenance\n";
        cout << "===========================================\n";
        cout << "[1] Add New Customer\n";
        cout << "[2] Show Customer Details\n";
        cout << "[3] List of Videos Rented by a Customer\n";
        cout << "[4] Exit to Main Menu\n";
        cout << "===========================================\n";

        cin >> subMenu;

        switch (subMenu) {
        case 1:
            cm.newCustomers();
            break;
        case 2:
            cm.printCustomers();
            break;
        case 3:
            cm.videoRentedByCustomer();
            break;
        case 4:
            cout << "Exiting to Main Menu..." << endl;
            main();
        default:
            cout << "Invalid selection. Please try again." << endl;
        }
    } while (subMenu != 4);
}

