#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
    bool isLeaf;
    std::vector<int> keys;
    Node(bool leafstatus) : isLeaf(leafstatus) {}
    virtual ~Node() = default;
};
struct Leaf : public Node
{
    Leaf *next;
    Leaf() : Node(true), next(nullptr) {}
};
struct internal : public Node
{
    std::vector<Node *> children;
    internal() : Node(false) {}
};
class Bplus
{
private:
    Node *root;
    int m;
    Node *insertInternal(int key, Node *node, int &promotedkey)
    {
        if (node->isLeaf)
        {
            auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
            node->keys.insert(it, key);
            if (node->keys.size() == m)
            {
                Leaf *leaf = static_cast<Leaf *>(node);
                Leaf *newLeaf = new Leaf();

                int mid = m / 2;
                newLeaf->keys.assign(leaf->keys.begin() + mid, leaf->keys.end());
                leaf->keys.erase(leaf->keys.begin() + mid, leaf->keys.end());

                newLeaf->next = leaf->next;
                leaf->next = newLeaf;

                promotedkey = newLeaf->keys[0];
                return newLeaf;
            }

            return nullptr;
        }
        else
        {
            internal *Internal = static_cast<internal *>(node);

            int idx = 0;
            while (idx < Internal->keys.size() && key >= Internal->keys[idx])
            {
                idx++;
            }

            int newPromotedKey;
            Node *newChild = insertInternal(key, Internal->children[idx], newPromotedKey);

            if (newChild != nullptr)
            {
                Internal->keys.insert(Internal->keys.begin() + idx, newPromotedKey);
                Internal->children.insert(Internal->children.begin() + idx + 1, newChild);

                if (Internal->keys.size() == m)
                {
                    internal *newInternal = new internal();
                    int mid = m / 2;

                    promotedkey = Internal->keys[mid];

                    newInternal->keys.assign(Internal->keys.begin() + mid + 1, Internal->keys.end());
                    newInternal->children.assign(Internal->children.begin() + mid + 1, Internal->children.end());

                    Internal->keys.erase(Internal->keys.begin() + mid, Internal->keys.end());
                    Internal->children.erase(Internal->children.begin() + mid + 1, Internal->children.end());

                    return newInternal;
                }
            }
            return nullptr;
        }
    }

public:
    Bplus(int order) : m(order), root(nullptr) {}

    void insert(int key)
    {
        if (root == nullptr)
        {
            root = new Leaf();
            root->keys.push_back(key);
            return;
        }
        // if not root lets ofload to helper
        int promotedkey;
        Node *newChild = insertInternal(key, root, promotedkey);
        if (newChild != nullptr)
        {
            internal *newRoot = new internal();
            newRoot->keys.push_back(promotedkey);
            newRoot->children.push_back(root);
            newRoot->children.push_back(newChild);
            root = newRoot;
        }
    }
};

int main()
{
    Bplus B(4);
    return 0;
}