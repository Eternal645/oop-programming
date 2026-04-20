#ifndef ARRAY_H
#define ARRAY_H

// хранит массив целых чисел
class Array {
private:
    int* data;
    int size;

public:
    // создаёт массив из n элементов
    Array(int n);

    // освобождает память
    ~Array();

    // текущий размер массива
    int getSize() const;

    // возвращает элемент по индексу
    int get(int index) const;

    // удаляет элемент по индексц
    void removeAt(int index);
};

#endif
