#include <iostream>

template <typename U>
class DoubleNode
{
private:
    U value;
    DoubleNode *next;
    DoubleNode *prev;

public:
    DoubleNode()
    {
        next = nullptr;
        prev = nullptr;
    }
    DoubleNode(U VAL, DoubleNode *P = nullptr, DoubleNode *N = nullptr) : value(VAL), prev(P), next(N) {}
    DoubleNode *getNext() const { return next; }
    DoubleNode *getPrev() const { return prev; }
    U getValue() const { return value; }
    void setNext(DoubleNode *newnext) { next = newnext; }
    void setPrev(DoubleNode *newPrev) { prev = newPrev; }
    void setValue(U newValue) { value = newValue; }
};
template <typename U>
class DoublyLL
{
private:
    using Node = DoubleNode<U>; // Short type alias

    Node *head;
    Node *tail;
    int size;

public:
    DoublyLL() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLL(int S) : head(nullptr), tail(nullptr), size()
    {
        for (int i = 0; i < S; i++)
        {
            append(U());
        }
    }
    ~DoublyLL()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    int getSize() const { return size; }
    bool isEmpty() const { return (head == nullptr); }

    void append(U val)
    {
        Node *newnode = new Node(val);
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            tail->setNext(newnode);
            newnode->setPrev(tail);
            tail = newnode;
        }
        size++;
    }

    void prepend(U val)
    {
        Node *newnode = new Node(val);
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            newnode->setNext(head);
            head->setPrev(newnode);
            head = newnode;
        }
        size++;
    }

    void DisplayForward() const
    {
        std::cout << "Head -> ";
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->getValue() << " -> ";
            temp = temp->getNext();
        }
        std::cout << "Tail\n";
    }

    void DisplayBackwards() const
    {
        std::cout << "tail -> ";
        Node *temp = tail;
        while (temp != nullptr)
        {
            std::cout << temp->getValue() << " -> ";
            temp = temp->getPrev();
        }
        std::cout << "Head\n";
    }
    bool pop_back(U &popped)
    {
        if (tail == nullptr || isEmpty())
            return false;

        Node *temp = tail;
        popped = temp->getValue();
        tail = tail->getPrev();

        if (tail != nullptr)
        {
            tail->setNext(nullptr);
        }
        else
        {
            head = nullptr;
        }

        delete temp;
        size--;
        return true;
    }
    bool pop_back()
    {
        if (tail == nullptr || isEmpty())
            return false;

        Node *temp = tail;
        tail = tail->getPrev();

        if (tail != nullptr)
        {
            tail->setNext(nullptr);
        }
        else
        {
            head = nullptr;
        }

        delete temp;
        size--;
        return true;
    }
    bool pop_front(U &popped)
    {
        if (head == nullptr || isEmpty())
            return false;

        Node *temp = head;
        popped = temp->getValue();
        head = head->getNext();

        if (head != nullptr)
        {
            head->setPrev(nullptr);
        }
        else
        {
            tail = nullptr;
        }

        delete temp;
        size--;
        return true;
    }
    bool pop_front()
    {
        if (head == nullptr || isEmpty())
            return false;

        Node *temp = head;
        head = head->getNext();

        if (head != nullptr)
        {
            head->setPrev(nullptr);
        }
        else
        {
            tail = nullptr;
        }

        delete temp;
        size--;
        return true;
    }
    Node *getNodeAt(int index) const
    {
        if (index < 0 || index >= size)
            return nullptr;

        Node *curr = nullptr;

        if (index < size / 2)
        {
            curr = head;
            for (int i = 0; i < index; i++)
            {
                curr = curr->getNext();
            }
        }
        else
        {
            curr = tail;
            for (int i = size - 1; i > index; i--)
            {
                curr = curr->getPrev();
            }
        }
        return curr;
    }
    bool insert(U val, int index)
    {
        if (index < 0 || index > size)
        {
            return false;
        }
        if (index == 0)
        {
            prepend(val);
            return true;
        }
        if (index == size)
        {
            append(val);
            return true;
        }

        Node *target = getNodeAt(index);
        Node *prevNode = target->getPrev();

        Node *newnode = new Node(val, prevNode, target);

        prevNode->setNext(newnode);
        target->setPrev(newnode);

        size++;
        return true;
    }
    bool remove(int index)
    {
        if (index < 0 || index >= size)
        {
            return false;
        }

        if (index == 0)
        {
            pop_front();
            return true;
        }

        if (index == size - 1)
        {
            pop_back();
            return true;
        }

        Node *target = getNodeAt(index);
        Node *prevNode = target->getPrev();
        Node *nextNode = target->getNext();

        prevNode->setNext(nextNode);
        nextNode->setPrev(prevNode);

        delete target;
        size--;
        return true;
    }
    bool update(int index, U newVal)
    {
        Node *target = getNodeAt(index);
        if (target == nullptr)
        {
            return false;
        }
        target->setValue(newVal);
        return true;
    }
};
int main()
{
    DoublyLL<int> Mylist(5);
    std::cout << Mylist.getSize()<< "\n";
    Mylist.insert(5, 0);
    std::cout << Mylist.getSize()<< "\n";
    Mylist.update(5, 0);
    std::cout << Mylist.getSize()<<"\n";
    DoublyLL<int> Mylist2;
    std::cout << Mylist2.getSize()<< "\n";
    Mylist2.insert(5, 0);
    std::cout << Mylist2.getSize()<<"\n";
    
    return 0;
}