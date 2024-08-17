// Libraries
#include <iostream>
#include <string>

// Header files
#include "number.h"

// Instantiation (because of silly compile command)
#include "number.cpp"

int main(void)
{
    std::string input_line;
    std::getline(std::cin, input_line);

    // Parse input
    int base;
    std::string number_str_1;
    std::string number_str_2;
    size_t space_pos_1 = input_line.find(' ');
    size_t space_pos_2 = input_line.find(' ', space_pos_1 + 1);
    number_str_1 = input_line.substr(0, space_pos_1);
    number_str_2 = input_line.substr(space_pos_1 + 1, space_pos_2 - space_pos_1 - 1);
    base = std::stoi(input_line.substr(space_pos_2 + 1));

    // Create numbers objects
    Number number_1(number_str_1, base);
    Number number_2(number_str_2, base);
    Number sum(1, 10);
    Number product(2, 10);

    // Perform operations
    sum = number_1 + number_2;
    // product = number_1 * number_2;

    // Print results
    std::cout <<
        sum << " " << 
        product << " 0" <<
        std::endl;

    return 0;
}