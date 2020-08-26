
SRC=$(wildcard *.cpp)

all: $(SRC)
	$(CXX) -o run_tests $^  -std=c++17 -O2 -Wall
