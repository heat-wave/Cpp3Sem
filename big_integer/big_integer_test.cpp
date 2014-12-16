#include <algorithm>

#include "big_integer.hpp"
#include "exception.cpp"
#include "gtest/gtest.hpp"

TEST(correctness, twoPlusTwo)
{
big_integer a = big_integer(2) + 2,
        b = big_integer(2) + 2;

EXPECT_EQ(big_integer(4), big_integer(2) + big_integer(2));
EXPECT_EQ(4,             big_integer(2) + 2            );
EXPECT_EQ(4,             2             + big_integer(2));
}

TEST(correctness, defaultConstructor)
{
big_integer a;
big_integer b = 0;
EXPECT_EQ(0, a);
EXPECT_EQ(b, a);
}

TEST(correctness, copyConstructor)
{
big_integer a = 3;
big_integer b = a;

EXPECT_EQ(b, a);
EXPECT_EQ(3, b);
}

TEST(correctness, copyConstructorRealCopy)
{
big_integer a = 3;
big_integer b = a;
a = 5;

EXPECT_EQ(3, b);
}

TEST(correctness, copyConstructorRealCopy2)
{
big_integer a = 3;
big_integer b = a;
b = 5;

EXPECT_EQ(3, a);
}

TEST(correctness, assignmentOperator)
{
big_integer a = 4;
big_integer b = 7;
b = a;

EXPECT_TRUE(a == b);
}

TEST(correctness, selfAssignment)
{
big_integer a = 5;
a = a;

EXPECT_TRUE(a == 5);
}

TEST(correctness, assignmentReturnValue)
{
big_integer a = 4;
big_integer b = 7;
(a = b) = a;

EXPECT_TRUE(a == 7);
EXPECT_TRUE(b == 7);
}

TEST(correctness, comparisons)
{
big_integer a = 100;
big_integer b = 100;
big_integer c = 200;

EXPECT_TRUE(a == b);
EXPECT_TRUE(a != c);
EXPECT_TRUE(a < c);
EXPECT_TRUE(c > a);
EXPECT_TRUE(a <= a);
EXPECT_TRUE(a <= b);
EXPECT_TRUE(a <= c);
EXPECT_TRUE(c >= a);
}

TEST(correctness, compareZeroAndMinusZero)
{
big_integer a;
big_integer b = -a;

EXPECT_TRUE(a == b);
}

TEST(correctness, add)
{
big_integer a = 5;
big_integer b = 20;

EXPECT_TRUE(a + b == 25);

a += b;
EXPECT_TRUE(a == 25);
}

TEST(correctness, addSigned)
{
big_integer a = 5;
big_integer b = -20;

EXPECT_TRUE(a + b == -15);

a += b;
EXPECT_TRUE(a == -15);
}

TEST(correctness, addReturnValue)
{
big_integer a = 5;
big_integer b = 1;

(a += b) += b;
EXPECT_EQ(7, a);
}

TEST(correctness, sub)
{
big_integer a = 20;
big_integer b = 5;

EXPECT_TRUE(a - b == 15);

a -= b;
EXPECT_TRUE(a == 15);
}

TEST(correctness, subSigned)
{
big_integer a = 5;
big_integer b = 20;

EXPECT_TRUE(a - b == -15);

a -= b;
EXPECT_TRUE(a == -15);

a -= -100;
EXPECT_TRUE(a == 85);
}

TEST(correctness, subReturnValue)
{
big_integer a = 5;
big_integer b = 1;

(a -= b) -= b;
EXPECT_EQ(3, a);
}

TEST(correctness, mul)
{
big_integer a = 5;
big_integer b = 20;

EXPECT_TRUE(a * b == 100);

a *= b;
EXPECT_TRUE(a == 100);
}

TEST(correctness, mulSigned)
{
big_integer a = -5;
big_integer b = 20;

EXPECT_TRUE(a * b == -100);

a *= b;
EXPECT_TRUE(a == -100);
}

TEST(correctness, mulReturnValue)
{
big_integer a = 5;
big_integer b = 2;

(a *= b) *= b;
EXPECT_EQ(20, a);
}

TEST(correctness, unaryPlus)
{
big_integer a = 123;
big_integer b = +a;

EXPECT_TRUE(a == b);

// this code should not compile:
// &+a;
}

TEST(correctness, negation)
{
big_integer a = 666;
big_integer b = -a;

EXPECT_TRUE(b == -666);
}

TEST(correctness, addLong)
{
big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
big_integer b(                                                     "100000000000000000000000000000000000000");
big_integer c("10000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000");

EXPECT_EQ(c, a + b);
}

TEST(correctness, addLongSigned)
{
big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
big_integer b( "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

EXPECT_EQ(0, a + b);
}

TEST(correctness, addLongSigned2)
{
big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
big_integer b(                                                     "100000000000000000000000000000000000000");
big_integer c( "-999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

EXPECT_EQ(c, a + b);
}

TEST(correctness, addLongPow)
{
big_integer a( "18446744073709551616");
big_integer b("-18446744073709551616");
big_integer c( "36893488147419103232");

EXPECT_EQ(c, a + a);
EXPECT_EQ(a, b + c);
EXPECT_EQ(a, c + b);
}

TEST(correctness, subLong)
{
big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
big_integer b(                                                     "100000000000000000000000000000000000000");
big_integer c( "9999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

EXPECT_EQ(c, a - b);
}

TEST(correctness, mulLong)
{
big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
big_integer b(                                                     "100000000000000000000000000000000000000");
big_integer c("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000");

EXPECT_EQ(c, a * b);
}

TEST(correctness, mulLongSigned)
{
big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
big_integer b(                                                     "100000000000000000000000000000000000000");
big_integer c("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000");

EXPECT_EQ(c, a * b);
}

TEST(correctness, mulLongSigned2)
{
big_integer a("-100000000000000000000000000");
big_integer c( "100000000000000000000000000"
        "00000000000000000000000000");

EXPECT_EQ(c, a * a);
}

TEST(correctness, mulLongPow)
{
big_integer a("18446744073709551616");
big_integer b("340282366920938463463374607431768211456");
big_integer c("115792089237316195423570985008687907853269984665640564039457584007913129639936");

EXPECT_EQ(b, a * a);
EXPECT_EQ(c, b * b);
}

TEST(correctness, negationLong)
{
big_integer a( "10000000000000000000000000000000000000000000000000000");
big_integer c("-10000000000000000000000000000000000000000000000000000");

EXPECT_EQ(c, -a);
EXPECT_EQ(-c, a);
}

TEST(correctness, stringConversion)
{
EXPECT_EQ("100",               to_string(big_integer("100")));
EXPECT_EQ("100",               to_string(big_integer("0100")));
EXPECT_EQ("0",                 to_string(big_integer("0")));
EXPECT_EQ("0",                 to_string(big_integer("-0")));
EXPECT_EQ("-1000000000000000", to_string(big_integer("-1000000000000000")));
}

TEST(correctness, stringExceptions) {
EXPECT_NO_THROW(big_integer("1000000000000000000000000000000000000"));
EXPECT_THROW(big_integer("0abc1"), parse_exception);
EXPECT_THROW(big_integer("--1"),   parse_exception);
EXPECT_THROW(big_integer("1.0"),   parse_exception);
EXPECT_THROW(big_integer(""),      parse_exception);
}