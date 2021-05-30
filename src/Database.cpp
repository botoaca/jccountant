#include "include/Database.h"
#include "include/Transaction.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

using json = nlohmann::json;

Database::Database(std::string dbPath) {
    _dbPath = dbPath;
}

void Database::addEntry(Transaction t) {
    json j = {
        { "date", t.getDate() },
        { "type", t.getType() },
        { "reason", t.getReason() },
        { "amount", t.getAmount() },
        { "balance", t.getBalance() }
    };

    std::ifstream inputFile(_dbPath);
    json result = json::array();
    inputFile >> result;
    result.push_back(j);

    std::ofstream file(_dbPath, std::ios_base::trunc | std::ios_base::out);
    file << std::setw(4) << result;
}

void Database::removeEntry(int idx) {
    std::ifstream inputFile(_dbPath);
    json result = json::array();
    inputFile >> result;
    result.erase(idx);

    std::ofstream file(_dbPath);
    file << std::setw(4) << result;
}

void Database::seeEntries() {
    std::ifstream inputFile(_dbPath);
    json result = json::array();
    inputFile >> result;
    std::cout << std::setw(4) << result;
}

void Database::resetDatabase() {
        // Step 1: Create the file
        std::ofstream initializeFile(_dbPath);
        initializeFile << "[]";
        initializeFile.close();

        // Step 2: Generate the JSON array
        int initialBalance = 0;

        std::cout << "What is your initial balance?\n";
        std::cin >> initialBalance;

        
        json initial = {
            { "initial", initialBalance }
        };

        std::ifstream dbFile(_dbPath);
        json result = json::array();
        dbFile >> result;
        result.push_back(initial);
        dbFile.close();

        // Step 3. Write the JSON array
        std::ofstream file(_dbPath, std::ios_base::trunc | std::ios_base::out);
        file << std::setw(4) << result;
        file.close();
}