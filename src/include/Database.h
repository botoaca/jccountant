#ifndef DATABASE_H
#define DATABASE_H

#include "Transaction.h"
#include <iostream>

class Database {
    std::string _dbPath;

    public:
        Database(std::string dbPath);
        void addEntry(Transaction t);
        void removeEntry(int idx);
        void seeEntries();
        void resetDatabase();
};

#endif // DATABASE_H