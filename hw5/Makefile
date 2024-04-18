CXX := g++

CXXFLAGS := -Wall -Wextra -Werror

GFLAGS := -lgtest -lgtest_main -pthread

all: build

build: main

main: main.o serializer.o
	$(CXX) main.o serializer.o -g -o main.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

serializer.o: serializer.cpp
	$(CXX) $(CXXFLAGS) -c serializer.cpp -o serializer.o

run: build
	./main.exe

test: tests
	./tests.exe

tests: tests.o serializer.o
	$(CXX) $(CXXFLAGS) tests.o serializer.o $(GFLAGS) -g -o tests.exe

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp $(GFLAGS)

memory: build
	valgrind $(VALGRIND_OPTS) ./main.exe

memory_test: test
	valgrind $(VALGRIND_OPTS) ./tests.exe

clean:
	rm -rf *.o tests.exe main.exe

.PHONY: all build run memory clean
