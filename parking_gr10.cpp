#include <iostream>
#include <fstream>
#include "linkedList.h"
#include "queue.h"
#include "stack.h"

using namespace std;

// Constants na palitan nalang if mas malaki
const int maxRow = 5;
const int maxCol = 5;
const int maxQueue = 5;
LinkedList licenseList;
Queue waitingLine(maxQueue);
Stack vacantSpot;

// Global Data Structures para mas madaling maaccess
char parkingLot[maxRow][maxCol];          // 2D array 
string parkedVehicles[maxRow][maxCol];    // Store vehicle license plates
int front = -1, rear = -1;                // Line pointers
string logFileName = "parking_log.txt";   // File to save activity log

// Function to initialize the parking lot
void initializeParkingLot() {
    for (int i = maxRow - 1; i >= 0; i--) {
        if (i % 2 == 1){
            for (int j = 0; j < maxCol; j++) {
                parkingLot[i][j] = 'E';
                vacantSpot.push(i, j);
                }
        }
        else { //Reverses finder every alternate row
            for (int j = maxCol - 1; j >= 0; j--) {
                parkingLot[i][j] = 'E';
                vacantSpot.push(i, j);
            }
        }
    }
}


//traversal while checking if index in matrix is full or not (E  or  P)
bool findNearestSpot(int &row, int &col) {
    //Stack Implementation
    if (!vacantSpot.isEmpty()) {
    vacantSpot.pop(row, col);
    return true;
    }
    return false; // Full parking na
}


void parkVehicle(const string &licensePlate) {
    int row, col;

    if (licenseList.exist(licensePlate)) {
        cout << "| Vehicle is already parked\n";
        return;
    }

    if (findNearestSpot(row, col)) {
        parkingLot[row][col] = 'P'; // Mark the spot as parked
        parkedVehicles[row][col] = licensePlate;
        licenseList.add(licensePlate, row, col);
        cout << "| Vehicle <" << licensePlate << "> parked at (" << char(col+65) << row+1 << ")\n";

        //file writing 
        ofstream logFile(logFileName, ios::app);
        if (logFile) {
            logFile << "| Vehicle <" + licensePlate + "> parked at (" + char(col+65) + to_string(row+1) + ")\n";
            logFile.close();
        }
    } else {
        cout << "| Parking lot is full. Adding vehicle to the waiting line.\n";
        waitingLine.addLine(licensePlate);
    }
}


void retrieveVehicle(const string &licensePlate) {
    int row, col;
    string replacingVehicle;
    if (licenseList.exist(licensePlate)) {
        licenseList.remove(licensePlate, row, col);
        vacantSpot.push(row, col);
        parkingLot[row][col] = 'E';
        cout << "| Vehicle <" << licensePlate << "> left at (" << char(col+65) << row+1 << ")\n";

        ofstream logFile(logFileName, ios::app);
        if (logFile) {
            logFile << "Vehicle <" + licensePlate + "> left at (" + char(col+65) + to_string(row+1) + ")\n";
            logFile.close();
        }

        if (!waitingLine.isLineEmpty()){
            replacingVehicle = waitingLine.removeLine();
            licenseList.add(replacingVehicle, row, col);
            cout << "| Vehicle <" << replacingVehicle << "> from waiting queue parked at (" << char(col+65) << row+1 << ")\n";
                ofstream logFile(logFileName, ios::app);
                if (logFile) {
                logFile << "| Vehicle <" << replacingVehicle << "> from waiting queue parked at (" << char(col+65) << row+1 << ")\n";
                logFile.close();
                }
            parkingLot[row][col] = 'P';
            vacantSpot.pop(row, col);
        }      
        return;
    }
    else {
        cout << "| Vehicle with licensplate <" << licensePlate << "> does not exist.\n";
        return;
    }
}


void displayParkingLot() {
    cout << "|     ";
    for (char c = 'A'; c < 'A' + maxCol; ++c) {
        cout << c << "    ";
    }
    cout << endl;

    for (int i = 0; i < maxRow; i++) {
        
        cout << "| " << i + 1 << " ";
        for (int j = 0; j < maxCol; j++) {
            cout << "[ " << parkingLot[i][j] << " ]";    
        }
        cout << endl;
    }
    return;
}

void displaySpot(string spot){
    int row, col;
    string licensePlate;
    row = spot[1] - 49;
    col = spot[0] - 65;
    licenseList.findspot(licensePlate, row, col);
    if (licensePlate == "") {
        cout << "| Spot (" << spot << ") is vacant. " << endl;
        return;
    }
    cout << "| Spot " << spot << " is vacated by <" << licensePlate << ">" << endl;
    return;
}

void searchVehicle(string licensePlate){
    int row, col;
    string spot;
    licenseList.findPos(licensePlate, row, col);
    if (row == -1 && col == -1){
        cout << "| No vehicle with license plate <" << licensePlate << "> is parked\n";
        return;
    }
    cout << "| Vehicle <" << licensePlate << "> is on spot ("<< char(col+65) << row+1 << ")" << endl;
    return;
}

int main() {
    initializeParkingLot();
    int choice;
    string licensePlate, spot;

    do {
    	cout << "|-----------------------------------------------------------------";
        cout << "\n|================= Parking Lot Management System =================\n";
       	cout << "|-----------------------------------------------------------------\n";
        cout << "| 1. Park Vehicle\n"; 
        cout << "| 2. Retrieve Vehicle\n";  //Done
        cout << "| 3. Display Parking Lot\n"; //Done
        cout << "| 4. Search Vehicle with Plate number\n";
        cout << "| 5. Display License Number with Spot \n";
        cout << "| 6. Show Vacant Spots\n";
        cout << "| 0. Exit\n";
        cout << "| Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
       	        cout << "|-----------------------------------------------------------------";
                cout << "\n|======================== Park a Vehicle =========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "| Enter the license plate of the vehicle: ";
                cin >> licensePlate;
                parkVehicle(licensePlate);
                cout << "| ";
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|======================= Retrieve a Vehicle ======================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "| Enter the license plate of the vehicle: ";
                cin >> licensePlate;
                retrieveVehicle(licensePlate);
                cout << "| ";
                system("pause");
                system("cls"); 
                break;
            case 4:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|======================= Search a Vehicle ========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "| Enter the license plate of the vehicle: ";
                cin >> licensePlate;
                searchVehicle(licensePlate);
                cout << "| ";
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|======================== Parking Lot Map ========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                displayParkingLot();
                cout << "| \n";
                cout << "| ";
                system("pause");
                system("cls"); 
                break;
            case 5:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|========================= Display Spot ==========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "| Enter the parking spot: ";
                cin >> spot;
                displaySpot(spot);
                cout << "| ";
                system("pause");
                system("cls");
                break;
            case 6:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|======================= List of Vacant Spot =====================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                vacantSpot.display();
                cout << "| ";
                system("pause");
                system("cls");
                break;
            case 0:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|=========================== Thank You ===========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "| Exiting system. Thank you for using this system!\n";
                cout << "| ";
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|============================= ERROR =============================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "| Invalid choice. Please try again.\n";
                cout << "| ";
                system("pause");
                system("cls");
                break;
        }
    } while (choice != 0);

    return 0;
}
