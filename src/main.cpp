#include <iostream>
#include <fstream>
#include <ctime>
#include "nlohmann/json.hpp"
#include "include/Transaction.h"
#include "include/Database.h"

using json = nlohmann::json;

bool dbExists(const char *filename) {
    std::ifstream input(filename);
    return input.good();
}

int main() {
    std::string dbName;
    char* dbPath;
    std::cout << "What is your database's name?\n(You can input a new name to create a new database.)\n";
    std::cin >> dbName;
    dbPath = &(dbName + ".json")[0];

    if (!dbExists(dbPath)) {
        std::ofstream file(dbPath);
        file << "[]";
    }

    Database db(dbPath);

    time_t now = time(0);
    std::string date = ctime(&now);

    char inputType[8];
    char inputReason[80];
    int inputAmount = 0;

    int choice;

    std::cout << "What do you want to do?\n1. Add an entry\n2. Remove an entry\n3. See all entries\n4. Reset the database\n";
    std::cin >> choice;

    switch (choice) {
        case 1:
        {
            std::cout << "What is the type of this transaction?\n";
            std::cin.ignore(INT_MAX, '\n');
            std::cin.get(inputType, 8);

            std::cout << "What is the reason for this transaction?\n";
            std::cin.ignore(INT_MAX, '\n');
            std::cin.get(inputReason, 80);

            std::cout << "What is the amount of this transaction?\n";
            std::cin >> inputAmount;

            Transaction t(date, inputType, inputReason, inputAmount);

            db.addEntry(t);
            break;
        }
        case 2:
            int idx;
            std::cout << "Which entry would you like to remove? (Starting from 0)\n";
            std::cin >> idx;
            db.removeEntry(idx);
            break;
        case 3:
            db.seeEntries();
            break;
        case 4:
            db.resetDatabase();
            break;
    }

    return 0;
}