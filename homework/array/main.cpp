#include <iostream>
#include "array.h"
using namespace std;

int main(void)
{
    Array arr(4);

    // Вставляем 4 элемента в конец: 1, 2, 3, 4
    for (int i = 0; i < 4; i++)
        arr.insert(i + 1);
    cout << arr << endl;

    // Вставляем элементы по чётным индексам: 10, 12, 14, 16
    for (int i = 0; i < 8; i += 2)
        arr.insert(10 + i, i);
    cout << arr << endl;

    // Записываем по нечётным индексам: 21, 23, 25, 27
    for (int i = 1; i < 8; i += 2)
        arr[i] = 20 + i;
    cout << arr << endl;

    // Удаляем элементы: 6, 3, 0
    for (int i = 6; i >= 0; i -= 3)
        arr.remove(i);
    cout << arr << endl;

    return 0;
}
