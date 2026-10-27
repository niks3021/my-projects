#include <iostream>
#include <string>
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

class LinkedList
{
private:
    Node *Head;

public:
    LinkedList() : Head(nullptr) {}

    ~LinkedList()
    {
        while (Head != nullptr)
        {
            Node *temp = Head;
            Head = Head->getPointer();
            delete temp;
        }
    }
    // getter head
    Node *getHead() const { return Head; }
    // setter head
    void setHead(Node *newHead) { Head = newHead; }

    int insert(int value, int TargetIndex)
    {
        // 0-Index special case
        if (TargetIndex == 0)
        {
            Node *newNode = new Node(value, Head);
            Head = newNode;
            return 0;
        }

        if (Head == nullptr)
        {
            return -1;
        }

        Node *temp = Head;
        for (int i = 0; i < TargetIndex - 1; i++)
        {
            if (temp == nullptr)
            {
                return -1;
            }
            temp = temp->getPointer();
        }

        if (temp == nullptr)
        {
            return -1;
        }

        Node *newNode = new Node(value, temp->getPointer());
        temp->setPointer(newNode);
        return 0;
    }

    int remove(int TargetIndex)
    {
        if (Head == nullptr)
        {
            return -1;
        }

        if (TargetIndex == 0)
        {
            Node *toDelete = Head;
            Head = Head->getPointer();
            delete toDelete;
            return 0;
        }

        Node *temp = Head;
        for (int i = 0; i < TargetIndex - 1; i++)
        {
            if (temp == nullptr)
            {
                return -1;
            }
            temp = temp->getPointer();
        }

        if (temp == nullptr)
        {
            return -1;
        }

        Node *toDelete = temp->getPointer();
        if (toDelete == nullptr)
        {
            return -1;
        }

        temp->setPointer(toDelete->getPointer());
        delete toDelete;
        return 0;
    }

    int search(int targetValue)
    {
        Node *temp = Head;
        int indexFound = 0;

        while (temp != nullptr)
        {
            if (temp->getValue() == targetValue)
            {
                return indexFound;
            }

            indexFound++;
            temp = temp->getPointer();
        }

        return -1;
    }

    void display() const
    {
        Node *temp = Head;
        while (temp != nullptr)
        {
            std::cout << temp->getValue() << " -> ";
            temp = temp->getPointer();
        }
        std::cout << "nullptr\n";
    }

    int count()
    {
        Node *temp = Head;
        int counter = 0;
        while (temp != nullptr)
        {
            counter++;
            temp = temp->getPointer();
        }
        return counter;
    }

    int sum()
    {
        Node *temp = Head;
        int counter = 0;
        while (temp != nullptr)
        {
            counter += temp->getValue();
            temp = temp->getPointer();
        }
        return counter;
    }

    bool isSorted()
    {
        Node *temp = Head;
        bool isAscending = true, isDescending = true;
        while (temp != nullptr && temp->getPointer() != nullptr)
        {
            if (temp->getValue() > temp->getPointer()->getValue())
                isAscending = false;
            if (temp->getValue() < temp->getPointer()->getValue())
                isDescending = false;
            temp = temp->getPointer();
            if (!isAscending && !isDescending)
            {
                return false;
            }
        }
        return isAscending || isDescending;
    }
    Node *reverse()
    {
        Node *curr = Head, *prev = nullptr, *next;
        while (curr != nullptr)
        {
            next = curr->getPointer();
            curr->setPointer(prev);
            prev = curr;
            curr = next;
        }
        Head = prev;
        return Head;
    }
};
int ConcatanateLists(LinkedList &linkedlist1, LinkedList &linkedlist2)
{
    Node *Head1 = linkedlist1.getHead();
    Node *Head2 = linkedlist2.getHead();
    if (Head2 == nullptr)
    {
        return -1;
    }
    if (Head1 == nullptr)
    {
        linkedlist1.setHead(Head2);
        linkedlist2.setHead(nullptr);
        return 1;
    }
    Node *temp = Head1;
    while (temp->getPointer() != nullptr)
    {
        temp = temp->getPointer();
    }
    temp->setPointer(Head2);
    linkedlist2.setHead(nullptr);
    return 1;
}
LinkedList mergeLinkedList(LinkedList &list1, LinkedList &list2)
{
    LinkedList result;
    Node *p1 = list1.getHead();
    Node *p2 = list2.getHead();

    if (!p1 && !p2)
        return result;
    Node dummy(0, nullptr);
    Node *tail = &dummy;

    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->getValue() <= p2->getValue())
        {
            tail->setPointer(p1);
            p1 = p1->getPointer();
        }
        else
        {
            tail->setPointer(p2);
            p2 = p2->getPointer();
        }
        tail = tail->getPointer();
    }
    if (p1 != nullptr)
        tail->setPointer(p1);
    if (p2 != nullptr)
        tail->setPointer(p2);
    result.setHead(dummy.getPointer());
    list1.setHead(nullptr);
    list2.setHead(nullptr);
    return result;
}
class CircularLinkedList
{
private:
    Node *Head;

public:
    CircularLinkedList() : Head(nullptr) {}

    ~CircularLinkedList()
    {
        if (Head == nullptr)
            return;
        Node *curr = Head->getPointer();
        while (curr != Head)
        {
            Node *temp = curr;
            curr = curr->getPointer();
            delete temp;
        }
        delete Head;
    }

    void insert(int val)
    {
        if (Head == nullptr)
        {
            Head = new Node(val, nullptr);
            Head->setPointer(Head);
            return;
        }

        Node *temp = Head;
        while (temp->getPointer() != Head)
        {
            temp = temp->getPointer();
        }

        Node *newNode = new Node(val, Head);
        temp->setPointer(newNode);
    }

    void display() const
    {
        if (Head == nullptr)
        {
            std::cout << "Circular LL is empty\n";
            return;
        }
        Node *temp = Head;
        do
        {
            std::cout << temp->getValue() << " -> ";
            temp = temp->getPointer();
        } while (temp != Head);
        std::cout << "(Head: " << Head->getValue() << ")\n";
    }
};
class NodeDLL
{
public:
    int value;
    NodeDLL *prev;
    NodeDLL *next;

    NodeDLL(int v, NodeDLL *p = nullptr, NodeDLL *n = nullptr)
        : value(v), prev(p), next(n) {}
};
class DoublyLinkedList
{
private:
    NodeDLL *Head;

public:
    DoublyLinkedList() : Head(nullptr) {}

    ~DoublyLinkedList()
    {
        NodeDLL *curr = Head;
        while (curr != nullptr)
        {
            NodeDLL *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    void insert(int val, int index)
    {
        if (index == 0)
        {
            NodeDLL *newNode = new NodeDLL(val, nullptr, Head);
            if (Head != nullptr)
                Head->prev = newNode;
            Head = newNode;
            return;
        }

        NodeDLL *temp = Head;
        for (int i = 0; i < index - 1 && temp != nullptr; i++)
        {
            temp = temp->next;
        }

        if (temp == nullptr)
            return;

        NodeDLL *newNode = new NodeDLL(val, temp, temp->next);
        if (temp->next != nullptr)
        {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }
    void reverse()
    {
        NodeDLL *temp = nullptr;
        NodeDLL *curr = Head;

        while (curr != nullptr)
        {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        if (temp != nullptr)
        {
            Head = temp->prev;
        }
    }

    void display() const
    {
        NodeDLL *temp = Head;
        std::cout << "nullptr <=> ";
        while (temp != nullptr)
        {
            std::cout << temp->value << " <=> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
};

int main()
{
    std::cout << "      Demonstrating Linked List Functions\n\n";

    // 1. Setup Initial Linked List
    LinkedList LL1;
    LL1.insert(10, 0);
    LL1.insert(20, 1);
    LL1.insert(30, 2);
    LL1.insert(40, 3);

    // i. Display
    std::cout << "  i. Displaying LL1: ";
    LL1.display();

    // ii. Count & Sum
    std::cout << "  ii. Count of LL1: " << LL1.count() << "\n";
    std::cout << " Sum of LL1: " << LL1.sum() << "\n";

    // iii. Search
    int key = 30;
    int index = LL1.search(key);
    std::cout << "  iii. Search for " << key << ": "
              << (index != -1 ? "Found at index " + std::to_string(index) : "Not found") << "\n";

    // iv. Delete
    std::cout << "  iv. Deleting element at index 1 (value 20)... \n";
    LL1.remove(1);
    std::cout << " LL1 after deletion: ";
    LL1.display();

    // v. Is Sorted
    std::cout << "  v. Is LL1 sorted? " << (LL1.isSorted() ? "Yes" : "No") << "\n";

    // vi. Reverse
    std::cout << "  vi. Reversing LL1...\n";
    LL1.reverse();
    std::cout << " LL1 after reversal: ";
    LL1.display();

    // vii. Concatenation
    LinkedList LL2;
    LL2.insert(50, 0);
    LL2.insert(60, 1);
    std::cout << "  vii. Concatenating LL1 with LL2 (50 -> 60 -> nullptr)...\n";
    ConcatanateLists(LL1, LL2);
    std::cout << "  LL1 after concatenation: ";
    LL1.display();

    // viii. Merge two sorted lists
    LinkedList sorted1, sorted2;
    sorted1.insert(1, 0);
    sorted1.insert(3, 1);
    sorted1.insert(5, 2);
    sorted2.insert(2, 0);
    sorted2.insert(4, 1);
    sorted2.insert(6, 2);

    std::cout << "  viii. Merging Sorted1 (1->3->5) and Sorted2 (2->4->6)...\n";
    LinkedList mergedList = mergeLinkedList(sorted1, sorted2);
    std::cout << "Merged List: ";
    mergedList.display();

    // ix. Circular Linked List
    std::cout << "  ix. Circular Linked List Creation & Display:\n";
    CircularLinkedList cll;
    cll.insert(100);
    cll.insert(200);
    cll.insert(300);
    std::cout << " CLL Display: ";
    cll.display();

    // x. Doubly Linked List
    std::cout << "  x. Doubly Linked List Creation, Insertion, and Reversal:\n";
    DoublyLinkedList dll;
    dll.insert(5, 0);
    dll.insert(15, 1);
    dll.insert(25, 2);
    std::cout << "DLL Display: ";
    dll.display();
    std::cout << "Reversing DLL...\n";
    dll.reverse();
    std::cout << "DLL Display after Reversal: ";
    dll.display();
    return 0;
}