#include <iostream>
#include <fstream>
#include "linkedList.h"
#include "queue.h"
#include "stack.h"

using namespace std;

// Constants na palitan nalang if mas malaki
const int maxRow = 2;
const int maxCol = 2;
const int maxQueue = 5;
LinkedList licenseList;
Queue waitingLine(maxQueue);
Stack vacantSpot;

// Global Data Structures para mas madaling maaccess
char parkingLot[maxRow][maxCol];          // 2D array 
string parkedVehicles[maxRow][maxCol];    // Store vehicle license plates
// string waitingLine[max_waiting_line];     // Array for the queueline
int front = -1, rear = -1;                // Line pointers
string logFileName = "parking_log.txt";   // File to save activity log

// Function to initialize the parking lot
void initializeParkingLot() {
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            parkingLot[i][j] = 'E'; // 'E' stands for Empty
        }
    }
}


//traversal while checking if index in matrix is full or not (E  or  P)
bool findNearestSpot(int &row, int &col) {
    if (!vacantSpot.isEmpty()) {
        vacantSpot.pop(row, col);
        return true;
    }
    
    for (int i = 0; i < maxRow; i++) {
        if (i % 2 == 0){
            for (int j = 0; j < maxCol; j++) {
                if (parkingLot[i][j] == 'E') { // Check if the parking spot is empty
                    row = i;
                    col = j;
                    return true; // Parking Spot found and available
                }
            }
        }
        else { //Reverses finder every alternate row
            for (int j = maxCol - 1; j >= 0; j--) {
                if (parkingLot[i][j] == 'E') {
                    row = i;
                    col = j;
                    return true;
                }
            }
        }
    }
    return false; // Full parking na
}


void parkVehicle(const string &licensePlate) {
    int row, col;

    if (licenseList.exist(licensePlate)) {
        cout << "Vehicle is already parked\n";
        return;
    }

    if (findNearestSpot(row, col)) {
        parkingLot[row][col] = 'P'; // Mark the spot as parked
        parkedVehicles[row][col] = licensePlate;
        licenseList.add(licensePlate, row, col);
        cout << "Vehicle " + licensePlate + " parked at (" + to_string(row) + ", " + to_string(col) + ")\n";

        //file writing 
        ofstream logFile(logFileName, ios::app);
        if (logFile) {
            logFile << "Vehicle " + licensePlate + " parked at (" + to_string(row) + ", " + to_string(col) + ")\n";
            logFile.close();
        }
    } else {
        cout << "Parking lot is full. Adding vehicle to the waiting line.\n";
        waitingLine.addLine(licensePlate);
    }
}


void retrieveVehicle(const string &licensePlate) {
    int row, col;
    if (licenseList.exist(licensePlate)) {
        licenseList.remove(licensePlate, row, col);
        vacantSpot.push(row, col);
        parkingLot[row][col] = 'E';
        cout << "Vehicle " + licensePlate + " left at (" + to_string(row) + ", " + to_string(col) + ")\n";

        ofstream logFile(logFileName, ios::app);
        if (logFile) {
            logFile << "Vehicle " + licensePlate + " left at (" + to_string(row) + ", " + to_string(col) + ")\n";
            logFile.close();
        }
        return;
    }
    else {
        cout << "Vehicle with licensplate " << licensePlate << " does not exist.\n";
        return;
    }
}


void displayParkingLot() {
    cout << "    ";
    for (char c = 'A'; c < 'A' + maxCol; ++c) {
        cout << c << "    ";
    }
    cout << endl;

    for (int i = 0; i < maxRow; i++) {
        
        cout << i << " ";
        for (int j = 0; j < maxCol; j++) {
            cout << "[ " << parkingLot[i][j] << " ]";    
        }
        cout << endl;
    }
}


int main() {
    initializeParkingLot();
    int choice;
    string licensePlate;

    do {
    	cout << "-----------------------------------------------------------------";
        cout << "\n================= Parking Lot Management System ===============\n";
       	cout << "-----------------------------------------------------------------\n";
        cout << "1. Park Vehicle\n"; 
        cout << "2. Retrieve Vehicle\n";  //Done
        cout << "3. Display Parking Lot\n"; //Done 
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the license plate of the vehicle: ";
                cin >> licensePlate;
                parkVehicle(licensePlate);
                break;
            case 2:
                cout << "Enter the license plate of the vehicle: ";
                cin >> licensePlate;
                retrieveVehicle(licensePlate);
                vacantSpot.display(); 
                break;
            case 3:
                displayParkingLot(); 
                break;
            case 4:
                cout << "Exiting system. Thank you for using this system!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
