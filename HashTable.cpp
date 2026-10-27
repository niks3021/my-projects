#include <iostream>
#include <string>
#include <functional>

template <typename K, typename V>
class HashTable
{
private:
    struct HashNode
    {
        K key;
        V value;
        HashNode *next;

        HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
        HashNode(const HashNode &other) : key(other.key), value(other.value), next(nullptr) {}
    };
    HashNode **Table;
    int size;
    int capacity;

    int getHash(const K &key) const
    {
        return std::hash<K>{}(key) % capacity;
    }
    void rehash();

public:
    HashTable(int cap = 10) : capacity(cap), size(0)
    {
        Table = new HashNode *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            Table[i] = nullptr;
        }
    }
    HashTable(const HashTable<K, V> &other);
    ~HashTable()
    {
        for (int i = 0; i < capacity; i++)
        {
            HashNode *curr = Table[i];
            while (curr != nullptr)
            {
                HashNode *temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] Table;
    }
    int getCapacity() const { return capacity; }
    bool insert(K newKey, V newValue);
    void display() const;
    bool remove(K key);
    bool get(K key, V &val) const;
    V &operator[](const K &key);
    HashTable& operator=(const HashTable<K, V>& other);
    HashTable<K, V> operator+(const HashTable<K, V>& other) const; 
};
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
    int oldCapacity = capacity;
    HashNode **oldTable = Table;
    capacity = capacity * 2;
    Table = new HashNode *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        Table[i] = nullptr;
    }
    for (int i = 0; i < oldCapacity; i++)
    {
        HashNode *curr = oldTable[i];
        while (curr != nullptr)
        {
            HashNode *next = curr->next;
            int newBucket = getHash(curr->key);
            curr->next = Table[newBucket];
            Table[newBucket] = curr;

            curr = next;
        }
    }
    delete[] oldTable;
}
template <typename K, typename V>
bool HashTable<K, V>::insert(K newKey, V newValue)
{
    if ((double)size / capacity >= 0.75)
    {
        rehash();
    }
    int newHash = getHash(newKey);
    HashNode *curr = Table[newHash];
    while (curr != nullptr)
    {
        if (curr->key == newKey)
        {
            curr->value = newValue;
            return false;
        }
        curr = curr->next;
    }
    HashNode *newNode = new HashNode(newKey, newValue);
    newNode->next = Table[newHash];
    Table[newHash] = newNode;
    size++;

    return true;
}
template <typename K, typename V>
bool HashTable<K, V>::get(K key, V &val) const
{
    int lookHash = getHash(key);
    HashNode *curr = Table[lookHash];
    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            val = curr->value;
            return true;
        }
        curr = curr->next;
    }
    return false;
}
template <typename K, typename V>
bool HashTable<K, V>::remove(K key)
{
    int deleteHash = getHash(key);
    HashNode *curr = Table[deleteHash];
    HashNode *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            if (prev == nullptr)
                Table[deleteHash] = curr->next;
            else
                prev->next = curr->next;
            delete curr;
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false; // not found
}
template <typename K, typename V>
void HashTable<K, V>::display() const
{
    for (int i = 0; i < capacity; i++)
    {
        std::cout << "Bucket " << i << ": ";
        HashNode *curr = Table[i];

        while (curr != nullptr)
        {
            std::cout << "[" << curr->key << ": " << curr->value << "] -> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }
}
template <typename K, typename V>
V &HashTable<K, V>::operator[](const K &key)
{
    int hash = getHash(key);

    HashNode *curr = Table[hash];
    while (curr != nullptr)
    {
        if (curr->key == key)
            return curr->value;
        curr = curr->next;
    }

    insert(key, V());
    curr = Table[hash];
    while (curr != nullptr)
    {
        if (curr->key == key)
            return curr->value;
        curr = curr->next;
    }

    return Table[hash]->value; // just in case
}
template <typename K, typename V>
HashTable<K, V>::HashTable(const HashTable<K, V> &other)
{
    capacity = other.capacity;
    size = other.size;

    Table = new HashNode *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        Table[i] = nullptr;
    }
    for (int i = 0; i < capacity; i++)
    {
        HashNode *curr = other.Table[i];
        HashNode *tail = nullptr;
        while (curr != nullptr)
        {
            HashNode *newNode = new HashNode(*curr);

            if (Table[i] == nullptr)
            {
                Table[i] = newNode;
            }
            else
            {
                tail->next = newNode;
            }
            tail = newNode;
            curr = curr->next;
        }
    }
}
template <typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& other)
{
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < capacity; i++) {
        HashNode* curr = Table[i];
        while (curr != nullptr) {
            HashNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete[] Table;

    capacity = other.capacity;
    size = other.size;

    Table = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++) {
        Table[i] = nullptr;
    }

    for (int i = 0; i < capacity; i++) {
        HashNode* curr = other.Table[i];
        HashNode* tail = nullptr;
        while (curr != nullptr) {
            HashNode* newNode = new HashNode(*curr);
            if (Table[i] == nullptr) {
                Table[i] = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
            curr = curr->next;
        }
    }
    return *this;
}
template <typename K, typename V>
HashTable<K, V> HashTable<K, V>::operator+(const HashTable<K, V>& other) const 
{
    HashTable<K, V> result = *this;

    for (int i = 0; i < other.capacity; i++) 
    {
        HashNode* curr = other.Table[i];
        while (curr != nullptr) 
        {
            result.insert(curr->key, curr->value);
            curr = curr->next;
        }
    }

    return result;
}
int main()
{
    HashTable<int , std::string> spade(18);
    spade[1] = "Ace";
    spade[2] = "Two";
    spade[3] = "Three";
    spade[4] = "Four";
    spade[5] = "Five";
    spade[6] = "Six";
    spade[7] = "Seven";
    spade[8] = "Eight";
    spade[9] = "Nine";
    spade[10] = "Ten";
    spade[11] = "Jack";
    spade[12] = "Queen";
    spade[13] = "King";
    HashTable<int,std::string> clubs(spade);
    HashTable<int,std::string> hearts(18);
    hearts = clubs;
    HashTable<int,std::string> diamond(18);
    diamond = diamond + clubs;
    diamond.display();

}