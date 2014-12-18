#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iosfwd>
#include <vector>
#include <istream>

struct big_integer
{
    big_integer();
    big_integer(big_integer && other);
    big_integer(big_integer const& other);
    big_integer(int a);
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator=(big_integer const& other);


    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);

    big_integer& operator*=(char rhs);
    big_integer& operator*=(big_integer const& rhs);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);

    big_integer operator+() const;
    big_integer operator-() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend std::string to_string(big_integer const& a);

    friend int absoluteComparator(big_integer const& a, big_integer const& b);

private:
    std::vector<char> digits;
    int sign;
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);

bool operator!=(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);

std::ostream& operator<<(std::ostream& out, big_integer const& a);


#endif // BIG_INTEGER_H