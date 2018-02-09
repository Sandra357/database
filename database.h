#pragma once;

#include "date.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef map<Date, vector<string>> MapDatabase;

bool operator<(const Date&a, const Date& b);

class Database {
public:
    void Add(Date date, string event);
    int RemoveIf(UnaryPredicate p);

    ostream& Print(ostream& os);

    MapDatabase database;
};