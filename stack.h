#include <iostream>
using namespace std;

class Stack {
public:
    struct Node {
        int row, col; // coordinates
        Node* next;
    };

    Node* top; // pointer to the top of the stack

    Stack() {
        this->top = nullptr;
    }

    void push(int row, int col);
    void pop(int &row, int &col);
    bool isEmpty();
    void display();
};

void Stack::push(int row, int col){
    Node* newNode = new Node;
    newNode->row = row;
    newNode->col = col;
    if (isEmpty()) {    // if the stack is empty, set the new as the top
       top = newNode;
       newNode->next = nullptr;
    } else {    // else, link the new node to the current top and update top
        newNode->next = top;
        top = newNode;
    }
}

void Stack::pop(int &row, int &col){
    if (isEmpty()) {    // check if the stack is empty
        cout << "| Parking lot is full\n";
    } else {

        // retrieve the row and column of the top
        row = top->row;
        col = top->col;

        // delete  the top node and update  top pointer
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

// returns true if the the top is null, else returns false
bool Stack::isEmpty(){
    bool status;

    if (!top) {
        status = true;
    } else {
        status = false;
    }

    return status;
}


void Stack::display() {
    if (isEmpty()) {
        cout << "| Parking lot is full\n";
    } else {
        Node* nodePtr;
        nodePtr = top; // starts on the top of the stack
        cout << "| Displaying all vacated spots in stack:\n";
        cout << "| Top | ";
        while (nodePtr != nullptr) { // traverse through the stack while printing every coordinate
            cout << char(nodePtr->col+65) << nodePtr->row+1 << " "; // convert the column to letter 
            nodePtr = nodePtr->next; // move to next node
        }
        cout << "| Bottom \n";
    }
}
