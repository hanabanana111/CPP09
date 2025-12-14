#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

#define CSV_PATH "../cpp_09/data.csv"

class BitcoinExchange{
    private:
        std::map<std::string, double> _dataBase;
        std::string _date;
        double _value;

        void processLine(const std::string &line);

        void parseLine(const std::string &line);

        bool IsValidData(const std::string &date);
        bool isLeap(int y);


        bool IsNumValue(const std::string &value);
        bool IsMinusValue(const double &value);
        bool IsTooBigValue(const std::string &value);

        void loadDatabase(const std::string &csvPath);
        std::string findNearestDate(const std::string &date);

        static std::string trim(const std::string line);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        void run(const std::string &inputPath);
};

#endif