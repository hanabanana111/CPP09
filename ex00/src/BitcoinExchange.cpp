#include  "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){};
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){};
BitcoinExchange::~BitcoinExchange(){};


void BitcoinExchange::processLine(const std::string &line){
    std::string tmp = trim(line);
    if (tmp == ""){
        return ;
    }

};
void BitcoinExchange::parseLine(const std::string &line){
    const std::string sep = "|";
    size_t pos = line.find(sep); 
    std::string tmpDate;
    std::string tmpValue;
    int flag = 0;

    if (pos == std::string::npos || 
        line.find(sep, pos + sep.size()) != std::string::npos){
        std::cerr << "Error: bad input => " << line << std::endl;
        return ;
    }

    tmpDate = trim(line.substr(0, pos));
    tmpValue = trim(line.substr(pos, line.size()));
    if (tmpDate == "" || tmpValue == ""|| IsValidData(tmpDate) == false){
        std::cerr << "Error: bad input => " << line << std::endl;
        return ;
    }

    if (IsValidValue()){

    }
};

//まずは、数値かチェックする、マイナス化チェックする、大きすぎないかチェックする
bool BitcoinExchange::IsValidData(const std::string &date){};
bool BitcoinExchange::IsValidValue(const std::string &value){};
void BitcoinExchange::loadDatabase(const std::string &csvPath){};
std::string BitcoinExchange::findNearestDate(const std::string &date){};

static std::string trim(const std::string line){
    const std::string spaces = " \n\r\t 　  ";
    size_t start = line.find_first_of(spaces);
    size_t end = line.find_last_of(spaces);
    if (start == std::string::npos){
        return "";
    }
    return line.substr(start, end - start + 1);
};

void BitcoinExchange::run(const std::string &dataPath){
    std::ifstream input(dataPath);

    if (!input){
        throw std::runtime_error("ファイルを開けません：" + dataPath);
    }
    std::string line;
    while(std::getline(input, line)){
        processLine(line);
    }
};
