#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

string ParseEvent(istream& is) {
    string event;
    getline(is, event);
    const char* t = " \t\n\r\f\v";
    event.erase(0, event.find_first_not_of(t));

    return event;
}


void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            auto count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestDbSimple(){
  Database db;
  stringstream ss;
  db.Print(ss);
  AssertEqual(ss.str(), "", "empty database print"); //  проверяем на пустую базу печатание 
  ss.str(""); // clear ss
  try{
    ss << db.Last(Date(5, 10, 15));
  } catch (exception &) {};
  AssertEqual(ss.str(), "", "empty database last");
  auto condition = ParseCondition(ss);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
  AssertEqual(db.FindIf(predicate).size(), 0, "empty find");
  AssertEqual(db.RemoveIf(predicate), 0, "empty remove");
  //****************************************************************
  {
    istringstream is("2017-11-07 big sport event");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
    db.Print(temp);
    AssertEqual(temp.str(), "2017-11-07 big sport event\n", "add test"); 
  }
  {
    istringstream is(""); // проверка 
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    AssertEqual(entries.size(), 1, "find all test size");
    stringstream temp;
    for(const auto &x: entries){
      temp << x << endl;
    }
    AssertEqual(temp.str(), "2017-11-07 big sport event\n", "find all test value");
  }
  {
    istringstream is("2017-11-08");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "2017-11-07 big sport event\n", "last test the day after event");
  }
  {
    istringstream is("2017-11-07");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "2017-11-07 big sport event\n", "last test in day of event");
  }
  {
    istringstream is("2017-11-06");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "No entries\n", "last test in day before event");
  }
  {
    istringstream is("2017-11-07 small sport event");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
    db.Print(temp);
    AssertEqual(temp.str(), "2017-11-07 big sport event\n2017-11-07 small sport event\n", "add test 2"); 
  }
  {
    istringstream is("2017-11-07");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "2017-11-07 small sport event\n", "last test in day of event 2");
  }
  {
    istringstream is("");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    auto count = db.RemoveIf(predicate);
    AssertEqual(count, 2, "del test");
  }
  {
    stringstream temp;
    db.Print(ss);
    AssertEqual(ss.str(), "", "print empty test");
  }
  {
    istringstream is("");
    auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      auto count = db.RemoveIf(predicate);
    AssertEqual(count, 0, "del all empty");
  }
  {
    istringstream is("");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    AssertEqual(entries.empty(), true, "find all empty db");
  }
}

void TestDbMedium(){
  Database db;
  /*
    добавляем 2000-1-1 ev1, 2000-2-1 ev2 ev3, 2000-3-1 ev1 ev4 ev5
  */
  {
    istringstream is("2000-1-1 ev1");
  stringstream temp;
  const auto date = ParseDate(is);
  const auto event = ParseEvent(is);
  db.Add(date, event);
  }

  //*******************************************
  {
    istringstream is("2000-2-1 ev3");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("2000-2-1 ev2");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }

  //*******************************************
  {
    istringstream is("2000-3-1 ev1");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("2000-3-1 ev4");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("2000-3-1 ev5");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    stringstream temp;
    db.Print(temp);
    AssertEqual(temp.str(), "2000-01-01 ev1\n2000-02-01 ev3\n2000-02-01 ev2\n2000-03-01 ev1\n2000-03-01 ev4\n2000-03-01 ev5\n", "print test");
  }
  {
    istringstream is("2017-11-1");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "2000-03-01 ev5\n", "last 1 medium");
  }
  {
    istringstream is("2000-3-1");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "2000-03-01 ev5\n", "last 2 medium");
  }
  {
    istringstream is("2000-02-15");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "2000-02-01 ev2\n", "last 3 medium");
  }
  {
    istringstream is("1999-1-1");
    stringstream ss;
    try {
      ss << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
      ss << "No entries" << endl;
      }
    AssertEqual(ss.str(), "No entries\n", "last 4 medium");
  }
  {
    istringstream is("");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-01-01 ev1\n2000-02-01 ev3\n2000-02-01 ev2\n2000-03-01 ev1\n2000-03-01 ev4\n2000-03-01 ev5\n", "find all test");
  }
  {
    istringstream is("event == \"ev1\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-01-01 ev1\n2000-03-01 ev1\n", "find 2 events test");
  }
  {
    istringstream is("event == \"ev6\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "", "find no events test");
  }
  {
    istringstream is("date >= \"2000-2-1\" AND date <= \"2000-2-31\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-02-01 ev3\n2000-02-01 ev2\n", "find feb test");
  }
  {
    istringstream is("date >= \"2000-2-1\" AND date <= \"2000-2-31\" AND event != \"ev3\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-02-01 ev2\n", "find feb without ev3 test");
  }
  {
    istringstream is("event != \"ev1\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-02-01 ev3\n2000-02-01 ev2\n2000-03-01 ev4\n2000-03-01 ev5\n", "find except ev1 test 1");
  }
  {
    istringstream is("date != \"2000-2-1\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-01-01 ev1\n2000-03-01 ev1\n2000-03-01 ev4\n2000-03-01 ev5\n", "find except ev1 test 2");
  }
  {
    istringstream is("date == \"2000-2-1\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-02-01 ev3\n2000-02-01 ev2\n", "find except ev1 test 3");
  }
  {
    istringstream is("date == \"2000-2-1\" OR date == \"2000-3-1\" AND event != \"ev4\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "2000-02-01 ev3\n2000-02-01 ev2\n2000-03-01 ev1\n2000-03-01 ev5\n", "find except ev5 test");
  }
  {
    istringstream is("date == \"2000-2-1\" AND (event != \"ev2\" AND event != \"ev3\")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    auto count = db.RemoveIf(predicate);
    AssertEqual(count, 0, "del nothing");
  }
  {
    istringstream is("date == \"2000-3-1\" AND (event == \"ev1\")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    auto count = db.RemoveIf(predicate);
    AssertEqual(count, 1, "del 1");
    stringstream ss;
    db.Print(ss);
    AssertEqual(ss.str(), "2000-01-01 ev1\n2000-02-01 ev3\n2000-02-01 ev2\n2000-03-01 ev4\n2000-03-01 ev5\n", "del second ev1 test");
  }
  {
    istringstream is("");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    auto count = db.RemoveIf(predicate);
    AssertEqual(count, 5, "del 1");
    stringstream ss;
    db.Print(ss);
    AssertEqual(ss.str(), "", "del all test");
  }
  {
    istringstream is("");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    auto count = db.RemoveIf(predicate);
    AssertEqual(count, 0, "del all second");
    stringstream ss;
    db.Print(ss);
    AssertEqual(ss.str(), "", "del all second test");
  }
  {
    istringstream is("event == \"ev6\"");
    stringstream ss;
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    for (const auto& entry : entries) {
        ss << entry << endl;
    }
    AssertEqual(ss.str(), "", "find no events test");
  }
  {
    stringstream ss;
    db.Print(ss);
    AssertEqual(ss.str(), "", "print nothing");
  }
}

void TestDbRemove(){
  Database db;
  /*
    добавляем 1-1-1 b, 1-1-1 c, 1-1-1 d, 1-1-1 a, 1-1-1 f, 1-1-1 e
  */
  {
    istringstream is("1-1-1 b");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("1-1-1 c");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("1-1-1 d");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("1-1-1 a");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("1-1-1 f");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("1-1-1 e");
    stringstream temp;
    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);
    db.Add(date, event);
  }
  {
    istringstream is("event > \"d\"");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    auto count = db.RemoveIf(predicate);
    AssertEqual(count, 2, "del 2");
    stringstream ss;
    db.Print(ss);
    AssertEqual(ss.str(), "0001-01-01 b\n0001-01-01 c\n0001-01-01 d\n0001-01-01 a\n", "del bigger than d test");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  tr.RunTest(TestDbSimple, "TestDbSimple");
  tr.RunTest(TestDbMedium, "TestDbMedium");
  tr.RunTest(TestDbRemove, "TestDbRemove");
}
