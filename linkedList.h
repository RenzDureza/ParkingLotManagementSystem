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
    void findspot(string licensePlate);
    void findPos(string licensePlate);
};


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

void LinkedList::findPos(string licensePlate) {
    Node *nodePtr;
    nodePtr = head;
    if (exist(licensePlate)) {
        while (nodePtr) {
            if (nodePtr->licensePlate == licensePlate) {
                cout << "License Plate: " << licensePlate << " is on space "<< nodePtr->row << ", " << nodePtr->col << endl;
                return;
            }
            nodePtr = nodePtr->next;
        }
    } else {
        cout << "No vehicle with license plate: " << licensePlate << " is parked\n"; 
    }    
}   