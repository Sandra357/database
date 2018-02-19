#include "database.h"

#include <algorithm>

ostream& operator<<(ostream& os, const pair<Date, string> p){
    os << p.first << " " << p.second;
    return os;
}

void Database::Add(Date date, string event) {
    if (database.empty()) {
        set<string> tmp_set;
        vector<string> tmp_vector;
        auto it_set = tmp_set.insert(event);
        tmp_vector.push_back(event);
        Containers c;
        c.vector_data = tmp_vector;
        c.set_data = tmp_set;
        database.insert({date, c});
    } else {
        auto it = database.upper_bound(date);
        if (prev(it)->first == date) {
            auto search = it->second.set_data.find(event);
            if (search == it->second.set_data.end()) {
                prev(it)->second.vector_data.push_back(event);
                prev(it)->second.set_data.insert(event);
            }
        } else {
            set<string> tmp_set;
            vector<string> tmp_vector;
            auto it_set = tmp_set.insert(event);
            tmp_vector.push_back(event);
            Containers c;
            c.vector_data = tmp_vector;
            c.set_data = tmp_set;
            database.insert(prev(it), {date, c});
        }
        /*if (it != database.end()) {
            auto search = it->second.set_data.find(event);
            if (search == it->second.set_data.end()) {
                it->second.vector_data.push_back(event);
                it->second.set_data.insert(event);
            }
        } else {
            database[date].vector_data.push_back(event);
            database[date].set_data.insert(event);*/
            /*set<string> tmp_set;
            vector<string> tmp_vector;
            auto it_set = tmp_set.insert(event);
            tmp_vector.push_back(event);
            Containers c;
            c.vector_data = tmp_vector;
            c.set_data = tmp_set;
            database.insert({date, c});*/
            //database[date].vector_data.push_back(event);
            //auto it = database.find(date);
            //it->second.set_data.insert(event);
            //database[date].set_data = tmp_set;
        //}
    }
    //if (database[date].empty()) {
        //set<string> tmp;
        //auto it = tmp.insert(event);
        //database[date].base_set.insert(event);
        //database[date].base_vector.push_back(event);
        //database_set.insert({date, tmp});
        //database[date].push_back(event);
    /*} else {
        auto search = database_set[date].find(event);
        if (search == database_set[date].end()) {
            database[date].push_back(event);
            database_set[date].insert(event);
        }
    }*/
}

int Database::RemoveIf(function<bool(const Date&, const string&)>p) {
    int deleted_data_num = 0;
    bool erased = false;

    for (auto i2 = database.begin(); i2 != database.end();) {
        for (auto j2 = i2->second.set_data.begin(); j2 != i2->second.set_data.end();) {
            if (p(i2->first, *j2)) {
                auto it = find(database[i2->first].vector_data.begin(), database[i2->first].vector_data.end(), *j2);
                database[i2->first].vector_data.erase(it);
                j2 = i2->second.set_data.erase(j2);
                deleted_data_num++;
                if (i2->second.vector_data.empty()) {
                    //database.erase(i2->first);
                    i2 = database.erase(i2);
                    erased = true;
                    //cout << "erased" << endl;
                    break;
                } else {
                    erased = false;
                }
            } else {
                ++j2;
                erased = false;
            }
        }
        //cout << "for 1" << endl;
        if (!erased) {
            i2++;
        }
    }
    //cout << "after for" << endl;

    return deleted_data_num;
}

VectorFindDatabse Database::FindIf(function<bool(const Date&, const string&)>p) {
    VectorFindDatabse find_database;

    for (auto i = database.begin(); i != database.end(); i++) {
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