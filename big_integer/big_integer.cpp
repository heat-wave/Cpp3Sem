#include "big_integer.hpp"
#include <iostream>
#include <algorithm>
#include "exception.cpp"

//constructors
//default
big_integer::big_integer() {
    sign = 0;
    digits = std::vector<char>('0');
};

//move
big_integer::big_integer(big_integer && other) {
    *this = other;
};

//copy
big_integer::big_integer(big_integer const& copy) {
    this->sign = copy.sign;
    this->digits = copy.digits;
};

//integer
big_integer::big_integer(int number) {
    long long int extended = number;
    extended = std::abs(extended);
    if (number < 0) {
        sign = -1;
    }
    else if (number == 0) {
        sign = 0;
        digits = std::vector<char>('0');
    }
    else {
        sign = 1;
    }
    while (extended > 0) {
        this->digits.push_back(extended % 10);
        extended /= 10;
    }
};

//string
big_integer::big_integer(std::string const& str) {
    if (str == "" || str == "0") {
        *this = big_integer();
    }
    else {
        std::string temp = str;
        int cut = 0;
        if (temp.at(0) == '-')
            cut = 1;
        while (temp.at(cut) == '0' && cut < temp.size() - 1)
            temp.erase(cut, cut);
        if (temp == "0" || temp == "-0" || temp == "") {
            *this = big_integer();
            return;
        }
        std::reverse(temp.begin(), temp.end());
        for (int i = 0; i < temp.size() - 1; ++i) {
            if (!isdigit(temp[i])) {
                throw parse_exception("Illegal character");
            }
            this->digits.push_back(temp[i] - 48);
        }
        if (temp[temp.size() - 1] == '-') {
            sign = -1;
        }
        else {
            sign = 1;
            this->digits.push_back(temp[temp.size() - 1] - 48);
        }
    }
};

//destructor
big_integer::~big_integer() {
};

//assignment
big_integer& big_integer::operator=(big_integer const& other) {
    this->digits = other.digits;
    this->sign = other.sign;
    return *this;
};

//add
big_integer& big_integer::operator+=(big_integer const& rhs) {
    if (sign == 0) {
        *this = rhs;
        return *this;
    }
    if (rhs.sign == 0)
        return *this;
    if (sign == rhs.sign) {
        int carry = 0;
        for (int i = 0; i < std::max(digits.size(), rhs.digits.size()) || carry; ++i) {
            if (i == digits.size())
                digits.push_back(0);
            digits[i] += carry + (i < rhs.digits.size() ? rhs.digits[i] : 0);
            carry = digits[i] >= 10;
            if (carry) digits[i] -= 10;
        }
        return *this;
    }
    else {
        big_integer temp;
        switch (absolute_comparator(*this, rhs)) {
            case 0:
                *this = big_integer();
                return *this;
            case 1:
                if (sign == 1) {
                    *this -= -rhs;
                }
                else {
                    sign = 1;
                    *this -= rhs;
                    sign = -1;
                }
                return *this;
            case -1:
                sign = -sign;
                temp = rhs - *this;
                *this = temp;
                return *this;
            default:
            	break;
        }
        return *this;
    }

};

//subtract
big_integer& big_integer::operator-=(big_integer const& rhs) {
    if (sign == rhs.sign) {
        big_integer temp;
        switch (absolute_comparator(*this, rhs)) {
            case 0:
                *this = big_integer();
                return *this;
            case 1:
            	break;
            case -1:
                temp = rhs - *this;
                temp.sign = -temp.sign;
                *this = temp;
                return *this;
            default:
            	break;
        }
        int carry = 0;
        for (int i = 0; i < rhs.digits.size() || carry; ++i) {
            digits[i] -= carry + (i < rhs.digits.size() ? rhs.digits[i] : 0);
            carry = digits[i] < 0;
            if (carry) digits[i] += 10;
        }
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        return *this;
    }
    else {
            *this += -rhs;
            return *this;
    }
};

//multiply by a one-digit number
big_integer& big_integer::operator*=(char rhs) {
    int carry = 0;
    for (int i = 0; i < digits.size() || carry; ++i) {
        if (i == digits.size())
            digits.push_back (0);
        long long cur = carry + digits[i] * 1ll * rhs;
        digits[i] = int (cur % 10);
        carry = int (cur / 10);
    }
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
    return *this;
};

//multiply by an arbitrary big_integer
big_integer& big_integer::operator*=(big_integer const& rhs) {
    sign *= rhs.sign;
    if (!sign)
        return *this;
    big_integer temp1 = *this, temp2 = 0;
    for (int i = 0; i < rhs.digits.size(); i++) {
        temp1 *= rhs.digits[i];
        for (int j = 0; j < i; j++)
            temp1.digits.insert(temp1.digits.begin(), 0);
        temp2 += temp1;
        temp1 = *this;
    }
    return *this = temp2;
};

//unary operators
big_integer big_integer::operator+() const
{
    return *this;
}

big_integer big_integer::operator-() const
{
    big_integer temp(*this);
    temp.sign = -temp.sign;
    return temp;
}

//increment & decrement
big_integer& big_integer::operator++() {
    return *this += 1;
}

big_integer big_integer::operator++(int) {
    big_integer temp(*this);
    ++*this;
    return temp;
}

big_integer& big_integer::operator--() {
    return *this -= 1;
}

big_integer big_integer::operator--(int) {
    big_integer temp(*this);
    --*this;
    return temp;
}


//binary operators
big_integer operator+(big_integer a, big_integer const& b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b) {
    return a *= b;
}

//converting a big_integer to a string representation
std::string to_string(big_integer const &a) {
    std::string aux;
    for (int i = a.digits.size() - 1; i >= 0; --i) {
        aux += ('0' + a.digits[i]);
    }
    if (a.sign == -1) {
        aux.insert(0, "-", 1);
    }
    return aux;
}

//stream operations
std::ostream& operator<<(std::ostream& out, big_integer const& a) {
    return out << to_string(a);
}

std::istream& operator>>(std::istream in, big_integer & a) {
    std::string tmp;
    in >> tmp;
    a = big_integer(tmp);
    return in;
}

//auxiliary method for comparing two big_integers
//disregarding their sign
int absolute_comparator(big_integer const &a, big_integer const &b) {
    if (a.digits.size() > b.digits.size()) {
        return 1;
    }
    else if (a.digits.size() < b.digits.size()) {
        return -1;
    }
    else {
        for (int i = a.digits.size() - 1; i >= 0; i--) {
            if (a.digits[i] > b.digits[i]) {
                return 1;
            }
            else if (a.digits[i] < b.digits[i]) {
                return -1;
            }
        }
    }
    return 0;
}

//comparison
bool operator==(big_integer const& a, big_integer const& b)  {
    return (a.digits == b.digits && a.sign == b.sign);
}

bool operator!=(big_integer const& a, big_integer const& b)  {
    return (!(a == b));
}

bool operator<(big_integer const& a, big_integer const& b)  {
    if (a == b)
        return false;
    if (a.sign == -1 && b.sign == 1)
        return true;
    if (a.sign == 1 && b.sign == -1)
        return false;
    if (absoluteComparator(a, b) == 1) {
        if (a.sign == 1)
            return false;
        else
            return true;
    }
    else {
        if (a.sign == 1)
            return true;
        else
            return false;
    }
}

bool operator>(big_integer const& a, big_integer const& b)  {
    return (-a < -b);
}

bool operator<=(big_integer const& a, big_integer const& b)  {
    return (a < b || a == b);
}

bool operator>=(big_integer const& a, big_integer const& b) {
    return (a > b || a == b);
}