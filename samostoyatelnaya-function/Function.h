#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class Function {
public:
    virtual ~Function() {}
    virtual double f(double x) const = 0;
    virtual void print(double x) const = 0;
    virtual double findMin(double a, double b, double step = 0.001) const;
    virtual double findMax(double a, double b, double step = 0.001) const;
    virtual double integrate(double a, double b, int n = 1000) const;
    virtual double differentiate(double x, double h = 1e-5) const;
};

class Hiperbola : public Function {
    double a;
public:
    Hiperbola(double a);
    double f(double x) const override;
    void print(double x) const override;
};

class Parabola : public Function {
    double a, b, c;
public:
    Parabola(double a, double b, double c);
    double f(double x) const override;
    void print(double x) const override;
};

class Exponenta : public Function {
    double a, b;
public:
    Exponenta(double a, double b);
    double f(double x) const override;
    void print(double x) const override;
};

class Polinom : public Function {
    std::vector<double> coeffs;
public:
    Polinom(const std::vector<double>& coeffs);
    double f(double x) const override;
    void print(double x) const override;
};
