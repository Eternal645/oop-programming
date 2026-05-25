#include "Field.h"
#include <iostream>
using namespace std;

static const int DIR_NUMBER = 4;
static const int di[] = { 1,  0,  1, 1 };
static const int dj[] = { 0,  1, -1, 1 };
static const int WIN_LENGTH = 4;

// Конструктор
Field::Field(bool isRedFirst)
{
    clear(isRedFirst);
}

// Очистка поля
void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst;
    winner    = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

// Выполнить ход в колонку column
bool Field::makeTurn(int column)
{
    // Игра уже завершена или номер колонки вне диапазона
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;

    int i = column - 1;

    // Ищем первую свободную ячейку снизу (j=0 - дно)
    for (int j = 0; j < FIELD_HEIGHT; j++)
    {
        if (cells[i][j] == EMPTY)
        {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner();           // появился ли победитель
            isRedTurn = !isRedTurn;
            return true;
        }
    }
    // Колонка заполнена
    return false;
}

// Проверить победителя после последнего хода
void Field::checkWinner()
{
    for (int i = 0; i < FIELD_WIDTH; i++)
    {
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            Cell start = cells[i][j];
            if (start == EMPTY) continue;

            for (int dir = 0; dir < DIR_NUMBER; dir++)
            {
                int length = 1;
                int iline  = i;
                int jline  = j;

                while (length < WIN_LENGTH)
                {
                    iline += di[dir];
                    jline += dj[dir];
                    if (iline < 0 || iline >= FIELD_WIDTH  ||
                        jline < 0 || jline >= FIELD_HEIGHT)
                        break;
                    if (cells[iline][jline] != start)
                        break;
                    length++;
                }

                if (length == WIN_LENGTH)
                {
                    winner = start;
                    return;
                }
            }
        }
    }
}

// Закончилась ли игра?
bool Field::isOver() const
{
    if (winner != EMPTY)
        return true;

    // Если хотя бы одна ячейка свободна - игра продолжается
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            if (cells[i][j] == EMPTY)
                return false;

    return true; // все ячейки заняты, ничья
}

bool Field::isWon(bool red) const
{
    return winner == (red ? RED : YELLOW);
}

Cell Field::getCell(int i, int j) const
{
    return cells[i][j];
}

bool Field::isRedTurnNow() const
{
    return isRedTurn;
}

// Печать поля
void Field::print() const
{
    cout << endl;
    // Номера колонок
    cout << " ";
    for (int i = 1; i <= FIELD_WIDTH; i++)
        cout << " " << i;
    cout << endl;

    // Строки поля
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--)
    {
        cout << "|";
        for (int i = 0; i < FIELD_WIDTH; i++)
        {
            switch (cells[i][j])
            {
                case EMPTY:  cout << " ."; break;
                case RED:    cout << " R"; break;
                case YELLOW: cout << " Y"; break;
            }
        }
        cout << " |" << endl;
    }

    // Нижняя граница
    cout << " ";
    for (int i = 0; i < FIELD_WIDTH; i++)
        cout << "--";
    cout << "-" << endl;
}

// Печать результата
void Field::printResult() const
{
    print();
    if (winner == RED)
        cout << "Победил КРАСНЫЙ игрок!" << endl;
    else if (winner == YELLOW)
        cout << "Победил ЖЕЛТЫЙ игрок!" << endl;
    else
        cout << "Ничья!" << endl;
}
