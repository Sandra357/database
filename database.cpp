#include "database.h"

#include <algorithm>

ostream& operator<<(ostream& os, const pair<Date, string> p){
    os << p.first << " " << p.second;
    return os;
}

void Database::Add(Date date, string event) {
    if(database[date].empty()) {
        database[date].push_back(event);
    } else {
        if (find(database[date].begin(), database[date].end(), event) == database[date].end()) {
            database[date].push_back(event);
        }
    }
}

int Database::RemoveIf(function<bool(const Date&, const string&)>p) {
    int deleted_data_num = 0;

    for (auto i = database.begin(); i != database.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end();) {
            if (p(i->first, *j)) {
                i->second.erase(j);
                deleted_data_num++;
            } else {
                ++j;
            }
        }
    }

    return deleted_data_num;
}

VectorFindDatabse Database::FindIf(function<bool(const Date&, const string&)>p) {
    VectorFindDatabse find_database;

    for (auto i = database.begin(); i != database.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            if (p(i->first, *j)) {
                find_database.push_back({i->first, *j});
            }
        }
    }

    return find_database;
}

pair<Date, string> Database::Last(Date d) {
    auto last = upper_bound(database.begin(), database.end(), d,
                            [](Date dd, pair<Date, vector<string>> p) {
                                return p.first > dd;
                            });

    if (last == database.begin()) {
        throw invalid_argument("No entries");
    }

    last--;
    pair<Date, string> last_pair = {last->first, last->second.back()};

    return last_pair;
}

ostream& Database::Print(ostream& os) {
    for (auto i : database) {
        for (auto j : i.second) {
            os << i.first << " " << j << endl;
        }
    }
    return os;
}