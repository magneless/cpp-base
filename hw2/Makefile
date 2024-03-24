CXX := g++

CXXFLAGS := -Wall -Wextra -Werror

GFLAGS := -lgtest -lgtest_main -pthread

VALGRIND_OPTS := --leak-check=full --show-leak-kinds=all --track-origins=yes

all: build

build: main

main: main.o parser.o
	$(CXX) $(CXXFLAGS) main.o parser.o -o main.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

parser.o:
	$(CXX) $(CXXFLAGS) -c parser.cpp

run: build
	./main.exe

memory: build
	valgrind $(VALGRIND_OPTS) ./main.exe

memory_test: test
	valgrind $(VALGRIND_OPTS) ./tests.exe

test: tests
	./tests.exe

tests: parser.o tests.o
	$(CXX) $(CXXFLAGS) parser.o tests.o $(GFLAGS) -g -o tests.exe

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp $(GFLAGS)

clean:
	-rm -rf *.o *.exe

.PHONY: all build run memory clean
