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

Number Number::operator+(const Number& other)
{
    if (this->base != other.base)
        throw std::invalid_argument("Bases must be the same for addition.");

    std::vector<char> result_digits;
    int carry = 0;

    // grab lengths
    int length_1 = this->digits.size();
    int length_2 = other.digits.size();
    int max_len = std::max(length_1, length_2);

    // add digits together
    for (int index = 0; index < max_len; index++)
    {
        int digit_1 = (index < length_1) ? this->digits[length_1 - 1 - index] - '0' : 0;
        int digit_2 = (index < length_2) ? other.digits[length_2 - 1 - index] - '0' : 0;

        int sum = digit_1 + digit_2 + carry;
        carry = sum / this->base;
        sum = sum % this->base;

        result_digits.push_back(sum + '0');
    }

    if (carry > 0)
        result_digits.push_back(carry + '0');
    
    std::reverse(result_digits.begin(), result_digits.end());

    std::string return_str(result_digits.begin(), result_digits.end());

    return Number(return_str, this->base);
}

std::ostream& operator<<(std::ostream & os, const Number & number)
{
    for (char digit : number.digits)
    {
        os << digit;
    }
    return os;
}