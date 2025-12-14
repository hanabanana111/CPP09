#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

#define CSV_PATH "./cpp_09/data.csv"
#define THIS_YEAR 2025

class BitcoinExchange{
    private:
        std::map<std::string, double> _dataBase;
        std::string _date;
        double _value;

        void processLine(const std::string &line);

        bool parseLine(const std::string &line, const std::string &sep);

        bool IsValidData(const std::string &date);
        bool isLeap(int y);


        bool IsNumValue(const std::string &value);
        bool IsMinusValue();
        bool IsTooBigValue();

        bool loadDatabase(const std::string &csvPath);
        void findNearestDate();

        static std::string trim(const std::string line);
        static bool isLeapYear(int year);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        void run(const std::string &inputPath);
};

#endif