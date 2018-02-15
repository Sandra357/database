all: database_project

clean:
	rm -rf database_project *.o

main.o: main.cpp
	g++ -std=c++17 -c -o main.o main.cpp

test_runner.o: test_runner.cpp
	g++ -std=c++17 -c -o test_runner.o test_runner.cpp

condition_parser_test.o: condition_parser_test.cpp
	g++ -std=c++17 -c -o condition_parser_test.o condition_parser_test.cpp

condition_parser.o: condition_parser.cpp
	g++ -std=c++17 -c -o condition_parser.o condition_parser.cpp

database.o: database.cpp
	g++ -std=c++17 -c -o database.o database.cpp

date.o: date.cpp
	g++ -std=c++17 -c -o date.o date.cpp

node.o: node.cpp
	g++ -std=c++17 -c -o node.o node.cpp

token.o: token.cpp
	g++ -std=c++17 -c -o token.o token.cpp

database_project: main.o test_runner.o condition_parser_test.o condition_parser.o database.o date.o node.o \
	token.o
	g++ -std=c++17 -o database main.o test_runner.o condition_parser_test.o condition_parser.o database.o  \
	date.o node.o token.o
