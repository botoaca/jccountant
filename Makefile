CXX = g++
CXXFLAGS = -Wall

all: build output

build:
	mkdir build

output: main.o transaction.o database.o 
	${CXX} ${CXXFLAGS} build/main.o build/transaction.o build/database.o -o build/output

main.o: src/main.cpp
	${CXX} ${CXXFLAGS} -c src/main.cpp -o build/main.o

transaction.o: src/Transaction.cpp src/include/Transaction.h
	${CXX} ${CXXFLAGS} -c src/Transaction.cpp -o build/Transaction.o

database.o: src/Database.cpp src/include/Database.h
	${CXX} ${CXXFLAGS} -c src/Database.cpp -o build/Database.o

clean:
	del build/*.o build/output.exe