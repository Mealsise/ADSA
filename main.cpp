#include <iostream>
#include <sstream>
#include <string>
#include "AVL_Tree_Node.h"

int main() {
    std::string input;
    std::getline(std::cin, input); // Get the whole input line
    std::istringstream iss(input);
    std::string command;
    
    AVL_Tree_Node* root = nullptr;

    while (iss >> command) {
        if (command[0] == 'A') {
            // Insert command
            int key = std::stoi(command.substr(1));
            if (root == nullptr) {
                root = new AVL_Tree_Node(key);
            } else {
                root = root->insert(key);
            }
        } else if (command[0] == 'D') {
            // Delete command
            int key = std::stoi(command.substr(1));
            if (root != nullptr) {
                root = root->remove(key);
            }
        } else if (command == "PRE") {
            // Preorder traversal
            if (root != nullptr) {
                root->preorder();
                std::cout << std::endl;
            } else {
                std::cout << "EMPTY" << std::endl;
            }
        } else if (command == "IN") {
            // Inorder traversal
            if (root != nullptr) {
                root->inorder();
                std::cout << std::endl;
            } else {
                std::cout << "EMPTY" << std::endl;
            }
        } else if (command == "POST") {
            // Postorder traversal
            if (root != nullptr) {
                root->postorder();
                std::cout << std::endl;
            } else {
                std::cout << "EMPTY" << std::endl;
            }
        }
    }

    delete root; // Clean up memory
    return 0;
}
