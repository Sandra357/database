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

    for (auto i = database.begin(); i != database.end();) {
        auto it = remove_if(i->second.begin(), i->second.end(),
                            [&](string s) {
                                return p(i->first, s);
                            });
        if (it != i->second.end()) {
            int remove_num = i->second.end() - it;
            i->second.erase(it, i->second.end());
            if (i->second.size() == 0) {
                i = database.erase(i);
            } else {
                i++;
            }
            deleted_data_num += remove_num;
        } else {
            i++;
        }
    }

    return deleted_data_num;
}

VectorFindDatabse Database::FindIf(function<bool(const Date&, const string&)>p) {
    VectorFindDatabse find_database;

    for (auto i = database.begin(); i != database.end(); i++) {
        auto it = partition(i->second.begin(), i->second.end(),
                            [&](string s) {
                                return p(i->first, s);
                            });
        for (auto j = i->second.begin(); j != it; j++) {
            find_database.push_back({i->first, *j});
        }
    }

    return find_database;
}

pair<Date, string> Database::Last(Date d) {
    auto last = upper_bound(database.begin(), database.end(), d,
                            [](Date dd, pair<Date, deque<string>> p) {
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