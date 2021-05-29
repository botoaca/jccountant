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
        { "amount", t.getAmount() }
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
    std::ofstream file(_dbPath);
    file << "[]";
}