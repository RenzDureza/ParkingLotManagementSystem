#include <iostream> 
#include <string>

using namespace std;

class Queue {
    private:
    string *waitingLine;
    int size, front, rear, maxSize;     // Array for the queueline

    public:
    Queue (int size);
    ~Queue();
    bool isLineEmpty();
    bool isLineFull();
    void addLine(const string &licensePlate, int &qnum);
    string removeLine();
    bool exist(string licensePlate);
};    

Queue::Queue(int queueSize){
    waitingLine = new string[queueSize];
    front = -1;
    rear = -1;
    size = 0;
    maxSize = queueSize;
}

Queue::~Queue() {
    delete[] waitingLine;
}

//Check if queue is empty by returning true if size is 0.
bool Queue::isLineEmpty() {
    if (size) return false;
    else return true;
}

//Checks if line is full by returning true if queue size is equal to maxsize.
bool Queue::isLineFull() {
    if (size < maxSize) return false;
    else return true;
}

//Adds vehicle to queue while also returning license plate and queue number for updating logs.
void Queue::addLine(const string &licensePlate, int &qnum) {
    if (isLineFull()) {
        cout << "| Queue line is full. Cannot add more vehicles.\n";
        return;
    }
    else {
        rear = (rear + 1) % maxSize;
        waitingLine[rear] = licensePlate;
        size++;
        qnum = size;
        return;
    }
}

//Removes vehicle from queue and returns the license plate of the removed vehicle.
string Queue::removeLine() {
    string licensePlate;
    if (isLineEmpty()) {
        cout << "| Queue line is empty.\n";
        return ""; 
    }
    front = (front + 1) % maxSize;
    licensePlate = waitingLine[front];
    size--;
    return licensePlate;
}

//Checks if license plate exists within the queue for duplicates.
bool Queue::exist(string licensePlate){
    if (isLineEmpty()) {
        return false; 
    }
    for (int i = front; i < size; i++){
        if (waitingLine[i] == licensePlate){
            return true;
        }
    }
    return false;
}
