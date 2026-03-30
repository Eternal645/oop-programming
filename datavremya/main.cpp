#include <iostream>
#include "datetime.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, ".UTF8");

    cout << "=== Форматы вывода ===\n";
    DateTime date1(17, 3, 2025, 9, 15, 0);
    date1.showFormat1();
    date1.showFormat2();
    date1.showFormat3();
    date1.showISO();
    cout << "День недели: " << date1.weekDay() << "\n";

    cout << "\n=== Разница дат ===\n";
    DateTime date2(4, 11, 2025);
    cout << "Разница: " << date1.daysBetween(date2) << " дн.\n";

    cout << "\n=== Проверка корректности ===\n";
    DateTime d1(28, 2, 2025);
    cout << "28.02.2025: ";
    d1.showFormat1();
    DateTime d2(29, 2, 2025);

    cout << "\n=== Дата Пасхи ===\n";
    int years[] = {2022, 2023, 2024, 2025};
    for (int i = 0; i < 4; i++)
    {
        cout << years[i] << " | Католическая: ";
        DateTime::catholikEaster(years[i]).showFormat2();
        cout << "       Православная: ";
        DateTime::orthodoxEaster(years[i]).showFormat2();
    }

    cout << "\n=== Ввод с клавиатуры ===\n";
    DateTime date3;
    date3.inputDate();
    cout << "Вы ввели: ";
    date3.showFormat2();
    cout << "ISO: ";
    date3.showISO();
    cout << "День недели: " << date3.weekDay() << "\n";

    return 0;
}