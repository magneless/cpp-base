CXX := g++ -std=c++20

CXXFLAGS := -Wall -Wextra -Werror

GFLAGS := -lgtest -lgtest_main -pthread

VALGRIND_OPTS := --leak-check=full --show-leak-kinds=all --track-origins=yes

all: build


build: main

main: main.o format.o
	$(CXX) $(CXXFLAGS) -g -o main.exe main.o format.o 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
 
format.o: format.cpp
	$(CXX) $(CXXFLAGS) -c format.cpp

run: build
	./main.exe

test: tests
	./tests.exe

tests: tests.o format.o
	$(CXX) $(CXXFLAGS) tests.o format.o $(GFLAGS) -g -o tests.exe

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp $(GFLAGS)

memory: build
	valgrind $(VALGRIND_OPTS) ./main.exe

memory_test: test
	valgrind $(VALGRIND_OPTS) ./tests.exe

clean:
	rm -rf *.o *.exe

.PHONY: all build run memory clean