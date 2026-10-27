#include <iostream>

// 1. Node Structure
struct Node {
    int data;
    Node* next;
};

// 2. Stack Class
class LinkedListStack {
private:
    Node* top;

public:
    LinkedListStack() : top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    bool isFull() const {
        // Full if system runs out of heap memory
        Node* temp = new (std::nothrow) Node();
        if (temp == nullptr) return true;
        delete temp;
        return false;
    }

    void push(int val) {
        Node* newNode = new (std::nothrow) Node();
        if (!newNode) {
            std::cout << "Stack Overflow!\n";
            return;
        }
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "Stack Underflow!\n";
            return -1;
        }
        Node* temp = top;
        int poppedValue = temp->data;
        top = top->next;
        delete temp;
        return poppedValue;
    }

    int peek() const {
        if (isEmpty()) return -1;
        return top->data;
    }

    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};
int main()
{
    LinkedListStack S1;
    std::cout << (S1.isEmpty() ? "Stack is Empty\n" : "Stack is Not empty\n");
    S1.push(5);
    std::cout << (S1.isEmpty() ? "Stack is Empty\n" : "Stack is Not empty\n");
    S1.push(4);
    std::cout << S1.peek() << "\n";
    S1.pop();
    std::cout << S1.peek() << "\n";
}