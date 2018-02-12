#include "database.h"

#include <algorithm>

bool operator<(const Date&a, const Date& b) {
    return tie(a.year, a.month, a.day) < tie(b.year, b.month, b.day);
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
    cout << "start RemoveIf\n";
    for (auto i = database.begin(); i != database.end(); i++) {
        cout << "Try date: " << i->first << endl;
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            cout << "Try event: " << *j << endl;
            //auto new_end = remove_if(i.begin(), i.end(), p(i.first, j));
            if (p(i->first, *j)) {
                cout << "Find: " << i->first << " " << *j << endl;
                database.erase(i->first);
                //if (new_end != i.first.end()) {
                deleted_data_num++;
                //i.first.end() = new_end;
            }
        }
        cout << "Try next" << endl;
    }

    cout << "end of RemoveIf\n";

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