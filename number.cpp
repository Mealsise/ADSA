#include "number.h"

Number::Number(std::string input, int base)
: base(base)
{
    for (char digit : input)
    {
        digits.push_back(digit);
    }
}

std::ostream& operator<<(std::ostream & os, const Number & number)
{
    for (char digit : number.digits)
    {
        os << digit;
    }
    return os;
}