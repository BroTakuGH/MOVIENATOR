#include <iostream>
#include "data.h"
using namespace std;
//test11111
int main()
{
    int input;
    string input2;

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
        cout << "Enter Movie ID: ";
        cin >> input2;
        inputData(input2);
        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    case 7:

        break;
    case 8:

        break;
    }
}

