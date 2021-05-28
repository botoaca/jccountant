#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>

class Transaction {
    std::string _date;
    std::string _type;
    std::string _reason;
    int _amount;

    public:
        Transaction(std::string date, std::string type, std::string, int amount);
        std::string getDate();
        std::string getType();
        std::string getReason();
        int getAmount();
};

#endif // TRANSACTION_H