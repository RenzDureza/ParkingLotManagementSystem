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

//Adds new node containing license plate, row , and column.
void LinkedList::add(string licensePlate, int row, int col){
    Node *newNode, *nodePtr;

    newNode = new Node;
    newNode->licensePlate = licensePlate;
    newNode->row = row;
    newNode->col = col;
    newNode->next = NULL;

    //If linked list is empty, new node is the head;
    if (!head){
        head = newNode;
    }
    //Iterates until the end of linked list, and adds the new node at the end.
    else {
        nodePtr = head;
        while (nodePtr->next) nodePtr = nodePtr->next;
        nodePtr->next = newNode;
    }
}

//Removes a node from the linked list.
void LinkedList::remove(string licensePlate, int &row, int &col){    
    Node *prevNode, *nodePtr;
    
    nodePtr = head;
    prevNode = nullptr;
    //Iterates through all nodes
    while (nodePtr != nullptr) {
        //Checks until license plate matches then deletes that node.
        if (nodePtr->licensePlate == licensePlate) {
            if (prevNode == nullptr) {
                head = nodePtr->next;
            }
            row = nodePtr->row;
            col = nodePtr->col;
            delete nodePtr;
            return;
        }
        //Previous node points to node pointer while node pointer points to the next.
        prevNode = nodePtr;
        nodePtr = nodePtr->next;
    }
}

//Checks if the license plate exists inside the linked list
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

//Takes the row and column then returns the License plate that vacates that spot.
void LinkedList::findspot(string &licensePlate, int row, int col){
    Node *nodePtr;

    nodePtr = head;
    //Iterates through the linked list until node matches the row and column spot.
    while (nodePtr) {
        if (nodePtr->row == row && nodePtr->col == col) {
            licensePlate = nodePtr->licensePlate;
            return;
        }
        nodePtr = nodePtr->next;
    }
    return;
}

//Takes the license plate of a vehicle and returns the row and column where it is parked.
void LinkedList::findPos(string licensePlate, int &row, int &col) {
    Node *nodePtr;
    nodePtr = head;
    //Iterates through the linked list until node matches license plate.
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
    //Returns -1 for row and column if no vehicle with license plate is parked.
    row = -1;
    col = -1;
    return; 
}    