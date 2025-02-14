#include <iostream>
#include <fstream>
#include "linkedList.h"
#include "queue.h"
#include "stack.h"

using namespace std;

// Constants to change
const int maxRow = 5;
const int maxCol = 5;
const int maxQueue = 5;

//Initialization of Data Structures
LinkedList licenseList;
Queue waitingLine(maxQueue);
Stack vacantSpot;

// Global Data Structures para mas madaling maaccess
char parkingLot[maxRow][maxCol];          // 2D array of Parking Lot
string logFileName = "parking_log.txt";   // File to save activity log

// Function Prototyping
void initializeParkingLot();
bool findNearestSpot(int &row, int &col);
void parkVehicle(const string &licensePlate);
void retrieveVehicle(const string &licensePlate);
void displayParkingLot();
void displaySpot(string spot);
void searchVehicle(string licensePlate);
void updateLog(string message);
bool invalidInput();
bool isValidLicense(string licensePlate);

int main() {
    initializeParkingLot();
    int choice;
    string licensePlate, spot;
    bool run = true;

    do {
    	cout << "|-----------------------------------------------------------------";
        cout << "\n|================= Parking Lot Management System =================\n";
       	cout << "|-----------------------------------------------------------------\n";
        cout << "| 1. Park Vehicle\n"; 
        cout << "| 2. Retrieve Vehicle\n";
        cout << "| 3. Display Parking Lot\n";
        cout << "| 4. Check a Spot (insert Spot)\n";
        cout << "| 5. Search Vehicle (insert Plate number)\n";
        cout << "| 6. Show Vacant Spots\n";
        cout << "| 0. Exit\n";
        cout << "| Enter your choice: ";
        cin >> choice;
        //Cheks for valid input within the same data type, else it will prompt the user again to enter their choice.
        if (invalidInput()) {
            system("cls");
            continue;
        }

        switch (choice) {
            case 1:
                system("cls");
       	        cout << "|-----------------------------------------------------------------";
                cout << "\n|======================== Park a Vehicle =========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                cout << "| Enter the license plate of the vehicle: ";
                cin >> licensePlate;
                //Checks if license plate is valid, if not valid, case will break and the vehicle will not be parked.
                if (!isValidLicense(licensePlate)) break;
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
            case 4:
                system("cls");
                cout << "|-----------------------------------------------------------------";
                cout << "\n|========================= Check a Spot ==========================\n";
       	        cout << "|-----------------------------------------------------------------\n";
                displayParkingLot();
                cout << "|\n| Enter the parking spot: ";
                cin >> spot;
                displaySpot(spot);
                cout << "| ";
                system("pause");
                system("cls");
                break;
            case 5:
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
                run = false;
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
    } while (run);
    return 0;
}

// Function to initialize the parking lot
void initializeParkingLot() {
    for (int i = maxRow - 1; i >= 0; i--) {
        if (i % 2 == 1){
            for (int j = 0; j < maxCol; j++) {
                parkingLot[i][j] = 'E';
                //Push spot stack.
                vacantSpot.push(i, j);
            }
        }
        else { //Reverses every alternate row
            for (int j = maxCol - 1; j >= 0; j--) {
                parkingLot[i][j] = 'E';
                //Push spot to stack.
                vacantSpot.push(i, j);
            }
        }
    }
}

//Get the nearest parking spot from top of stack.
bool findNearestSpot(int &row, int &col) {
    if (!vacantSpot.isEmpty()) {
        vacantSpot.pop(row, col);
        return true;
    }
    return false; // Full parking na
}

//Parks a vehicle with its license plate.
void parkVehicle(const string &licensePlate) {
    int row, col, qnum;

    //Checks for duplicate license plate in parking lot.
    if (licenseList.exist(licensePlate)) {
        cout << "| Vehicle is already parked\n";
        return;
    }

    //Returns true if there is an available parking spot as well as its row and column.
    if (findNearestSpot(row, col)) {
        parkingLot[row][col] = 'P'; // Mark the spot as parked
        licenseList.add(licensePlate, row, col);
        string message = "Vehicle <" + licensePlate + "> parked at (" + string(1, char(col + 65)) + to_string(row + 1) + ")\n";
        updateLog(message);
    } 
    //Returns false if parking lot is full
    else {
        cout << "| Parking lot is full. Adding vehicle to the waiting line.\n";
        //Checks for duplicate license plate in waiting queue.
        if (waitingLine.exist(licensePlate)) {
            cout << "| Vehicle is already in waiting line.\n";
            return;
        }
        //Transfers the vehicle to queue.
        waitingLine.addLine(licensePlate, qnum);
        string message = "Vehicle <" + licensePlate + "> added to the waiting line queue #" + to_string(qnum) + "\n";
        updateLog(message);
    }
}

//Retrieves vehicle from parking lot.
void retrieveVehicle(const string &licensePlate) {
    int row, col;
    string replacingVehicle;
    //Checks if license plate exists for retrieval.
    if (licenseList.exist(licensePlate)) {
        licenseList.remove(licensePlate, row, col);
        //Push vacant spot to stack.
        vacantSpot.push(row, col);
        //Changes character in parking lot array to Empty.
        parkingLot[row][col] = 'E';
        string message = "Vehicle <" + licensePlate + "> left at (" + string(1, char(col + 65)) + to_string(row + 1) + ")\n";
        updateLog(message);
        //Checks for available vehicles in queue.
        if (!waitingLine.isLineEmpty()){
            replacingVehicle = waitingLine.removeLine();
            //Adds vehicle from queue to parking lot linked list.
            licenseList.add(replacingVehicle, row, col);
            string message = "Vehicle <" + replacingVehicle + "> from waiting queue parked at (" + string(1, char(col + 65)) + to_string(row + 1) + ")\n";
            updateLog(message);
            //Changes character in parking lot array back to Parked.
            parkingLot[row][col] = 'P';
            //Pops vacant spot from stack.
            vacantSpot.pop(row, col);
        }      
        return;
    }
    else {
        cout << "| Vehicle with licensplate <" << licensePlate << "> does not exist.\n";
        return;
    }
}

//Display Parking Lot Array
void displayParkingLot() {
    //Displays Column and Row Labels
    cout << "|     ";
    for (char c = 'A'; c < 'A' + maxCol; ++c) {
        cout << c << "    ";
    }
    cout << endl;

    //Displays all parking lot spaces whether if it is E for Empty and P for Parked
    for (int i = 0; i < maxRow; i++) {
        cout << "| " << i + 1 << " ";
        for (int j = 0; j < maxCol; j++) {
            cout << "[ " << parkingLot[i][j] << " ]";    
        }
        cout << endl;
    }
    return;
}

//Displays the license plate of a vehicle occupying a spot entered by the user.
void displaySpot(string spot){
    int row, col;
    string licensePlate;
    col = spot[0] - 65;
    row = spot[1] - 49;
    if (row < 0 || row >= maxRow || col < 0 || col >= maxCol){
        cout << "| Invalid Spot.\n"; 
        return;
    }
    licenseList.findspot(licensePlate, row, col);
    if (licensePlate == "") {
        cout << "| Spot (" << spot << ") is vacant. " << endl;
        return;
    }
    cout << "| Spot " << spot << " is vacated by <" << licensePlate << ">" << endl;
    return;
}

//Displays the spot where a vehicle is parked with the license plate entered by the user.
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

//Function for updating logs inside the .txt file
void updateLog(string message){
    cout << "| " << message;
    ofstream logFile(logFileName, ios::app);
    if (logFile) {
        logFile << message;
        logFile.close();
    }
}

//Checks input if the user inputs a different data type, cin will fail and the system will remove each character and return true
bool invalidInput(){
    if (cin.fail()){
        cin.clear();
        char c;
        while (cin.get(c) && c != '\n')
        ;
        cout << "| Invalid input. Please try again.\n";
        return true;
    }
    return false;
}

//Checks if the characters inside license plate string is valid containg only alphanumeric characters.
bool isValidLicense(string licensePlate) {
    if (licensePlate.length() > 6) {
        cout << "| Invalid License Plate. Maximum of 6 Characters\n";
        return false;
    }
    else{
        for(int i = 0; i < licensePlate.length(); i++) {
            //Checks each character's ascii value. Valid License plates are only between 0-9(48-57), A-Z (65-90), and a-z(97-112).
            if (licensePlate[i] < 48 || (licensePlate[i] > 57 && licensePlate[i] < 65) || (licensePlate[i] > 90 && licensePlate[i] < 97) || licensePlate[i] > 122){
                cout << "| Invalid character found.\n";
                return false;
                //Returns invalid license plate if a special character is found.
            }
        }
    }
    return true;
}
