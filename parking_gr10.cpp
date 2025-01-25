#include <iostream>
#include <fstream>
#include "linkedList.h"

using namespace std;

LinkedList licenseList;
// Constants na palitan nalang if mas malaki
const int rows = 5;
const int cols = 5;
const int max_waiting_line = 5; // Maximum size of the waiting line

// Global Data Structures para mas madaling maaccess
char parkingLot[rows][cols];              // 2D array 
string parkedVehicles[rows][cols];        // Store vehicle license plates
string waitingLine[max_waiting_line];     // Array for the queueline
int front = -1, rear = -1;                // Line pointers
string logFileName = "parking_log.txt";   // File to save activity log

// Function to initialize the parking lot
void initializeParkingLot() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            parkingLot[i][j] = 'E'; // 'E' stands for Empty
        }
    }
}

// Functions pang check if the waiting line is empty or full na
bool isLineEmpty() {
    return front == -1 || front > rear;
}

bool isLineFull() {
    return rear == max_waiting_line - 1;
}

// Memang makeshift Enqueue
void addLine(const string &licensePlate) {
    if (isLineFull()) {
        cout << "Queue line is full. Cannot add more vehicles.\n";
    } else {
        if (front == -1) {
            front = 0;
        }
        waitingLine[++rear] = licensePlate;
        cout << "Vehicle " << licensePlate << " added to the waiting line.\n";
    }
}

// Memang makeshift Dequeue 
string removeLine() {
    if (isLineEmpty()) {
        return ""; 
    }
    string licensePlate = waitingLine[front++];
    if (front > rear) { 
        front = -1;
        rear = -1;
    }
    return licensePlate;
}

//traversal while checking if index in matrix is full or not (E  or  P)
bool findNearestSpot(int &row, int &col) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (parkingLot[i][j] == 'E') { // Check if the parking spot is empty
                row = i;
                col = j;
                return true; // Parking Spot found and available
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
        cout << "Vehicle parked at spot (" << row << ", " << col << ").\n";

        licenseList.add(licensePlate);
        //file writing 
        ofstream logFile(logFileName, ios::app);
        if (logFile) {
            logFile << "Parked Vehicle " + licensePlate + " at (" + to_string(row) + ", " + to_string(col) + ")\n";
            logFile.close();
        }
    } else {
        cout << "Parking lot is full. Adding vehicle to the waiting line.\n";
        addLine(licensePlate);
    }
}


void retrieveVehicle(const string &licensePlate) {
    cout << "[TO DO]";
}



void displayParkingLot() {
    for (int i = 0; i < rows; i++) {
        cout << "| ";
        for (int j = 0; j < cols; j++) {
            cout << "[ " << parkingLot[i][j] << " ]";    
        }
        cout << " |" << endl;
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
        cout << "2. Retrieve Vehicle\n";  //Pagawa Please 
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
                retrieveVehicle(licensePlate); 
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


