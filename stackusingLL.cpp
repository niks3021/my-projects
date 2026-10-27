#include <iostream>
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

class Stack
{
private:
    Node *top;

public:
    Stack() : top(nullptr) {}
    ~Stack()
    {
        while (top != nullptr)
        {
            Node *temp = top;
            top = top->getPointer();
            delete temp;
        }
    }

    void push(int Val)
    {
        Node *newNode = new Node(Val, top);
        top = newNode;
    }
    int pop()
    {

        if (top == nullptr)
        {
            std::cout << "Stack Underflow!\n";
            return -1;
        }

        Node *temp = top;
        int poppedValue = temp->getValue();
        top = top->getPointer();
        delete temp;

        return poppedValue;
    }
    int peek()
    {
        if (top == nullptr)
        {
            std::cout << "Stack is empty!\n";
            return -1;
        }
        return top->getValue();
    }
    void display()
    {
        std::cout << "Top -> ";
        Node *temp = top;
        while (temp != nullptr)
        {
            std::cout << temp->getValue() << " -> ";
            temp = temp->getPointer();
        }
        std::cout << " End\n";
    }
};

int main()
{
    Stack S1;
    S1.push(1);
    S1.push(3);
    S1.push(-5);
    S1.display();
    std::cout << "Popping: "<< S1.pop()<<std::endl;
    std::cout <<"top Element: "<<S1.peek();
}