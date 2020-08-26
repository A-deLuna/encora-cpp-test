SRC=$(wildcard *.cpp)
CFLAGS = -std=c++17 -O2 -Wall

run_tests: $(SRC)
	$(CXX) -o $@ $^ $(CFLAGS)

all: run_tests
