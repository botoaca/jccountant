#include "include/Transaction.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

Transaction::Transaction(std::string dbPath, std::string date, std::string type, std::string reason, int amount) {
    _dbPath = dbPath;
    _date = date;
    _type = type;
    _reason = reason;
    _amount = amount;
}

std::string Transaction::getDate() {
    return _date;
}

std::string Transaction::getType() {
    return _type;
}

std::string Transaction::getReason() {
    return _reason;
}

int Transaction::getAmount() {
    return _amount;
}

int Transaction::getBalance() {
    std::ifstream dbFile(_dbPath);
    json arr = json::array();
    dbFile >> arr;
    dbFile.close();

    if (_type == "ADD")
        return (int)arr[arr.size() - 1].at("balance") + _amount;
    if (_type == "REMOVE")
        return (int)arr[arr.size() - 1].at("balance") - _amount;
    
    return 0;
}