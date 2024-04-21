CXX := g++

CXXFLAGS := -Wall -Wextra -Werror

GFLAGS := -lgtest -lgtest_main -pthread

VALGRIND_OPTS := --leak-check=full --show-leak-kinds=all --track-origins=yes

all: build

build: main

main: main.o matrix.o
	$(CXX) main.o matrix.o -g -o main.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

matrix.o: matrix.o
	$(CXX) $(CXXFLAGS) -c matrix.cpp

run: build
	./main.exe

test: tests
	./tests.exe

tests: tests.o matrix.o
	$(CXX) $(CXXFLAGS) tests.o matrix.o $(GFLAGS) -g -o tests.exe

tests.o:
	$(CXX) $(CXXFLAGS) -c tests.cpp $(GFLAGS) -o tests.o

memory: build
	valgrind $(VALGRIND_OPTS) ./main.exe

memory_test: test
	valgrind $(VALGRIND_OPTS) ./tests.exe

clean:
	rm -rf *.o *.exe

.PHONY: all build run memory clean