#include "big_integer.hpp"
#include <iostream>
#include <algorithm


big_integer::big_integer() {
    sign = 0;
    digits = std::vector<char>('0');
};

big_integer::big_integer(big_integer && other) {
    *this = other;
};

big_integer::big_integer(big_integer const& copy) {
    sign = copy.sign;
    digits = copy.digits;
};

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

big_integer::big_integer(std::string const& str) {
    if (str == "" || str == "0") {
        *this = big_integer();
    }
    else {
        if (str[0] == '-') {
            sign = -1;
        }
        else {
            sign = 1;
            this->digits.push_back(str[0] - 48);
        }
        for (int i = 1; i < str.size(); ++i) {
            if (!isdigit(str[i])) {
                //TODO:exceptions
            }
            this->digits.push_back(str[i] - 48);
        }
    }
};

big_integer::~big_integer() {
};

big_integer& big_integer::operator=(big_integer const& other) {
    this->digits = other.digits;
    this->sign = other.sign;
    return *this;
};

big_integer& big_integer::operator+=(big_integer const& rhs) {
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
        switch (absoluteComparator(*this, rhs)) {
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
                *this = rhs - *this;
                return *this;
            default:;
        }
        return *this;
    }

};

big_integer& big_integer::operator-=(big_integer const& rhs) {
    if (sign == rhs.sign) {
        int carry = 0;
        for (int i = 0; i < rhs.digits.size() || carry; ++i) {
            digits[i] -= carry + (i < rhs.digits.size() ? rhs.digits[i] : 0);
            carry = digits[i] < 0;
            if (carry) digits[i] += 10;
        }
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
    }
    else {
            *this += -rhs;
            return *this;
    }
};

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
};
big_integer& big_integer::operator*=(big_integer const& rhs) {
    sign *= rhs.sign;
    if (!sign)
        return *this;
    big_integer temp1 = *this, temp2 = 0;
    for (int i = 0; i < rhs.digits.size(); i++) {
        temp1 *= rhs.digits[i];
        for (int j = 0; j < i; j++)
            temp1.digits.insert(digits.begin(), 0);
        temp2 += temp1;
        temp1 = *this;
    }
    return *this = temp2;

};

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

bool big_integer::operator==(big_integer const& b) const {
    return (this->digits == b.digits && this->sign == b.sign);
}

bool big_integer::operator!=(big_integer const& b) const {
    return (!(*this == b));
}

bool big_integer::operator<(big_integer const& b) const {
    if (*this == b)
        return false;
    if (this->sign == -1 && b.sign == 1)
        return true;
    if (this->sign == 1 && b.sign == -1)
        return false;
    if (absoluteComparator(*this, b) == 1) {
        if (sign == 1)
            return false;
        else
            return true;
    }
    else {
        if (sign == 1)
            return true;
        else
            return false;
    }
}

bool big_integer::operator>(big_integer const& b) const {
    return (-*this < -b);
}

bool big_integer::operator<=(big_integer const& b) const {
    return (*this < b || *this == b);
}

bool big_integer::operator>=(big_integer const& b) const{
    return (*this > b || *this == b);
}

big_integer operator+(big_integer a, big_integer const& b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b) {
    return a *= b;
}

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

//operator std::string() const;

std::ostream& operator<<(std::ostream& out, big_integer const& a) {
    return out << to_string(a);
}

std::istream& operator>>(std::istream in, big_integer & a) {
    std::string tmp;
    in >> tmp;
    a = big_integer(tmp);
    return in;
}

int absoluteComparator(big_integer const& a, big_integer const& b) {
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
