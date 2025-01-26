#include <iostream>
using namespace std;

class Stack {
public:
    struct Node {
        int row, col;
        Node* next;
    };

    Node* top;

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
    if (isEmpty()) {
       top = newNode;
       newNode->next = nullptr;
    } else {
        newNode->next = top;
        top = newNode;
    }
}

void Stack::pop(int &row, int &col){
    if (isEmpty()) {
        cout << "| Parking lot is full\n";
    } else {
        row = top->row;
        col = top->col;

        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

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
        nodePtr = top;
        cout << "| Displaying all vacated spots in stack:\n";
        cout << "| Top | ";
        while (nodePtr != nullptr) {
            cout << char(nodePtr->col+65) << nodePtr->row+1 << " ";
            nodePtr = nodePtr->next;
        }
        cout << "| Bottom \n";
    }
}
