#pragma once

#include <tuple>
#include <iostream>

using namespace std;

class Date {
public:
    Date(const int& y, const int& m, const int& d);
    Date(initializer_list<int> l);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    int year;
    int month;
    int day;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);
bool operator==(const Date& date1, const Date& date2);
bool operator<(const Date& date1, const Date& date2);
bool operator<=(const Date& date1, const Date& date2);
bool operator>(const Date& date1, const Date& date2);
bool operator>=(const Date& date1, const Date& date2);
bool operator!=(const Date& date1, const Date& date2);

