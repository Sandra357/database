#include "database.h"

#include <algorithm>

ostream& operator<<(ostream& os, const pair<Date, string> p){
    os << p.first << " " << p.second;
    return os;
}

void Database::Add(const Date& date, const string& event) {
    auto it_map = database.find(date);
    if (it_map == database.end()) {
        set<string> ev_set;
        vector<string> ev_vector;
        ev_set.insert(event);
        ev_vector.push_back(event);
        Containers c;
        c.set_data = ev_set;
        c.vector_data = ev_vector;
        database.insert({date, c});
        return;
    }

    auto it_set = it_map->second.set_data.find(event);
    if (it_set == it_map->second.set_data.end()) {
        it_map->second.set_data.insert(event);
        it_map->second.vector_data.push_back(event);
    }
}

int Database::RemoveIf(function<bool(const Date&, const string&)>p) {
    int deleted_data_num = 0;

    for (auto i = database.begin(); i != database.end();) {
        auto it_vector = stable_partition(i->second.vector_data.begin(), i->second.vector_data.end(),
                                   [&](string e) {
                                        return !p(i->first, e);
                                   });
        if (it_vector == i->second.vector_data.begin()) {
            deleted_data_num += i->second.vector_data.size();
            i = database.erase(i);
        } else if (it_vector != i->second.vector_data.end()) {
            int erased_num = i->second.vector_data.end() - it_vector;
            deleted_data_num += erased_num;
            for (auto it_erased = it_vector; it_erased != i->second.vector_data.end(); it_erased++) {
                i->second.set_data.erase(*it_erased);
            }
            i->second.vector_data.erase(it_vector, i->second.vector_data.end());
            i++;
        } else {
            i++;
        }
    }

    return deleted_data_num;
}

VectorFindDatabse Database::FindIf(function<bool(const Date&, const string&)>p) {
    VectorFindDatabse find_database;

    for (auto i = database.begin(); i != database.end(); i++) {
        vector<string> tmp;
        copy_if(i->second.vector_data.begin(), i->second.vector_data.end(), back_inserter(tmp),
                                   [&](string e) {
                                        return p(i->first, e);
                                   });
        if (tmp.size() != 0) {
            for (auto it = tmp.begin(); it != tmp.end(); it++) {
                find_database.push_back({i->first, *it});
            }
        }
    }

    return find_database;
}

pair<Date, string> Database::Last(const Date& d) {
    auto last = upper_bound(database.begin(), database.end(), d,
                            [](Date dd, pair<Date, Containers> p) {
                                return p.first > dd;
                            });

    if (last == database.begin()) {
        throw invalid_argument("No entries");
    }

    last--;
    pair<Date, string> last_pair = {last->first, last->second.vector_data.back()};

    return last_pair;
}

ostream& Database::Print(ostream& os) {
    for (auto i : database) {
        for (auto j : i.second.vector_data) {
            os << i.first << " " << j << endl;
        }
    }
    return os;
}