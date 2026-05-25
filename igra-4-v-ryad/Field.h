#pragma once
#include <iostream>

// Размеры игрового поля
const int FIELD_WIDTH  = 7;
const int FIELD_HEIGHT = 6;

// Содержимое ячейки
enum Cell
{
    EMPTY  = 0,
    RED    = 1,
    YELLOW = 2
};

class Field
{
public:
    // Конструктор isRedFirst - начинает ли красный
    Field(bool isRedFirst);

    // перезапуск игры
    void clear(bool isRedFirst);

    // Сделать ход в колонку column
    // Возвращает true, если ход допустим
    bool makeTurn(int column);

    // Проверка(закончилась ли игра)
    bool isOver() const;

    // Выиграл ли красный/желтый
    bool isWon(bool red) const;

    // Получить содержимое ячейки [i][j]
    Cell getCell(int i, int j) const;

    // Чья сейчас очередь
    bool isRedTurnNow() const;

    // Напечатать поле в консоль
    void print() const;

    // Напечатать результат игры
    void printResult() const;

private:
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    bool isRedTurn;                        
    Cell winner;                           

    // Проверить, появился ли победитель после последнего хода
    void checkWinner();
};
