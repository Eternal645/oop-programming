#include "datetime.h"

using namespace std;

bool DateTime::leapYear(int y) const
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateTime::monthDays(int m, int y) const
{
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && leapYear(y))
        return 29;
    return days[m];
}

long long DateTime::totalDays() const
{
    int y = year;
    if (month <= 2)
        y--;
    long long total = year * 365LL + day;
    for (int i = 1; i < month; i++)
        total += monthDays(i, year);
    total += (y / 4 - y / 100 + y / 400);
    return total;
}

DateTime::DateTime()
{
    day = 1;
    month = 1;
    year = 2000;
    hour = 0;
    minute = 0;
    second = 0;
}

DateTime::DateTime(int d, int m, int y, int hh, int mm, int ss)
{
    if (checkDate(d, m, y))
    {
        day = d;
        month = m;
        year = y;
        hour = hh;
        minute = mm;
        second = ss;
    }
    else
    {
        cout << "Некорректная дата! Установлено 01.01.2000\n";
        day = 1;
        month = 1;
        year = 2000;
        hour = 0;
        minute = 0;
        second = 0;
    }
}

bool DateTime::checkDate(int d, int m, int y) const
{
    if (y < 1 || m < 1 || m > 12 || d < 1)
        return false;
    return d <= monthDays(m, y);
}

void DateTime::inputDate()
{
    int d, m, y, hh, mm, ss;
    cout << "Введите дату (день месяц год): ";
    cin >> d >> m >> y;
    cout << "Введите время (час минута секунда): ";
    cin >> hh >> mm >> ss;
    if (checkDate(d, m, y))
    {
        day = d;
        month = m;
        year = y;
        hour = hh;
        minute = mm;
        second = ss;
        cout << "Дата успешно обновлена.\n";
    }
    else
    {
        cout << "Ошибка: некорректная дата!\n";
    }
}

void DateTime::showFormat1() const
{
    cout << day << ".";
    if (month < 10)
        cout << "0";
    cout << month << "." << year << "\n";
}

void DateTime::showFormat2() const
{
    const char *months[] = {"", "января", "февраля", "марта", "апреля", "мая", "июня",
                            "июля", "августа", "сентября", "октября", "ноября", "декабря"};
    cout << day << " " << months[month] << " " << year << "\n";
}

void DateTime::showFormat3() const
{
    if (day < 10)
        cout << "0";
    cout << day << ".";
    if (month < 10)
        cout << "0";
    cout << month << ".";
    int y = year % 100;
    if (y < 10)
        cout << "0";
    cout << y << "\n";
}

void DateTime::showISO() const
{
    if (year < 1000)
        cout << "0";
    if (year < 100)
        cout << "0";
    if (year < 10)
        cout << "0";
    cout << year << "-";
    if (month < 10)
        cout << "0";
    cout << month << "-";
    if (day < 10)
        cout << "0";
    cout << day << "T";
    if (hour < 10)
        cout << "0";
    cout << hour << ":";
    if (minute < 10)
        cout << "0";
    cout << minute << ":";
    if (second < 10)
        cout << "0";
    cout << second << "\n";
}

long long DateTime::daysBetween(const DateTime &other) const
{
    long long diff = totalDays() - other.totalDays();
    return diff < 0 ? -diff : diff;
}

const char *DateTime::weekDay() const
{
    int d = day, m = month, y = year;
    if (m < 3)
    {
        m += 12;
        y--;
    }
    int k = y % 100, j = y / 100;
    int w = (d + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    if (w < 0)
        w += 7;
    const char *days[] = {"Суббота", "Воскресенье", "Понедельник", "Вторник",
                          "Среда", "Четверг", "Пятница"};
    return days[w];
}

DateTime DateTime::catholikEaster(int y)
{
    int a = y % 19, b = y / 100, c = y % 100;
    int d = b / 4, e = b % 4, f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4, k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int mn = (a + 11 * h + 22 * l) / 451;
    int mo = (h + l - 7 * mn + 114) / 31;
    int da = (h + l - 7 * mn + 114) % 31 + 1;
    return DateTime(da, mo, y);
}

DateTime DateTime::orthodoxEaster(int y)
{
    int a = y % 4, b = y % 7, c = y % 19;
    int d = (19 * c + 15) % 30;
    int e = (2 * a + 4 * b - d + 34) % 7;
    int mo = (d + e + 114) / 31;
    int da = (d + e + 114) % 31 + 1;
    da += 13;
    if (da > 30 && mo == 4)
    {
        da -= 30;
        mo = 5;
    }
    if (da > 31 && mo == 5)
    {
        da -= 31;
        mo = 6;
    }
    return DateTime(da, mo, y);
}