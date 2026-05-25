#pragma once
#include <iostream>
#include <cmath>

// Точка 
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Абстрактный базовый класс
class Shape {
public:
    virtual ~Shape() {}
    virtual double calc_area()     = 0;
    virtual double calc_perimetr() = 0;
    virtual void   name()          = 0;
};

// Круг
class Circle : public Shape {
    Point  center;
    double r;
public:
    Circle(Point center, double r);
    Circle(double cx, double cy, double r);
    Circle(int    cx, int    cy, int    r);
    Circle(float  cx, float  cy, float  r);
    double calc_area()     override;
    double calc_perimetr() override;
    void   name()          override;
};

// Эллипс
class Ellipse : public Shape {
    Point  center;
    double a, b;
public:
    Ellipse(Point center, double a, double b);
    Ellipse(double cx, double cy, double a, double b);
    Ellipse(int    cx, int    cy, int    a, int    b);
    Ellipse(float  cx, float  cy, float  a, float  b);
    double calc_area()     override;
    double calc_perimetr() override;
    void   name()          override;
};

// Треугольник
class Triangle : public Shape {
    Point p[3];
public:
    Triangle(Point p1, Point p2, Point p3);
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
    Triangle(int    x1, int    y1, int    x2, int    y2, int    x3, int    y3);
    Triangle(double a, double b, double c);   // по сторонам
    double calc_area()     override;
    double calc_perimetr() override;
    void   name()          override;
};

// Прямоугольник
class Rectangle : public Shape {
    Point p[4];
public:
    Rectangle(Point p1, Point p2, Point p3, Point p4);
    Rectangle(double x1, double y1, double x2, double y2,
              double x3, double y3, double x4, double y4);
    Rectangle(double w, double h);
    Rectangle(int    w, int    h);
    Rectangle(float  w, float  h);
    double calc_area()     override;
    double calc_perimetr() override;
    void   name()          override;
};

// Многоугольник
static const int POLY_MAX = 2048;

class Polygon : public Shape {
public:
    Point pts[POLY_MAX];
    int   nv;

    Polygon();
    Polygon(const Point* pts, int n);
    explicit Polygon(const char* filename);
    double calc_area()     override;
    double calc_perimetr() override;
    void   name()          override;
};

static const int GRID_ROWS = 205;
static const int GRID_COLS = 205;
static const int MAX_PIX   = GRID_ROWS * GRID_COLS;
static const int MAX_COMP  = 600;

struct Component {
    int row[MAX_PIX];
    int col[MAX_PIX];
    int n;
    Component() : n(0) {}
    void add(int r, int c) {
        if (n < MAX_PIX) { row[n] = r; col[n] = c; ++n; }
    }
};

int  findComponents(const char grid[][GRID_COLS], int rows,
                    Component comps[], int maxComp);

char   classifyComponent(const Component& comp);
double estimateArea(const Component& comp, char type);
