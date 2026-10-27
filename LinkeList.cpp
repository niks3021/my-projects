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

    int swap(int target1, int target2)
    {
        Node *prev1 = nullptr, *curr1 = Head;
        for (int i = 0; i < target1 && curr1 != nullptr; i++)
        {
            prev1 = curr1;
            curr1 = curr1->getPointer();
        }

        Node *prev2 = nullptr, *curr2 = Head;
        for (int i = 0; i < target2 && curr2 != nullptr; i++)
        {
            prev2 = curr2;
            curr2 = curr2->getPointer();
        }

        if (curr1 == nullptr || curr2 == nullptr)
        {
            return -1;
        }

        if (curr1 == curr2)
        {
            return 0;
        }
        Node *next1 = curr1->getPointer();
        Node *next2 = curr2->getPointer();

        if (next1 == curr2)
        {
            if (prev1 == nullptr)
                Head = curr2;
            else
                prev1->setPointer(curr2);

            curr2->setPointer(curr1);
            curr1->setPointer(next2);
        }
        else if (next2 == curr1)
        {
            if (prev2 == nullptr)
                Head = curr1;
            else
                prev2->setPointer(curr1);

            curr1->setPointer(curr2);
            curr2->setPointer(next1);
        }
        else
        {
            if (prev1 == nullptr)
                Head = curr2;
            else
                prev1->setPointer(curr2);

            if (prev2 == nullptr)
                Head = curr1;
            else
                prev2->setPointer(curr1);

            curr1->setPointer(next2);
            curr2->setPointer(next1);
        }
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

    void print() const
    {
        Node *temp = Head;
        while (temp != nullptr)
        {
            std::cout << temp->getValue() << " -> ";
            temp = temp->getPointer();
        }
        std::cout << "nullptr\n";
    }
};

int main()
{
    LinkedList list;
    int insertValue;
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Enter value at index : "<< i << " : ";
        std::cin >> insertValue;
        list.insert(insertValue, i);
    }
    list.print();

    std::cout << " Which element would you like delete: ";
    int target;
    std::cin >> target;
    target = list.search(target);
    if(target == -1)
    {
        std::cout << "Target Not found";
        return -1;
    }
    list.remove(target);
    list.print();
}