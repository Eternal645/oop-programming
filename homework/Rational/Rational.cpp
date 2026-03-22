#include "rational.h"
#include <cmath>
#include <iostream>
#include <locale.h>

using namespace std;

void Rational::reduce()
{
    if (denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }

    int a = std::abs(numer);
    int b = std::abs(denom);

    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }

    if (a > 1)
    {
        numer /= a;
        denom /= a;
    }
}

Rational::Rational() : numer(0), denom(1) {}

Rational::Rational(int n) : numer(n), denom(1) {}

Rational::Rational(int n, int d) : numer(n), denom(d)
{
    reduce();
}

Rational Rational::operator-() const
{
    return Rational(-numer, denom);
}

Rational &Rational::operator+=(const Rational &r)
{
    numer = numer * r.denom + r.numer * denom;
    denom = denom * r.denom;
    reduce();
    return *this;
}

Rational &Rational::operator-=(const Rational &r)
{
    return *this += -r;
}

Rational Rational::operator+(const Rational &r) const
{
    Rational tmp(*this);
    return tmp += r;
}

Rational Rational::operator-(const Rational &r) const
{
    Rational tmp(*this);
    return tmp -= r;
}

Rational &Rational::operator++()
{
    numer += denom;
    return *this;
}

Rational Rational::operator++(int)
{
    Rational tmp(*this);
    numer += denom;
    return tmp;
}

bool Rational::operator==(const Rational &r) const
{
    return numer == r.numer && denom == r.denom;
}

bool Rational::operator!=(const Rational &r) const
{
    return !(*this == r);
}

Rational::operator int() const
{
    return numer / denom;
}

Rational::operator double() const
{
    return (double)numer / denom;
}

std::istream &operator>>(std::istream &in, Rational &r)
{
    in >> r.numer >> r.denom;
    r.reduce();
    return in;
}

std::ostream &operator<<(std::ostream &out, const Rational &r)
{
    out << r.numer << "/" << r.denom;
    return out;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Rational a(1, 2), b(-1, 6);
    cout << "a = " << a << ", b = " << b << endl;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;

    Rational c = a;
    c += b;
    cout << "a += b => " << c << endl;

    cout << "++a = " << ++a << endl;
    cout << "a++ = " << a++ << ", после: a = " << a << endl;

    cout << "a == b: " << (a == b ? "true" : "false") << endl;
    cout << "a != b: " << (a != b ? "true" : "false") << endl;

    cout << "a как double = " << (double)a << endl;
    cout << "a как int    = " << (int)a << endl;

    Rational g;
    cout << "Введите дробь (числитель знаменатель): ";
    cin >> g;
    cout << "Вы ввели: " << g << endl;

    return 0;
}