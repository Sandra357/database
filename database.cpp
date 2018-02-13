#include "database.h"

#include <algorithm>

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

ostream& Database::Print(ostream& os) {
    for (auto i : database) {
        for (auto j : i.second) {
            os << i.first << " " << j << endl;
        }
    }
    return os;
}