CXX = g++
CXXFLAGS = -Wall

all: build build/output

build:
	mkdir build

build/output: build/main.o build/transaction.o build/database.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build/main.o: src/main.cpp src/nlohmann/json.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/transaction.o: src/Transaction.cpp src/include/Transaction.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/database.o: src/Database.cpp src/include/Database.h
	$(CXX) $(CXXFLAGS) -c $< -o $@