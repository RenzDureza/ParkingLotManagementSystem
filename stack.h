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
    void pop();
    bool isEmpty();
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

void Stack::pop(){
    if (isEmpty()) {
        cout << "Parking lot is full\n";
    } else {
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
