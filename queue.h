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
    void addLine(const string &licensePlate);
    string removeLine();
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

// Functions pang check if the waiting line is empty or full na
bool Queue::isLineEmpty() {
    if (size) return false;
    else return true;
}

bool Queue::isLineFull() {
    if (size < maxSize) return false;
    else return true;
}

// Memang makeshift Enqueue
void Queue::addLine(const string &licensePlate) {
    if (isLineFull()) {
        cout << "| Queue line is full. Cannot add more vehicles.\n";
    } else {
        rear = (rear + 1) % maxSize;
        waitingLine[rear] = licensePlate;
        size++;
        cout << "| Vehicle <" << licensePlate << "> added to the waiting line queue #" << size << endl;
    }
}

// Memang makeshift Dequeue 
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


