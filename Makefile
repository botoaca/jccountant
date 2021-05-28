all: build output

build:
	mkdir build

output: main.o transaction.o database.o 
	g++ build/main.o build/transaction.o build/database.o -o build/output

main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

transaction.o: src/Transaction.cpp src/include/Transaction.h
	g++ -c src/Transaction.cpp -o build/Transaction.o

database.o: src/Database.cpp src/include/Database.h
	g++ -c src/Database.cpp -o build/Database.o

clean:
	del build/*.o build/output.exe