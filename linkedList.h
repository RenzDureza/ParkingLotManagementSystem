#include <iostream> 
#include <string>

using namespace std;

class LinkedList {
    public:
    struct Node {
        string licensePlate;
        int row, col;
        struct Node *next;
    };

    Node *head;

    LinkedList() {
        head = nullptr;
    }

    void add(string licensePlate, int row, int col);
    void remove(string licensePlate, int &row, int &col);
    bool exist(string licensePlate);
    void findspot(string &licensePlate, int row, int col);
    void findPos(string licensePlate, int &row, int &col);
};

// adds license plate to the list and their position
void LinkedList::add(string licensePlate, int row, int col){
    Node *newNode, *nodePtr;

    newNode = new Node;
    newNode->licensePlate = licensePlate;
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;

    if (!head){
        head = newNode;
    }
    else {
        nodePtr = head;
        while (nodePtr->next) nodePtr = nodePtr->next;
        nodePtr->next = newNode;
    }
}

// removes license plate from the list and returning their position as row and column
void LinkedList::remove(string licensePlate, int &row, int &col){    
    Node *prevNode, *nodePtr;
    
    nodePtr = head;
    prevNode = nullptr;
    while (nodePtr != nullptr) {
        if (nodePtr->licensePlate == licensePlate) {
            if (prevNode == nullptr) {
                head = nodePtr->next;
            }
            row = nodePtr->row;
            col = nodePtr->col;
            delete nodePtr;
            return;
        }
        prevNode = nodePtr;
        nodePtr = nodePtr->next;
    }
}

// checks if the inputted license plate exist in the list
bool LinkedList::exist(string licensePlate){
    Node *nodePtr;

    nodePtr = head;
    while (nodePtr) {
        if (nodePtr->licensePlate == licensePlate) {
            return true;
        }
        nodePtr = nodePtr->next;
    }
    return false;
}

// a function that uses the position to find a license plate from the list and retrieve its license plate
void LinkedList::findspot(string &licensePlate, int row, int col){
    Node *nodePtr;

    nodePtr = head;
    while (nodePtr) {
        if (nodePtr->row == row && nodePtr->col == col) {
            licensePlate = nodePtr->licensePlate;
            return;
        }
        nodePtr = nodePtr->next;
    }
    return;
}

// Finds the position of a license plate using the inputted position
void LinkedList::findPos(string licensePlate, int &row, int &col) {
    Node *nodePtr;
    nodePtr = head;
    if (exist(licensePlate)) {
        while (nodePtr) {
            if (nodePtr->licensePlate == licensePlate) {
                row = nodePtr->row;
                col = nodePtr->col;
                return;
            }
            nodePtr = nodePtr->next;
        }
    }
    row = -1;
    col = -1;
    return; 
}    