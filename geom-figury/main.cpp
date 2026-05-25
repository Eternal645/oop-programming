#include <iostream>
#include <cmath>
#include "GeomFigury.h"

using namespace std;

static int readGrid(const char* filename, char grid[][GRID_COLS]) {
    FILE* f = fopen(filename, "r");
    if (!f) { cerr << "Не удалось открыть: " << filename << "\n"; return 0; }
    int rows = 0;
    while (rows < GRID_ROWS) {
        for (int j = 0; j < GRID_COLS; ++j) grid[rows][j] = ' ';
        if (!fgets(grid[rows], GRID_COLS, f)) break;
        for (int j = 0; j < GRID_COLS; ++j) {
            char ch = grid[rows][j];
            if (ch == '\n' || ch == '\r' || ch == '\0') {
                for (int k = j; k < GRID_COLS; ++k) grid[rows][k] = ' ';
                break;
            }
        }
        ++rows;
    }
    fclose(f);
    return rows;
}

int main(int argc, char* argv[]) {
    const char* inputFile    = (argc >= 2) ? argv[1] : "input.dat";
    const char* outputFile   = (argc >= 3) ? argv[2] : "output.dat";
    const char* granitsyFile = (argc >= 4) ? argv[3] : "granitsy-uchastka2.txt";

    // Демонстрация иерархии классов
    cout << "=== Тест классов ===\n";


    static const int LIST_MAX = 16;
    Shape* list[LIST_MAX];
    int    listN = 0;

    list[listN++] = new Circle(Point(0, 0), 5);
    list[listN++] = new Circle(3, 4, 7);
    list[listN++] = new Ellipse(Point(0, 0), 6, 3);
    list[listN++] = new Triangle(Point(0,0), Point(4,0), Point(0,3));
    list[listN++] = new Triangle(3.0, 4.0, 5.0);   // по сторонам
    list[listN++] = new Rectangle(10.0, 4.0);       // по сторонам
    list[listN++] = new Rectangle(Point(0,0), Point(6,0), Point(6,3), Point(0,3));

    for (int i = 0; i < listN; ++i) {
        list[i]->name();
        cout << "  Площадь:  " << list[i]->calc_area()     << "\n";
        cout << "  Периметр: " << list[i]->calc_perimetr()  << "\n\n";
        delete list[i];
    }

    // Многоугольник из файла
    cout << "=== Площадь участка (" << granitsyFile << ") ===\n";
    Polygon poly(granitsyFile);
    if (poly.nv >= 3) {
        poly.name();
        cout << "  Вершин:   " << poly.nv               << "\n";
        cout << "  Площадь:  " << poly.calc_area()       << " кв.ед.\n";
        cout << "  Периметр: " << poly.calc_perimetr()   << " ед.\n\n";
    } else {
        cout << "  Файл не найден или содержит менее 3 вершин.\n\n";
    }

    // Обработка ASCII-сетки
    cout << "=== Обработка файла: " << inputFile << " ===\n";
    static char grid[GRID_ROWS][GRID_COLS];
    int rows = readGrid(inputFile, grid);
    if (rows == 0) return 1;

    static Component comps[MAX_COMP];
    int nComp = findComponents(grid, rows, comps, MAX_COMP);

    int    cntRect = 0, cntCircle = 0, cntTri = 0, cntNoise = 0;
    double areaRect = 0, areaCircle = 0, areaTri = 0;

    for (int i = 0; i < nComp; ++i) {
        char t = classifyComponent(comps[i]);
        if      (t == 'R') { ++cntRect;   areaRect   += estimateArea(comps[i],'R'); }
        else if (t == 'C') { ++cntCircle; areaCircle += estimateArea(comps[i],'C'); }
        else if (t == 'T') { ++cntTri;    areaTri    += estimateArea(comps[i],'T'); }
        else if (t == 'N') { ++cntNoise; }
    }

    // Запись в выходной файл
    FILE* fout = fopen(outputFile, "w");
    if (!fout) { cerr << "Не удалось открыть для записи: " << outputFile << "\n"; return 1; }
    fprintf(fout, "Rectangle = %d\n", cntRect);
    fprintf(fout, "Circle = %d\n",    cntCircle);
    fprintf(fout, "Triangle = %d\n",  cntTri);
    fprintf(fout, "Noise = %d\n",     cntNoise);
    fclose(fout);

    cout << "Rectangle = " << cntRect   << "\n";
    cout << "Circle = "    << cntCircle << "\n";
    cout << "Triangle = "  << cntTri    << "\n";
    cout << "Noise = "     << cntNoise  << "\n\n";

    double total = areaRect + areaCircle + areaTri;
    cout << "Суммарная площадь (Rectangle + Circle + Triangle) = " << total << " кв.ед.\n";
    cout << "  Rectangle : " << areaRect   << "\n";
    cout << "  Circle    : " << areaCircle << "\n";
    cout << "  Triangle  : " << areaTri    << "\n";

    return 0;
}
