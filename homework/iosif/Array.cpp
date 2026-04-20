#include "Array.h"

// Конструктор: выделяем память и заполняем числами от 1 до n
Array::Array(int n) {
    size = n;
    data = new int[n];
    for (int i = 0; i < n; i++) {
        data[i] = i + 1;  // элементы: 1, 2, 3, ..., n
    }
}

// Деструктор: освобождаем выделенную память
Array::~Array() {
    delete[] data;
}

// Возвращает текущий размер массива
int Array::getSize() const {
    return size;
}

// Возвращает элемент по индексу
int Array::get(int index) const {
    return data[index];
}

// Удаляет элемент по индексу: сдвигаем все элементы после него на одну позицию влево
void Array::removeAt(int index) {
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;  // уменьшаем размер
}
