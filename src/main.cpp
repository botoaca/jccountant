#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
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
        // Step 1: Create the file
        std::ofstream initializeFile(dbPath);
        initializeFile << "[]";
        initializeFile.close();

        // Step 2: Generate the JSON array
        int initialBalance = 0;

        std::cout << "What is your initial balance?\n";
        std::cin >> initialBalance;
        
        json initial = {
            { "initial", initialBalance }
        };

        std::ifstream dbFile(dbPath);
        json result = json::array();
        dbFile >> result;
        result.push_back(initial);
        dbFile.close();

        // Step 3. Write the JSON array
        std::ofstream file(dbPath, std::ios_base::trunc | std::ios_base::out);
        file << std::setw(4) << result;
        file.close();
    }

    Database db(dbPath);

    time_t now = time(0);
    std::string date = ctime(&now);

    char inputType[6];
    char upperInputType[6];
    char inputReason[80];
    int inputAmount = 0;

    int choice;

    std::cout << "What do you want to do?\n1. Add an entry\n2. Remove an entry\n3. See all entries\n4. Reset the database\n";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            do {
                std::cout << "What is the type of this transaction? (ADD/REMOVE)\n";
                std::cin.ignore(INT_MAX, '\n');
                std::cin.get(inputType, 6);
                for (unsigned i = 0; i < strlen(inputType); i++)
                    upperInputType[i] = toupper(inputType[i]);
            } while (!(strcmp(upperInputType, "ADD") == 0 || strcmp(upperInputType, "REMOVE") == 0));
            
            std::cout << "What is the reason for this transaction?\n";
            std::cin.ignore(INT_MAX, '\n');
            std::cin.get(inputReason, 80);

            std::cout << "What is the amount of this transaction?\n";
            std::cin >> inputAmount;

            Transaction t(date, upperInputType, inputReason, inputAmount);

            db.addEntry(t);
            break;
        }
        case 2: {
            int idx;
            std::ifstream inputFile(dbPath);
            int dbArraySize = json::array().max_size();

            do {
                std::cout << "Which entry would you like to remove? (Starting from 1)\n";
                std::cin >> idx;
                db.removeEntry(idx);
            } while (idx <= dbArraySize && idx != 0);

            break;
        }
        case 3:
            db.seeEntries();
            break;
        case 4:
            db.resetDatabase();
            break;
    }

    return 0;
}