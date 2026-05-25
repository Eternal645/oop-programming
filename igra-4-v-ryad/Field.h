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
    // Конструктор: isRedFirst — начинает ли красный
    Field(bool isRedFirst);

    // Очистка / перезапуск игры
    void clear(bool isRedFirst);

    // Сделать ход в колонку column (1..FIELD_WIDTH).
    // Возвращает true, если ход допустим.
    bool makeTurn(int column);

    // Закончилась ли игра (победа или ничья)?
    bool isOver() const;

    // Выиграл ли красный / желтый?
    bool isWon(bool red) const;

    // Получить содержимое ячейки [i][j]
    Cell getCell(int i, int j) const;

    // Чья сейчас очередь?
    bool isRedTurnNow() const;

    // Напечатать поле в консоль
    void print() const;

    // Напечатать результат игры
    void printResult() const;

private:
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT]; // [col][row], row=0 — дно
    bool isRedTurn;                        // true — ходит красный
    Cell winner;                           // EMPTY пока никто не выиграл

    // Проверить, появился ли победитель после последнего хода
    void checkWinner();
};
