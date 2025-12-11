#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange{
    private:
        std::map<std::string, double> _inputData;

        void processLine(const std::string &line);

        void parseLine(const std::string &dataPath);
        bool IsValidData(std::string &date, double &value);
        bool IsValidValue(std::string &date, double &value);

        void loadDatabase(const std::string &csvPath);
        std::string findNearestDate(const std::string &date);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        void run(const std::string &inputPath);
};

#endif*