#include <iostream>
#include "LineList.h"

using namespace std;

int main(void)
{
    setlocale(LC_ALL, "Russian");

    // Проверка шаблона функции поиска максимума
    int a = 2, b = 3;
    cout << "Max(a,b)=" << getMax(a, b) << endl;

    double x = 1.6e+3, y = 1.58e+3;
    cout << "Max(x,y)=" << getMax(x, y) << endl;

    // Использование шаблона класса списка
    // Указываем, список какого типа
    LineList<int> list;
    cout << "Начало: " << list << endl;

    list.insertFirst(10);
    LineListElem<int>* ptr = list.getStart();
    list.insertAfter(ptr, 15);
    list.insertAfter(ptr->getNext(), 12);
    list.insertFirst(7);
    cout << "Шаг 1: " << list << endl;

    // Задача: перебрать все элементы и найти сумму
    int sum = 0;
    // Используем переменную-итератор
    for (LineListElem<int>* it = list.getStart(); it; it = it->getNext())
        sum += it->getData();
    cout << "Сумма = " << sum << endl;

    return 0;
}
