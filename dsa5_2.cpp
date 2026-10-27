#include <iostream>
#include <vector>

using namespace std;

struct Element {
    int value;
    int priority;
};

class PriorityQueue {
private:
    vector<Element> queue;
    int capacity;

public:
    PriorityQueue(int cap) {
        capacity = cap;
    }

    bool isEmpty() const {
        return queue.empty();
    }

    bool isFull() const {
        return queue.size() >= capacity;
    }

    void enqueue(int value, int priority) {
        if (isFull()) {
            cout << "Queue Overflow!\n";
            return;
        }
        queue.push_back({value, priority});
        cout << "Inserted: " << value << " (Priority: " << priority << ")\n";
    }

    Element dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return {-1, -1};
        }

        int highestIndex = 0;
        for (int i = 1; i < queue.size(); i++) {
            if (queue[i].priority > queue[highestIndex].priority) {
                highestIndex = i;
            }
        }

        Element highest = queue[highestIndex];
        queue.erase(queue.begin() + highestIndex);
        return highest;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue items: ";
        for (const auto& item : queue) {
            cout << item.value << "(" << item.priority << ") ";
        }
        cout << "\n";
    }
};


int main() 
{
    int cap;
    cout << "Enter Priority Queue capacity: ";
    cin >> cap;

    PriorityQueue pq(cap);
    int choice, val, prio;

    do {
        cout << "\n1. Enqueue  2. Dequeue  3. isFull  4. isEmpty  5. Display  6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value and priority: ";
                cin >> val >> prio;
                pq.enqueue(val, prio);
                break;
            case 2: {
                Element e = pq.dequeue();
                if (e.value != -1) {
                    cout << "Dequeued: " << e.value << " with priority " << e.priority << "\n";
                }
                break;
            }
            case 3:
                cout << (pq.isFull() ? "Queue is Full\n" : "Queue is Not Full\n");
                break;
            case 4:
                cout << (pq.isEmpty() ? "Queue is Empty\n" : "Queue is Not Empty\n");
                break;
            case 5:
                pq.display();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
