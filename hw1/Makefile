CXX := g++

CXXFLAGS := -Wall -Wextra -Werror

GFLAGS := -lgtest -lgtest_main -pthread

VALGRIND_OPTS := --leak-check=full --show-leak-kinds=all --track-origins=yes

all: build

build: main


main: main.o alloc.o
	$(CXX) main.o alloc.o -g -o main.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
 
alloc.o: alloc.cpp
	$(CXX) $(CXXFLAGS) -c alloc.cpp

run: build
	./main.exe

test: tests
	./tests.exe

tests: tests.o alloc.o
	$(CXX) $(CXXFLAGS) tests.o alloc.o $(GFLAGS) -g -o tests.exe

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp $(GFLAGS)

memory: build
	valgrind $(VALGRIND_OPTS) ./main.exe

memory_test: test
	valgrind $(VALGRIND_OPTS) ./tests.exe

clean:
	rm -rf *.o tests.exe main.exe

.PHONY: all build run memory clean
