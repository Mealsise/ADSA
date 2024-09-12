#include <iostream>
#include <sstream>
#include <string>
#include "AVL_Tree_Node.h"

// Function to trim leading and trailing spaces from a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return ""; // Empty or all spaces
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

int main() {
    std::string input;
    AVL_Tree_Node* root = nullptr;
    
    // Keep reading until end of input
    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        std::string command;

        while (iss >> command) {
            command = trim(command);
            // std::cout << command << std::endl;
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
    }
    delete root; // Clean up memory
    return 0;
}




