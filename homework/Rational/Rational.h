#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
using namespace std;

class Rational
{
    // Числитель
    int numer;
    // Знаменатель (>=1)
    int denom;

    void simplify();

public:

    Rational();
    Rational(int number);
    Rational(int n, int d);

    Rational& operator +=(const Rational& r);
    Rational  operator +(const Rational& r) const;

    Rational  operator -() const;
    Rational& operator -=(const Rational& r);
    Rational  operator -(const Rational& r) const;

    Rational& operator *=(const Rational& r);
    Rational  operator *(const Rational& r) const;

    Rational& operator /=(const Rational& r);
    Rational  operator /(const Rational& r) const;

    Rational& operator ++();       // префикс
    Rational  operator ++(int);    // постфикс

    bool operator ==(const Rational& r) const;
    bool operator !=(const Rational& r) const;

    operator int() const;
    operator double() const;

    friend istream& operator >>(istream& in, Rational& r);
    friend ostream& operator <<(ostream& out, const Rational& r);
};

#endif
