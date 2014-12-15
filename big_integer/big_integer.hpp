#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

//#include <gmp.h>
#include <iosfwd>
#include <vector>
#include <istream>

struct big_integer
{
    big_integer();
    big_integer(big_integer && other);
    big_integer(big_integer const& other);
    //big_integer(std::string s);
    big_integer(int a); // int has the same size as pointer
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator=(big_integer const& other);


    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);

    big_integer& operator*=(char rhs);
    big_integer& operator*=(big_integer const& rhs);
    //big_integer& operator/=(big_integer const& rhs);
    //big_integer& operator%=(big_integer const& rhs);

    //big_integer& operator&=(big_integer const& rhs);
    //big_integer& operator|=(big_integer const& rhs);
    //big_integer& operator^=(big_integer const& rhs);

    //big_integer& operator<<=(int rhs);
    //big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    //big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    bool operator==(big_integer const& b) const;
    bool operator!=(big_integer const& b) const ;
    bool operator<(big_integer const& b) const;
    bool operator>(big_integer const& b) const;
    bool operator<=(big_integer const& b) const;
    bool operator>=(big_integer const& b) const;

    friend std::string to_string(big_integer const& a);
    //operator std::string() const;
    friend int absoluteComparator(big_integer const& a, big_integer const& b);

private:
    std::vector<char> digits;
    int sign;
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
//big_integer operator/(big_integer a, big_integer const& b);
//big_integer operator%(big_integer a, big_integer const& b);

//big_integer operator&(big_integer a, big_integer const& b);
//big_integer operator|(big_integer a, big_integer const& b);
//big_integer operator^(big_integer a, big_integer const& b);

//big_integer operator<<(big_integer a, int b);
//big_integer operator>>(big_integer a, int b);

/*bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);*/


std::ostream& operator<<(std::ostream& out, big_integer const& a);
//std::istream& operator>>(std::istream in, big_integer & a);


#endif // BIG_INTEGER_H