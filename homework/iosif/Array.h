#ifndef ARRAY_H
#define ARRAY_H

// Класс-контейнер Array — хранит массив целых чисел
class Array {
private:
    int* data;   // указатель на массив
    int size;    // текущее количество элементов

public:
    // Конструктор: создаёт массив из n элементов (1, 2, 3, ..., n)
    Array(int n);

    // Деструктор: освобождает память
    ~Array();

    // Возвращает текущий размер массива
    int getSize() const;

    // Возвращает элемент по индексу
    int get(int index) const;

    // Удаляет элемент по индексу (сдвигает остальные влево)
    void removeAt(int index);
};

#endif
