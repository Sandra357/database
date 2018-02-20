#include "database.h"

#include <algorithm>

ostream& operator<<(ostream& os, const pair<Date, string> p){
    os << p.first << " " << p.second;
    return os;
}

void Database::Add(Date& date, string& event) {
    auto it = database[date].set_data.find(event);
    if (it == database[date].set_data.end()) {
        database[date].vector_data.push_back(event);
        database[date].set_data.insert(event);
    }
}

int Database::RemoveIf(function<bool(const Date&, const string&)>p) {
    int deleted_data_num = 0;
    bool erased = false;

    for (auto i = database.begin(); i != database.end();) {
        auto it_vector = remove_if(i->second.vector_data.begin(), i->second.vector_data.end(),
                                   [&](string e) {
                                        return p(i->first, e);
                                   });
        if (it_vector == i->second.vector_data.begin()) {
            deleted_data_num += i->second.vector_data.size();
            i = database.erase(i);
        } else if (it_vector != i->second.vector_data.end()) {
            int erased_num = i->second.vector_data.end() - it_vector;
            deleted_data_num += erased_num;
            i->second.vector_data.erase(it_vector, i->second.vector_data.end());
            for (auto it_set = i->second.set_data.begin(); it_set != i->second.set_data.end();) {
                if (p(i->first, *it_set)) {
                    it_set = i->second.set_data.erase(it_set);
                } else {
                    it_set++;
                }
            }
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
        /*auto it_vector = find_if(i->second.vector_data.begin(), i->second.vector_data.end(),
                                   [&](string e) {
                                        return p(i->first, e);
                                   });
        for (auto it = i->second.vector_data.begin(); it != it_vector; it++) {
            find_database.push_back({i->first, *it});
        }*/
        for (auto j = i->second.vector_data.begin(); j != i->second.vector_data.end(); j++) {
            if (p(i->first, *j)) {
                find_database.push_back({i->first, *j});
            }
        }
    }

    return find_database;
}

pair<Date, string> Database::Last(Date d) {
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