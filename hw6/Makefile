CXX := g++

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

clean:
	rm -rf *.o *.exe