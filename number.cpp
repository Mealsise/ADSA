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

Number Number::operator-(const Number& other)
{
    if (this->base != other.base)
        throw std::invalid_argument("Bases must be the same for multiplication.");
    
    std::vector<char> result_digits;
    int borrow = 0;
    
    int length_1 = this->digits.size();
    int length_2 = other.digits.size();

    for (int index = 0; index < length_1; index++)
    {
        int digit_1 = this->digits[length_1 - 1 - index] - '0';
        int digit_2 = (index < length_2) ? other.digits[length_2 - 1 - index] - '0' : 0;

        int diff = digit_1 - digit_2 - borrow;

        if (diff < 0)
        {
            diff += this->base;
            borrow = 1;
        }
        else borrow = 0;

        result_digits.push_back(diff + '0');
    }

    while (result_digits.size() > 1 && result_digits.back() == '0') {
        result_digits.pop_back();
    }

    std::reverse(result_digits.begin(), result_digits.end());

    std::string return_str(result_digits.begin(), result_digits.end());

    return Number(return_str, this->base);
}

Number Number::operator*(const Number& other)
{
    if (this->base != other.base)
        throw std::invalid_argument("Bases must be the same for multiplication.");

    Number mod_this = *this;
    Number mod_other = other;

    int length_1 = this->digits.size();
    int length_2 = mod_other.digits.size();

    if (length_1 <= 1 && length_2 <= 1)
    {
        int digit_1 = (length_1 == 1) ? mod_this.digits[0] - '0' : 0;
        int digit_2 = (length_2 == 1) ? mod_other.digits[0] - '0' : 0;
        return Number(digit_1 * digit_2, mod_this.base);
    }

    if (length_1 < length_2) {
        mod_this.digits.insert(mod_this.digits.begin(), length_2 - length_1, '0');
    } else if (length_2 < length_1) {
        mod_other.digits.insert(mod_other.digits.begin(), length_1 - length_2, '0');
    }

    std::pair<Number, Number> split_1 = mod_this.split();
    std::pair<Number, Number> split_2 = mod_other.split();
    Number left_1 = split_1.first;
    Number right_1 = split_1.second;
    Number left_2 = split_2.first;
    Number right_2 = split_2.second;

    Number output_2 = left_1 * left_2;
    Number output_0 = right_1 * right_2;
    Number output_1 = (left_1 + right_1) * (left_2 + right_2) - output_2 - output_0;

    int digit_shift = std::max(right_1.digits.size(), right_2.digits.size());
    output_2.multiplyByBasePower(2 * digit_shift);
    output_1.multiplyByBasePower(digit_shift);

    Number result = output_2 + output_1 + output_0;
    // Ensure no leading zeros in the final result
    while (result.digits.size() > 1 && result.digits[0] == '0') {
        result.digits.erase(result.digits.begin());
    }

    return result;
}

std::pair<Number, Number> Number::split() const
{
    int total_length = this->digits.size();
    int mid = total_length / 2;

    std::vector<char> first_half(this->digits.begin(), this->digits.begin() + mid);
    std::vector<char> second_half(this->digits.begin() + mid, this->digits.end());

    if (total_length % 2) first_half.insert(first_half.begin(), '0');

    std::string first_str(first_half.begin(), first_half.end());
    std::string second_str(second_half.begin(), second_half.end());

    std::pair<Number, Number> output = {Number(first_str, this->base), Number(second_str, this->base)};

    return output;
}

void Number::multiplyByBasePower(int power)
{
    if (power == 0) return;

    this->digits.insert(this->digits.end(), power, '0');
}

std::ostream& operator<<(std::ostream & os, const Number & number)
{
    for (char digit : number.digits)
    {
        os << digit;
    }
    return os;
}