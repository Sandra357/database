#pragma once

#include <tuple>
#include <iostream>

using namespace std;

class Date {
public:
    Date(const string& y, const string& m, const string& d);

    string GetYear() const;
    string GetMonth() const;
    string GetDay() const;

    const string year;
    const string month;
    const string day;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);
bool operator==(const Date& date1, const Date& date2);
bool operator<(const Date& date1, const Date& date2);
bool operator<=(const Date& date1, const Date& date2);
bool operator>(const Date& date1, const Date& date2);
bool operator>=(const Date& date1, const Date& date2);
bool operator!=(const Date& date1, const Date& date2);
