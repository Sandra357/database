#pragma once

#include "date.h"

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

struct Containers {
	vector<string> vector_data;
	set<string> set_data;
};

typedef map<Date, Containers> MapDatabase;
typedef vector<pair<Date, string>> VectorFindDatabse;

ostream& operator<<(ostream& os, const pair<Date, string> p);

class Database {
public:
    void Add(const Date& date, const string& event);
    int RemoveIf(function<bool(const Date&, const string&)>p);
    VectorFindDatabse FindIf(function<bool(const Date&, const string&)>p);
    pair<Date, string> Last(Date d);
    ostream& Print(ostream& os);

    MapDatabase database;
};