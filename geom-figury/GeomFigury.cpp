#include "GeomFigury.h"
#include <iostream>
#include <cmath>

using namespace std;

static const double PI = acos(-1.0);

static double ptDist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

// формула гаусса для массива вершин
static double shoelace(const Point* v, int n) {
    double s = 0;
    for (int i = 0; i < n; ++i) {
        const Point& a = v[i];
        const Point& b = v[(i + 1) % n];
        s += a.x * b.y - b.x * a.y;
    }
    return fabs(s) / 2.0;
}

Circle::Circle(Point center, double r) : center(center), r(r) {}
Circle::Circle(double cx, double cy, double r) : center(cx, cy), r(r) {}
Circle::Circle(int    cx, int    cy, int    r) : center((double)cx, (double)cy), r((double)r) {}
Circle::Circle(float  cx, float  cy, float  r) : center((double)cx, (double)cy), r((double)r) {}

double Circle::calc_area()     { return PI * r * r; }
double Circle::calc_perimetr() { return 2.0 * PI * r; }
void   Circle::name()          { cout << "Circle\n"; }

Ellipse::Ellipse(Point center, double a, double b) : center(center), a(a), b(b) {}
Ellipse::Ellipse(double cx, double cy, double a, double b) : center(cx, cy), a(a), b(b) {}
Ellipse::Ellipse(int    cx, int    cy, int    a, int    b) : center((double)cx,(double)cy), a((double)a), b((double)b) {}
Ellipse::Ellipse(float  cx, float  cy, float  a, float  b) : center((double)cx,(double)cy), a((double)a), b((double)b) {}

double Ellipse::calc_area()     { return PI * a * b; }
double Ellipse::calc_perimetr() {
    double h = (a - b) * (a - b) / ((a + b) * (a + b));
    return PI * (a + b) * (1.0 + 3.0 * h / (10.0 + sqrt(4.0 - 3.0 * h)));
}
void Ellipse::name() { cout << "Ellipse\n"; }

Triangle::Triangle(Point p1, Point p2, Point p3) {
    p[0] = p1; p[1] = p2; p[2] = p3;
}
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    p[0] = Point(x1,y1); p[1] = Point(x2,y2); p[2] = Point(x3,y3);
}
Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    p[0] = Point((double)x1,(double)y1);
    p[1] = Point((double)x2,(double)y2);
    p[2] = Point((double)x3,(double)y3);
}
// по трём сторонам: p1=(0,0), p2=(a,0), p3 - теорема косинусов
Triangle::Triangle(double a, double b, double c) {
    double px = (a*a + b*b - c*c) / (2.0 * a);
    double py2 = b*b - px*px;
    double py = sqrt(py2 > 0 ? py2 : 0);
    p[0] = Point(0, 0);
    p[1] = Point(a, 0);
    p[2] = Point(px, py);
}

double Triangle::calc_area()     { return shoelace(p, 3); }
double Triangle::calc_perimetr() {
    return ptDist(p[0],p[1]) + ptDist(p[1],p[2]) + ptDist(p[2],p[0]);
}
void Triangle::name() { cout << "Triangle\n"; }

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) {
    p[0]=p1; p[1]=p2; p[2]=p3; p[3]=p4;
}
Rectangle::Rectangle(double x1,double y1,double x2,double y2,
                     double x3,double y3,double x4,double y4) {
    p[0]=Point(x1,y1); p[1]=Point(x2,y2);
    p[2]=Point(x3,y3); p[3]=Point(x4,y4);
}
Rectangle::Rectangle(double w, double h) {
    p[0]=Point(0,0); p[1]=Point(w,0); p[2]=Point(w,h); p[3]=Point(0,h);
}
Rectangle::Rectangle(int w, int h) {
    p[0]=Point(0,0); p[1]=Point((double)w,0);
    p[2]=Point((double)w,(double)h); p[3]=Point(0,(double)h);
}
Rectangle::Rectangle(float w, float h) {
    p[0]=Point(0,0); p[1]=Point((double)w,0);
    p[2]=Point((double)w,(double)h); p[3]=Point(0,(double)h);
}

double Rectangle::calc_area()     { return shoelace(p, 4); }
double Rectangle::calc_perimetr() {
    return ptDist(p[0],p[1]) + ptDist(p[1],p[2])
         + ptDist(p[2],p[3]) + ptDist(p[3],p[0]);
}
void Rectangle::name() { cout << "Rectangle\n"; }

Polygon::Polygon() : nv(0) {}

Polygon::Polygon(const Point* points, int n) : nv(0) {
    for (int i = 0; i < n && i < POLY_MAX; ++i)
        pts[nv++] = points[i];
}

Polygon::Polygon(const char* filename) : nv(0) {
    FILE* f = fopen(filename, "r");
    if (!f) return;
    char line[256];
    while (fgets(line, sizeof(line), f) && nv < POLY_MAX) {
        double x, y;
        if (sscanf(line, "%lf %lf", &x, &y) == 2)
            pts[nv++] = Point(x, y);
    }
    fclose(f);
}

double Polygon::calc_area()     { return (nv >= 3) ? shoelace(pts, nv) : 0; }
double Polygon::calc_perimetr() {
    if (nv < 2) return 0;
    double per = 0;
    for (int i = 0; i < nv; ++i)
        per += ptDist(pts[i], pts[(i+1) % nv]);
    return per;
}
void Polygon::name() { cout << "Polygon\n"; }

int findComponents(const char grid[][GRID_COLS], int rows,
                   Component comps[], int maxComp)
{
    static bool visited[GRID_ROWS][GRID_COLS];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < GRID_COLS; ++j)
            visited[i][j] = false;

    static int qr[MAX_PIX], qc[MAX_PIX];

    const int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    const int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};

    auto drawn = [&](int r, int c) -> bool {
        if (r < 0 || r >= rows || c < 0 || c >= GRID_COLS) return false;
        char ch = grid[r][c];
        return ch != ' ' && ch != '\0' && ch != '\r' && ch != '\n';
    };

    int nComp = 0;
    for (int r = 0; r < rows && nComp < maxComp; ++r) {
        for (int c = 0; c < GRID_COLS && nComp < maxComp; ++c) {
            if (!drawn(r, c) || visited[r][c]) continue;
            Component& comp = comps[nComp];
            comp.n = 0;
            int head = 0, tail = 0;
            qr[tail] = r; qc[tail] = c; ++tail;
            visited[r][c] = true;
            while (head < tail) {
                int cr = qr[head], cc = qc[head]; ++head;
                comp.add(cr, cc);
                for (int d = 0; d < 8; ++d) {
                    int nr = cr+dr[d], nc = cc+dc[d];
                    if (drawn(nr,nc) && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        qr[tail] = nr; qc[tail] = nc; ++tail;
                    }
                }
            }
            ++nComp;
        }
    }
    return nComp;
}

static void getBbox(const Component& comp,
                    int& minR, int& maxR, int& minC, int& maxC)
{
    minR = 999999; maxR = -999999;
    minC = 999999; maxC = -999999;
    for (int i = 0; i < comp.n; ++i) {
        if (comp.row[i] < minR) minR = comp.row[i];
        if (comp.row[i] > maxR) maxR = comp.row[i];
        if (comp.col[i] < minC) minC = comp.col[i];
        if (comp.col[i] > maxC) maxC = comp.col[i];
    }
}

char classifyComponent(const Component& comp)
{
    int n = comp.n;
    if (n <= 4) return 0;

    int minR, maxR, minC, maxC;
    getBbox(comp, minR, maxR, minC, maxC);
    int h = maxR - minR + 1;
    int w = maxC - minC + 1;

    if (h <= 2 || w <= 2 || n <= 8) return 0;

    // Прямоугольник 
    {
        int onEdge = 0, topCnt = 0, botCnt = 0, lCnt = 0, rCnt = 0;
        for (int i = 0; i < n; ++i) {
            int lr = comp.row[i] - minR;
            int lc = comp.col[i] - minC;
            bool edge = false;
            if (lr == 0)   { ++topCnt; edge = true; }
            if (lr == h-1) { ++botCnt; edge = true; }
            if (lc == 0)   { ++lCnt;   edge = true; }
            if (lc == w-1) { ++rCnt;   edge = true; }
            if (edge) ++onEdge;
        }
        if ((double)onEdge/n >= 0.7
            && (double)topCnt/w >= 0.5 && (double)botCnt/w >= 0.5
            && (double)lCnt/h  >= 0.5 && (double)rCnt/h  >= 0.5)
            return 'R';
    }

    // Круг 
    {
        int bigger  = h > w ? h : w;
        int smaller = h < w ? h : w;
        if ((double)bigger / smaller <= 1.6) {
            double cx = 0, cy = 0;
            for (int i = 0; i < n; ++i) { cx += comp.col[i]; cy += comp.row[i]; }
            cx /= n; cy /= n;
            double sumD = 0, sumD2 = 0;
            for (int i = 0; i < n; ++i) {
                double dx = comp.col[i] - cx, dy = comp.row[i] - cy;
                double d  = sqrt(dx*dx + dy*dy);
                sumD += d; sumD2 += d*d;
            }
            double mean = sumD / n;
            if (mean > 2.0) {
                double var = sumD2/n - mean*mean;
                double cv  = sqrt(var > 0 ? var : 0) / mean;
                if (cv < 0.3) return 'C';
            }
        }
    }

    // Треугольник 
    {
        int ti = 0, bli = 0, bri = 0;
        for (int i = 0; i < n; ++i) {
            if (comp.row[i] < comp.row[ti]) ti = i;
            if (comp.row[i]*w - comp.col[i] > comp.row[bli]*w - comp.col[bli]) bli = i;
            if (comp.row[i]*w + comp.col[i] > comp.row[bri]*w + comp.col[bri]) bri = i;
        }
        double ax = comp.col[ti],  ay = comp.row[ti];
        double bx = comp.col[bli], by = comp.row[bli];
        double cx = comp.col[bri], cy = comp.row[bri];
        double tArea = fabs((bx-ax)*(cy-ay) - (cx-ax)*(by-ay)) / 2.0;

        if (tArea >= 0.15 * (double)h * (double)w) {
            int near = 0;
            for (int i = 0; i < n; ++i) {
                double px = comp.col[i], py = comp.row[i];
                auto segDist = [](double px,double py,
                                  double x1,double y1,
                                  double x2,double y2) -> double {
                    double dx=x2-x1, dy=y2-y1, len2=dx*dx+dy*dy;
                    if (len2 < 1e-9) return (px-x1)*(px-x1)+(py-y1)*(py-y1);
                    double t=((px-x1)*dx+(py-y1)*dy)/len2;
                    if (t < 0.0) t=0.0;
                    if (t > 1.0) t=1.0;
                    double qx=x1+t*dx, qy=y1+t*dy;
                    return (px-qx)*(px-qx)+(py-qy)*(py-qy);
                };
                double d1=segDist(px,py,ax,ay,bx,by);
                double d2=segDist(px,py,bx,by,cx,cy);
                double d3=segDist(px,py,ax,ay,cx,cy);
                double dmin = d1<d2?d1:d2; dmin=dmin<d3?dmin:d3;
                if (dmin <= 9.0) ++near;
            }
            if ((double)near/n >= 0.65) return 'T';
        }
    }

    return 'N';
}

double estimateArea(const Component& comp, char type)
{
    int minR, maxR, minC, maxC;
    getBbox(comp, minR, maxR, minC, maxC);
    double h = (double)(maxR - minR) - 1.0;
    double w = (double)(maxC - minC) - 1.0;
    if (h < 0) h = 0;
    if (w < 0) w = 0;
    if (type == 'R') return w * h;
    if (type == 'C') { double r = (w+h)/4.0; return PI*r*r; }
    if (type == 'T') return 0.5 * w * h;
    return 0;
}
