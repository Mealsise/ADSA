#include <iostream>
#include "number.h"


#include "number.cpp"

int main(void)
{
    Number number = Number("1234", 10);
    std::cout << number << std::endl;
}