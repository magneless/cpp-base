CXX := g++

CXXFLAGS := -Wall -Wextra -Werror

GFLAGS := -lgtest -lgtest_main -pthread

all: build

build: main

main: main.o BigInt.o
	$(CXX) main.o BigInt.o -g -o main.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

BigInt.o: BigInt.cpp
	$(CXX) $(CXXFLAGS) -c BigInt.cpp -o BigInt.o

run: build
	./main.exe

memory: build
	valgrind $(VALGRIND_OPTS) ./main.exe

memory_test: test
	valgrind $(VALGRIND_OPTS) ./tests.exe

test: tests
	./tests.exe

tests: tests.o  BigInt.o
	$(CXX) $(CXXFLAGS) BigInt.o tests.o $(GFLAGS) -g -o tests.exe

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp $(GFLAGS)

clean:
	rm -rf *.o *.exe

.PHONY: all build run memory clean
