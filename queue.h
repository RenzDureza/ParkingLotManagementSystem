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

    Queue::Queue(int maxSize){
        waitingLine = new string[maxSize];
        front = -1;
        rear = -1;
        size = 0;
    }

    Queue::~Queue() {
        delete[] waitingLine;
    }

    // Functions pang check if the waiting line is empty or full na
    bool Queue::isLineEmpty() {
        return front == -1 || front > rear;
    }

    bool Queue::isLineFull() {
        return rear == maxSize - 1;
    }

    // Memang makeshift Enqueue
    void Queue::addLine(const string &licensePlate) {
        if (isLineFull()) {
            cout << "Queue line is full. Cannot add more vehicles.\n";
        } else {
            if (front == -1) {
                front = 0;
            }
            waitingLine[++rear] = licensePlate;
            cout << "rear:" << rear;
            cout << "Vehicle " << licensePlate << " added to the waiting line.\n";
        }
    }

    // Memang makeshift Dequeue 
    string Queue::removeLine() {
        if (isLineEmpty()) {
            cout << "Queue line is empty.\n";
            return ""; 
        }
        string licensePlate = waitingLine[front++];
        if (front > rear) { 
            front = -1;
            rear = -1;
        }
        return licensePlate;
    }


