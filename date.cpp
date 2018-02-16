#include "date.h"

#include <iostream>
#include <sstream>
#include <vector>

Date::Date(const int& y, const int& m, const int& d) : year(y), month(m), day(d) {};

Date::Date(initializer_list<int> l) {
    vector<int> list;
    for (auto i : l) {
        list.push_back(i);
    }
    year = list[0];
    month = list[1];
    day = list[2];
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

Date ParseDate(istream& is) {
    string date;
    is >> date;

    if (date == "") {
        throw invalid_argument("No entries");
    }

    istringstream iss(date);
    vector<string> date_parts;
    string tmp;
    char delimiter = '-';
    istringstream date_part_stream(date);
    while (getline(date_part_stream, tmp, delimiter)) {
        date_parts.push_back(tmp);
    }
    Date d(stoi(date_parts[0]), stoi(date_parts[1]), stoi(date_parts[2]));

    return d;
}

ostream& operator<<(ostream& os, const Date& date) {
    if (date.year < 1000) {
        os << "0";
    }
    if(date.year < 100) {
        os << "0";
    }
    if(date.year < 10) {
        os << "0";
    }
    os << date.year << "-";

    if (date.month < 10) {
        os << "0";
    }
    os << date.month << "-";

    if (date.day < 10) {
        os << "0";
    }
    os << date.day;

    return os;
}

bool operator==(const Date&a, const Date& b) {
    return tie(a.year, a.month, a.day) == tie(b.year, b.month, b.day);
}

bool operator!=(const Date&a, const Date& b) {
    return tie(a.year, a.month, a.day) != tie(b.year, b.month, b.day);
}

bool operator<(const Date&a, const Date& b) {
    return tie(a.year, a.month, a.day) < tie(b.year, b.month, b.day);
}

bool operator<=(const Date&a, const Date& b) {
    return tie(a.year, a.month, a.day) <= tie(b.year, b.month, b.day);
}

bool operator>(const Date&a, const Date& b) {
    return tie(a.year, a.month, a.day) > tie(b.year, b.month, b.day);
}

bool operator>=(const Date&a, const Date& b) {
    return tie(a.year, a.month, a.day) >=tie(b.year, b.month, b.day);
}
