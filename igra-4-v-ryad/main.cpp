#include <iostream>
#include "Field.h"

using namespace std;

int main()
{
    // Для корректного вывода кириллицы на Windows раскомментируйте:
    // setlocale(LC_ALL, "Russian");

    Field field(true); // красный ходит первым

    while (!field.isOver())
    {
        field.print();

        cout << "Ходит "
             << (field.isRedTurnNow() ? "КРАСНЫЙ (R)" : "ЖЕЛТЫЙ (Y)")
             << " игрок. Введите номер колонки (1-7): ";

        int column;
        if (!(cin >> column))
        {
            cout << "Некорректный ввод. Попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (!field.makeTurn(column))
            cout << "Недопустимый ход! Колонка заполнена или номер вне диапазона." << endl;
    }

    field.printResult();
    return 0;
}
