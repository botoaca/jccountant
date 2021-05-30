#ifndef DATABASE_H
#define DATABASE_H

#include "Transaction.h"
#include <iostream>

class Database {
    std::string _dbPath;

    public:
        Database(std::string);
        std::string getDbPath();
        void addEntry(Transaction);
        void removeEntry(int);
        void seeEntries();
        void resetDatabase();
};

#endif // DATABASE_H