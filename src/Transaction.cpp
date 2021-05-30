#include "include/Transaction.h"
#include <iostream>

Transaction::Transaction(std::string date, std::string type, std::string reason, int amount) {
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
    
}