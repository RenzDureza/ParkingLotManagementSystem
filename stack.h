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
        top = nullptr;
    }

    void push();
    void pop();
    bool isEmpty();
};

void Stack::push(){
    // TODO
}

void Stack::pop(){
    // TODO
}

bool Stack::isEmpty(){
    // TODO
}
