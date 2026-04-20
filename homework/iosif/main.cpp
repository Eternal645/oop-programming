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

    // Засекаем время начала
    clock_t start = clock();

    // Создаём контейнер с числами от 1 до N
    Array arr(N);

    // Текущая позиция счёта (начинаем с 0-го индекса)
    int current = 0;

    // Удаляем элементы, пока не останется один
    while (arr.getSize() > 1) {
        // Переходим на k-й элемент (отсчёт с текущей позиции)
        // k-1, потому что мы уже стоим на одном элементе (он считается первым)
        current = (current + k - 1) % arr.getSize();

        // Удаляем этот элемент
        arr.removeAt(current);

        // После удаления current указывает на следующий элемент — это корректно,
        // потому что removeAt сдвинул всё влево
    }

    // Засекаем время конца
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "Ответ: " << arr.get(0) << endl;
    cout << "Время расчета: " << elapsed << " сек" << endl;

    return 0;
}
