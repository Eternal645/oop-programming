#include "Function.h"

double Function::findMin(double a, double b, double step) const {
    double min = f(a);
    for (double x = a + step; x <= b; x += step)
        if (f(x) < min) min = f(x);
    return min;
}

double Function::findMax(double a, double b, double step) const {
    double max = f(a);
    for (double x = a + step; x <= b; x += step)
        if (f(x) > max) max = f(x);
    return max;
}

double Function::integrate(double a, double b, int n) const {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i)
        sum += f(a + i * h);
    return sum * h;
}

double Function::differentiate(double x, double h) const {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

Hiperbola::Hiperbola(double a) : a(a) {}

double Hiperbola::f(double x) const {
    return a / x;
}

void Hiperbola::print(double x) const {
    std::cout << "Hiperbola f(" << x << ") = " << f(x) << "\n";
}

Parabola::Parabola(double a, double b, double c) : a(a), b(b), c(c) {}

double Parabola::f(double x) const {
    return a * x * x + b * x + c;
}

void Parabola::print(double x) const {
    std::cout << "Parabola f(" << x << ") = " << f(x) << "\n";
}

Exponenta::Exponenta(double a, double b) : a(a), b(b) {}

double Exponenta::f(double x) const {
    return a * exp(b * x);
}

void Exponenta::print(double x) const {
    std::cout << "Exponenta f(" << x << ") = " << f(x) << "\n";
}

Polinom::Polinom(const std::vector<double>& coeffs) : coeffs(coeffs) {}

double Polinom::f(double x) const {
    double result = 0.0;
    for (int i = (int)coeffs.size() - 1; i >= 0; --i)
        result = result * x + coeffs[i];
    return result;
}

void Polinom::print(double x) const {
    std::cout << "Polinom f(" << x << ") = " << f(x) << "\n";
}
