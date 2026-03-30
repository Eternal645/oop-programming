#pragma once
#include <iostream>

using namespace std;

class DateTime
{
private:
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;

    bool leapYear(int y) const;
    int monthDays(int m, int y) const;
    long long totalDays() const;

public:
    DateTime();
    DateTime(int d, int m, int y, int hh = 0, int mm = 0, int ss = 0);

    bool checkDate(int d, int m, int y) const;
    void inputDate();

    void showFormat1() const;
    void showFormat2() const;
    void showFormat3() const;
    void showISO() const;

    long long daysBetween(const DateTime &other) const;
    const char *weekDay() const;

    static DateTime catholikEaster(int y);
    static DateTime orthodoxEaster(int y);
};