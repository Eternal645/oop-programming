#include <iostream>
#include <ctime>
#include "Array.h"

using namespace std;

int main() {
    int N, k;

    cout << "Введите N (количество элементов): ";
    cin >> N;
    cout << "Введите k (шаг выбывания): ";
    cin >> k;

    // засекаем время начала
    clock_t start = clock();

    // создаём контейнер с числами от 1 до N
    Array arr(N);

    // текущая позиция счёта
    int current = 0;

    // Удаляем элементы, пока не останется один
    while (arr.getSize() > 1) {
        current = (current + k - 1) % arr.getSize();

        // удаляем элемент
        arr.removeAt(current);
    }

    // засекаем время конца
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "Ответ: " << arr.get(0) << endl;
    cout << "Время расчета: " << elapsed << " сек" << endl;

    return 0;
}
