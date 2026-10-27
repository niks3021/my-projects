#include <iostream>
#include <stack>
class Node
{
private:
    int Value = 0;
    Node *pointer = nullptr;

public:
    // Contructor
    Node(int V, Node *p) : Value(V), pointer(p)
    {
    }
    // Getter
    int getValue() const { return Value; }
    Node *getPointer() const { return pointer; }
    // Setter
    void setValue(int V) { Value = V; }
    void setPointer(Node *P) { pointer = P; }
};

class Queue
{
private:
    Node *Front;
    Node *Rear;

public:
    Queue() : Front(nullptr), Rear(nullptr) {}
    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
    Node *getFront() const { return Front; }
    Node *getRear() const { return Rear; }
    void setFront(Node *F) { Front = F; }
    void setRear(Node *R) { Rear = R; }
    bool isEmpty() const
    {
        return Front == nullptr;
    }
    void enqueue(int val)
    {
        if (isEmpty())
        {
            Node *newNode = new Node(val, nullptr);
            Front = newNode;
            Rear = newNode;
        }
        else
        {
            Node *newNode = new Node(val, nullptr);
            Rear->setPointer(newNode);
            Rear = newNode;
        }
    }
    void dequeue()
    {
        if (isEmpty())
        {
            std::cout << "Underflow\n";
            return;
        }
        Node *temp = Front;
        Front = Front->getPointer();
        if (Front == nullptr)
        {
            Rear = nullptr;
        }
        delete temp;
    }
    int peek() const
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty\n";
            return -1; // Or throw an exception
        }
        return Front->getValue();
    }
};
