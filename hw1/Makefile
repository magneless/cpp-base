CXX := g++

CXXFLAGS := -Wall -Wextra -Werror

GFLAGS := -lgtest -lgtest_main -pthread 

VALGRIND_OPTS := --leak-check=full --show-leak-kinds=all --track-origins=yes

all: build

build: main


main: main.o alloc.o
	$(CXX) main.o alloc.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
 
alloc.o: alloc.cpp
	$(CXX) $(CXXFLAGS) -c alloc.cpp

run: build
	./main

test: tests
	./tests

tests: tests.o alloc.o
	$(CXX) $(CXXFLAGS) tests.o alloc.o $(GFLAGS) -o tests

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp $(GFLAGS)

memory: build
	valgrind $(VALGRIND_OPTS) ./main

memory_test: test
	valgrind $(VALGRIND_OPTS) ./tests

clean:
	rm -rf *.o tests main

.PHONY: all build run memory clean
