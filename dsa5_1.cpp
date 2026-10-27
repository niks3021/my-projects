#include <iostream>

class Queue
{
private:
    int top;
    int bottom;
    int capacity;
    int size;
    int *array;

public:
    Queue(int C) : capacity(C)
    {
        top = -1;
        bottom = 0;
        size = 0;
        array = new int[capacity]; 
    }
    ~Queue()
    {
       delete[] array;
    }

    bool isEmpty() const
    {
        return size == 0;
    }
    bool isFull() const
    {
        return size == capacity;
    }
    void enqueue(int val)
    {
        if (isFull())
            return;
        top++;
        array[top] = val;
        size++;
        std::cout << val << " Enqueued!\n";
    }
    void dequeue()
    {
        if (isEmpty())
            return;
        std::cout << array[bottom] << " Dequeued!\n";
        bottom++;
        size--;
    }
    int peek() const
    {
        if(isEmpty()) {std::cout << "Empty\n";
        return -1;}
        return array[bottom];
    }
};

int main()
{
int cap;
    std::cout << "Enter Queue Capacity: ";
    std::cin >> cap;

    Queue q(cap);
    int choice, val;

    do {
        std::cout << "\n    QUEUE MENU    \n";
        std::cout << "1. Enqueue (Insert)\t";
        std::cout << "2. Dequeue (Remove)\t";
        std::cout << "3. Peek (Front Element)\n";
        std::cout << "4. Check if Full\t";
        std::cout << "5. Check if Empty\t";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (q.isFull()) {
                    std::cout << "Overflow! Queue is Full.\n";
                } else {
                    std::cout << "Enter value: ";
                    std::cin >> val;
                    q.enqueue(val);
                }
                break;

            case 2:
                if (q.isEmpty()) {
                    std::cout << "Underflow! Queue is Empty.\n";
                } else {
                    q.dequeue();
                }
                break;

            case 3:
                val = q.peek();
                if (val != -1) {
                    std::cout << "Front element: " << val << "\n";
                }
                break;

            case 4:
                std::cout << (q.isFull() ? "Queue is Full.\n" : "Queue is NOT Full.\n");
                break;

            case 5:
                std::cout << (q.isEmpty() ? "Queue is Empty.\n" : "Queue is NOT Empty.\n");
                break;

            case 6:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);
    return 0;
}