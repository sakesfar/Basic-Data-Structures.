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

    void destroy_tree(Node* leaf)
    {
        if (leaf != nullptr)
        {
            destroy_tree(leaf->right);
            destroy_tree(leaf->left);
            delete leaf;
        }
    }

    Node* m_root;

public:
    BTree(const Object& obj = Object{})
    {
        m_root = new Node;
        m_root->data = obj;
        m_root->left = nullptr;
        m_root->right = nullptr;
    }

    ~BTree() 
    {
        destroy_tree(m_root);
    }

    void insert(const Object& obj,  Node* leaf)
    {
        if (obj < leaf->data)
        {
            if (leaf->left != nullptr)            
                insert(obj, leaf->left);
            else
            {
                leaf->left = new Node;
                leaf->left->data = obj;
                leaf->left->left = nullptr;
                leaf->left->right = nullptr;
            }
            
        }

        else if (obj >= leaf->data)
        {
            if (leaf->right != nullptr)
                insert(obj, leaf->right);
            else
            {
                leaf->right = new Node;
                leaf->right->data = obj;
                leaf->right->left = nullptr;
                leaf->right->right = nullptr;
            }

        }
    }

    Node* search(const Object& obj, const Node* leaf)
    {
        if (leaf != nullptr)
        {
            if (obj == leaf->data)
                return leaf;

            if (obj < leaf->data)
                return search(obj, leaf->left);
            else
                return search(obj, leaf->right);
        }

        else
        {
            std::cout << "COULD NOT FIND REQUESTED DATA!\n";
            return nullptr;
        }
    }

    Node* getRoot()
    {
        return m_root;
    }

    void printDataAscending(const Node* root )
    {

        if (root != nullptr)
        {
            printDataAscending(root->left);
            std::cout << " " << root->data;
            printDataAscending(root->right);
        }

        else
        {
            //std::cout << "\nEND!\n";
            return;
        }
    }

};

int main()
{
    BTree<int> binTree{ 8 };
    binTree.insert(10, binTree.getRoot());
    binTree.insert(15, binTree.getRoot());
    binTree.insert(2, binTree.getRoot());
    binTree.insert(16, binTree.getRoot());
    binTree.insert(21, binTree.getRoot());
    binTree.insert(28, binTree.getRoot());
    binTree.insert(29, binTree.getRoot());
    binTree.insert(5, binTree.getRoot());
    binTree.insert(35, binTree.getRoot());
    binTree.printDataAscending(binTree.getRoot());

    return 0;

}

