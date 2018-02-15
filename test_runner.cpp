#include "test_runner.h"

using namespace std;

ostream& operator<<(ostream& os, const vector<string> v) {
    for (auto i : v) {
        os << i << " ";
    }

    return os;
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}
