#include <algorithm>

#include "number.h"

Number::Number(int input, int base)
: base(base)
{
    if (input == 0)
    {
        digits.push_back('0');
    }
    else
    {
        while (input > 0)
        {
            int remainder = input % base;
            digits.push_back(remainder + '0');
            input /= base;
        }

        std::reverse(digits.begin(), digits.end());
    }
}

Number::Number(std::string input, int base)
: base(base)
{
  for (char digit : input) {
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