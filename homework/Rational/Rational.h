#pragma once
#include <cmath>
#include <iostream>

class Rational
{
    int numer;
    int denom;

    void reduce();

public:
    Rational();
    Rational(int n);
    Rational(int n, int d);

    Rational operator-() const;

    Rational &operator+=(const Rational &r);
    Rational &operator-=(const Rational &r);

    Rational operator+(const Rational &r) const;
    Rational operator-(const Rational &r) const;

    Rational &operator++();
    Rational operator++(int);

    bool operator==(const Rational &r) const;
    bool operator!=(const Rational &r) const;

    operator int() const;
    operator double() const;

    friend std::istream &operator>>(std::istream &in, Rational &r);
    friend std::ostream &operator<<(std::ostream &out, const Rational &r);
};