#include "date.h"

#include <sstream>
#include <vector>

Date::Date(const string& y, const string& m, const string& d) : year(y), month(m), day(d) {};

string Date::GetYear() const {
    return year;
}

string Date::GetMonth() const {
    return month;
}

string Date::GetDay() const {
    return day;
}

Date ParseDate(istream& is) {
    string date;
    is >> date;

    istringstream iss(date);
    vector<string> date_parts;
    string tmp;
    char delimiter = '-';
    istringstream date_part_stream(date);
    while (getline(date_part_stream, tmp, delimiter)) {
        date_parts.push_back(tmp);
    }

    Date d(date_parts[0], date_parts[1], date_parts[2]);
    return d;
}

ostream& operator<<(ostream& os, const Date& date) {
    int zero_num = 4 - date.GetYear().size();
    if (zero_num) {
        string tmp;
        tmp.insert(0, zero_num, '0');
        os << tmp;
    }
    os << date.GetYear() << "-";

    if (date.GetMonth().size() < 2) {
        os << "0";
    }
    os << date.GetMonth() << "-";

    if (date.GetDay().size() < 2) {
        os << "0";
    }
    os << date.GetDay();

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

/*
bool operator==(const Date& date1, const Date& date2) {
    if ((date1.GetYear() == date2.GetYear()) &&
        (date1.GetMonth() == date2.GetMonth()) &&
        (date1.GetDay() == date2.GetDay())) {
        return true;
    }
    return false;
}

bool operator<(const Date& date1, const Date& date2) {
    if (date1.GetYear() >= date2.GetYear()) {
        return false;
    } else if (date1.GetMonth() >= date2.GetMonth()) {
        return false;
    } else if (date1.GetDay() >= date2.GetDay()) {
        return false;
    }

    return true;
}

bool operator<=(const Date& date1, const Date& date2) {
    if (date1.GetYear() > date2.GetYear()) {
        return false;
    } else if (date1.GetMonth() > date2.GetMonth()) {
        return false;
    } else if (date1.GetDay() > date2.GetDay()) {
        return false;
    }

    return true;
}

bool operator>(const Date& date1, const Date& date2) {
    if (date1.GetYear() <= date2.GetYear()) {
        return false;
    } else if (date1.GetMonth() <= date2.GetMonth()) {
        return false;
    } else if (date1.GetDay() <= date2.GetDay()) {
        return false;
    }

    return true;
}

bool operator>=(const Date& date1, const Date& date2) {
    if (date1.GetYear() < date2.GetYear()) {
        return false;
    } else if (date1.GetMonth() < date2.GetMonth()) {
        return false;
    } else if (date1.GetDay() < date2.GetDay()) {
        return false;
    }

    return true;
}

bool operator!=(const Date& date1, const Date& date2) {
    if (date1.GetYear() == date2.GetYear()) {
        return false;
    } else if (date1.GetMonth() == date2.GetMonth()) {
        return false;
    } else if (date1.GetDay() == date2.GetDay()) {
        return false;
    }

    return true;
}
*/