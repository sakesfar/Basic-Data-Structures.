#include <iostream>

template <typename Object>
class BTree
{
private:
    struct Node
    {
        Object data;
        Node* left;
        Node* right;
    };

    Node* m_root = nullptr;

    void destroy_tree(Node* leaf)
    {
        if (leaf != nullptr)
        {
            destroy_tree(leaf->right);
            destroy_tree(leaf->left);
            delete leaf;
        }
    }

    void insert(const Object& obj, Node*& leaf)
    {
        if (leaf == nullptr)
        {
            leaf = new Node;
            leaf->data = obj;
            leaf->left = nullptr;
            leaf->right = nullptr;
            return;
        }

        if (obj < leaf->data)
        {
            insert(obj, leaf->left);
        }
        else
        {
            insert(obj, leaf->right);
        }
    }

    Node* search(const Object& obj, const Node* leaf) const
    {
        if (leaf == nullptr)
        {
            return nullptr;
        }

        if (obj == leaf->data)
            return leaf;

        if (obj < leaf->data)
            return search(obj, leaf->left);
        else
            return search(obj, leaf->right);
    }

public:
    BTree() = default;

    ~BTree() 
    {
        destroy_tree(m_root);
    }

    void insert(const Object& obj)
    {
        insert(obj, m_root);
    }

    Node* search(const Object& obj) const
    {
        Node* result = search(obj, m_root);
        if (result == nullptr)
        {
            std::cout << "COULD NOT FIND REQUESTED DATA!\n";
        }
        return result;
    }

    Node* getRoot() const
    {
        return m_root;
    }

    void printDataAscending(const Node* root) const
    {
        if (root != nullptr)
        {
            printDataAscending(root->left);
            std::cout << " " << root->data;
            printDataAscending(root->right);
        }
    }

    Node* findMax(Node* root) const
    {
        Node* temp = root;
        while (temp && temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }

    Node* findMin(Node* root) const
    {
        Node* temp = root;
        while (temp && temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }
};
