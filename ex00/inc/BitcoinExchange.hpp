#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange{
    private:
        std::map<std::string, double> _bitcoinData;
        std::map<std::string, double> _inputData;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        bool IsValidOpen(std::string &dataPath);
        void set_value(std::string &dataPath);

        // "date | value" format
        bool IsInputValidData();
        // Year-Month-Day
        bool IsInputValidDate();
        // between _bitcoinData.begin() to _bitcoinData.rbegin()
        bool IsInputDateValue();
        // 0 ~ 1000
        bool IsInputValidValue();
};

#endif