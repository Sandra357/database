all: database_project

clean:
	rm -rf database_project *.o

main.o: main.cpp
	g++ -std=c++17 -c -o main.o main.cpp

database.o: database.cpp
	g++ -std=c++17 -c -o database.o database.cpp

condition_parser.o: condition_parser.cpp
	g++ -std=c++17 -c -o condition_parser.o condition_parser.cpp

date.o: date.cpp
	g++ -std=c++17 -c -o date.o date.cpp

node.o: node.cpp
	g++ -std=c++17 -c -o node.o node.cpp

token.o: token.cpp
	g++ -std=c++17 -c -o token.o token.cpp

condition_parser_test.o: condition_parser_test.cpp
	g++ -std=c++17 -c -o condition_parser_test.o condition_parser_test.cpp

database_project: main.o database.o condition_parser.o date.o node.o token.o condition_parser_test.o
	g++ -std=c++17 -o database main.o database.o condition_parser.o date.o node.o token.o \
	condition_parser_test.o
