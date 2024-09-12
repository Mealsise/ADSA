#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include <iostream>
#include <algorithm>

class AVL_Tree_Node
{
private:
    AVL_Tree_Node* left;
    AVL_Tree_Node* right;
    int value;
    int height;

public:
    // Constructor
    AVL_Tree_Node(int key) : value(key), left(nullptr), right(nullptr), height(1)
    {}

    // Destructor
    ~AVL_Tree_Node()
    {
        delete left;
        delete right;
    }

    // Get the height of the node
    int getHeight() const
    {
        return height;
    }

    // Get balance factor of node to check if it has become unbalanced
    int getBalance() const
    {
        return (left ? left->getHeight() : 0) - (right ? right->getHeight() : 0);
    }

    // Update the height of the node
    void updateHeight()
    {
        height = 1 + std::max(left ? left->getHeight() : 0, right ? right->getHeight() : 0);
    }

    // Insert a new node with the given key
    AVL_Tree_Node* insert(int key)
    {
        if (key < value)
        {
            if (!left)
            {
                left = new AVL_Tree_Node(key);
            }
            else
            {
                left = left->insert(key);
            }
        }
        else if (key > value)
        {
            if (!right)
            {
                right = new AVL_Tree_Node(key);
            }
            else
            {
                right = right->insert(key);
            }
        }
        else
        {
            // Key already exists, do nothing
            return this;
        }

        updateHeight();
        return balanceTree();
    }

    // Remove a node with the given key
    AVL_Tree_Node* remove(int key)
    {
        if (key < value)
        {
            if (left != nullptr)
            {
                left = left->remove(key);
            }
        }
        else if (key > value)
        {
            if (right != nullptr)
            {
                right = right->remove(key);
            }
        }
        else
        {
            // This is the node to be deleted
            if (left == nullptr || right == nullptr)
            {
                AVL_Tree_Node* temporary = left ? left : right;
                if (temporary == nullptr)
                {
                    temporary = this;
                    delete temporary;
                    return nullptr;
                }
                else
                {
                    *this = *temporary;  // Copy the contents of the non-empty child
                }
            }
            else
            {
                // Node with two children: Get the inorder successor
                AVL_Tree_Node* temporary = right->findMin();
                value = temporary->value;
                right = right->remove(temporary->value);
            }
        }

        if (this == nullptr) return nullptr;

        updateHeight();
        return balanceTree();
    }

    // Find the node with the minimum value
    AVL_Tree_Node* findMin()
    {
        AVL_Tree_Node* current = this;
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    // Rotate right to balance the tree
    AVL_Tree_Node* rotateRight()
    {
        AVL_Tree_Node* x = left;
        AVL_Tree_Node* T2 = x->right;

        // Perform rotation
        x->right = this;
        left = T2;

        // Update heights
        updateHeight();
        x->updateHeight();

        return x;
    }

    // Rotate left to balance the tree
    AVL_Tree_Node* rotateLeft()
    {
        AVL_Tree_Node* y = right;
        AVL_Tree_Node* T2 = y->left;

        // Perform rotation
        y->left = this;
        right = T2;

        // Update heights
        updateHeight();
        y->updateHeight();

        return y;
    }

    // Balance the node according to AVL rules
    AVL_Tree_Node* balanceTree()
    {
        int balance = getBalance();

        // Left Left Case
        if (balance > 1 && getBalance(left) >= 0)
        {
            return rotateRight();
        }

        // Left Right Case
        if (balance > 1 && getBalance(left) < 0)
        {
            left = left->rotateLeft();
            return rotateRight();
        }

        // Right Right Case
        if (balance < -1 && getBalance(right) <= 0)
        {
            return rotateLeft();
        }

        // Right Left Case
        if (balance < -1 && getBalance(right) > 0)
        {
            right = right->rotateRight();
            return rotateLeft();
        }

        return this;  // No balance needed
    }

    // Utility to calculate balance factor of a child node
    int getBalance(AVL_Tree_Node* N)
    {
        if (!N) return 0;
        return N->getBalance();
    }

    // Preorder traversal of the tree
    void preorder()
    {
        std::cout << value << " ";
        if (left) left->preorder();
        if (right) right->preorder();
    }

    // Inorder traversal of the tree
    void inorder()
    {
        if (left) left->inorder();
        std::cout << value << " ";
        if (right) right->inorder();
    }

    // Postorder traversal of the tree
    void postorder()
    {
        if (left) left->postorder();
        if (right) right->postorder();
        std::cout << value << " ";
    }
};

#endif // AVL_TREE_NODE_H
