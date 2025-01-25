#include <iostream> 
#include <string>

using namespace std;

class LinkedList {
public:
    struct Node {
        string licensePlate;
        struct Node *next;
    };

    Node *head;

    LinkedList() {
        head = nullptr;
    }

    void add(string licensePlate);
    void remove(string licensePlate);
    bool exist(string licensePlate);
};


void LinkedList::add(string licensePlate){
    Node *newNode = new Node;
    newNode->licensePlate = licensePlate;
    newNode->next = head;
    head = newNode;
}

void LinkedList::remove(string licensePlate){    
    Node *nodePtr = head;
    Node * prevNode = nullptr;
    while (nodePtr != nullptr) {
        if (nodePtr->licensePlate == licensePlate) {
            if (prevNode == nullptr) {
                head = nodePtr->next;
            }
            delete nodePtr;
            return;
        }
        prevNode = nodePtr;
        nodePtr = nodePtr->next;
    }
}

bool LinkedList::exist(string licensePlate){
    Node* current = head;
    while (current != nullptr) {
        if (current->licensePlate == licensePlate) {
            return true;
        }
        current = current->next;
    }
    return false;
}
