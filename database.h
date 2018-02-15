#pragma once

#include "date.h"

#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef map<Date, deque<string>> MapDatabase;
typedef deque<pair<Date, string>> VectorFindDatabse;

ostream& operator<<(ostream& os, const pair<Date, string> p);

class Database {
public:
    void Add(Date date, string event);
    int RemoveIf(function<bool(const Date&, const string&)>p);
    VectorFindDatabse FindIf(function<bool(const Date&, const string&)>p);
    pair<Date, string> Last(Date d);
    ostream& Print(ostream& os);

    MapDatabase database;
};