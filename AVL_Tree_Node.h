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
    AVL_Tree_Node(int value)
        : value(value), left(nullptr), right(nullptr), height(1) {}

    ~AVL_Tree_Node()
    {
        delete left;
        delete right;
    }

    int getHeight() {return height;}

    int getBalance() {return (left ? left->getHeight() : 0) - (right ? right->getHeight() : 0);}

    void updateHeight() {height = 1 + std::max(left ? left->getHeight() : 0, right ? right->getHeight() : 0);}

    AVL_Tree_Node* insert(int key) {
        if (key < value)
        {
            if (!left) left = new AVL_Tree_Node(key);
            else left = left->insert(key);
        }
        else if (key > value)
        {
            if (!right) right = new AVL_Tree_Node(key);
            else right = right->insert(key);
        }
        else
            return this;

        // Update height after insertion
        updateHeight();

        int balance = getBalance();

        // Left heavy case
        if (balance > 1)
        {
            if (key < left->value)
                return rotateRight(); // Left-Left case
            else if (key > left->value)
            {
                left = left->rotateLeft();
                return rotateRight(); // Left-Right case
            }
        }

        // Right heavy case
        if (balance < -1)
        {
            if (key > right->value)
                return rotateLeft(); // Right-Right case
            if (key < right->value)
            {
                right = right->rotateRight();
                return rotateLeft(); // Right-Left case
            }
        }

        return this;
    }

    AVL_Tree_Node* findMin() {return left ? left->findMin() : this;}

    AVL_Tree_Node* remove(int key) {
        if (key < value) {
            if (left) left = left->remove(key);
        } else if (key > value) {
            if (right) right = right->remove(key);
        } else
        {
            // Node to delete found
            if (!left || !right) 
            {
                // One child or no child case
                AVL_Tree_Node* temp = left ? left : right;
                delete this;
                return temp;
            }
            else
            {
                // Node with two children
                AVL_Tree_Node* temp = right->findMin();
                value = temp->value;
                right = right->remove(temp->value);
            }
        }

        // Update height after deletion
        updateHeight();

        int balance = getBalance();

        // Left heavy case
        if (balance > 1)
        {
            if (left->getBalance() >= 0)
                return rotateRight(); // Left-Left case
            else
            {
                left = left->rotateLeft();
                return rotateRight(); // Left-Right case
            }
        }

        // Right heavy case
        if (balance < -1)
        {
            if (right->getBalance() <= 0)
                return rotateLeft(); // Right-Right case
            else
            {
                right = right->rotateRight();
                return rotateLeft(); // Right-Left case
            }
        }

        return this;
    }

    void preorder(){std::cout << value << " "; if (left) left->preorder(); if (right) right->preorder();}

    void inorder(){if (left) left->inorder(); std::cout << value << " "; if (right) right->inorder();}

    void postorder() {if (left) left->postorder(); if (right) right->postorder(); std::cout << value << " ";}

    AVL_Tree_Node* getLeft() {return left;}

    AVL_Tree_Node* getRight() {return right;}

    AVL_Tree_Node* rotateRight() {
        AVL_Tree_Node* newRoot = left;
        left = newRoot->right;
        newRoot->right = this;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    AVL_Tree_Node* rotateLeft() {
        AVL_Tree_Node* newRoot = right;
        right = newRoot->left;
        newRoot->left = this;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }
};

#endif // AVL_TREE_NODE_H
