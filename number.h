#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <string>
#include <iostream>

class Number {
private:
    std::vector<char> digits;
    int base;

public:
    Number(int input, int base);
    Number(std::string input, int base);

    // Number operator+(const Number& other);
    // Number operator*(const Number& other);

    // Number operator+(const int other) {this + Number(other, this->base)}
    // Number operator*(const int other) {this * Number(other, this->base)}

    friend std::ostream& operator<<(std::ostream& os, const Number& number);
};

#endif // NUMBER_H