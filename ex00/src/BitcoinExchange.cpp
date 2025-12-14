#include  "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange():
    _date(""),_value(0){};
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other):
    _date(other._date),_value(other._value){};
BitcoinExchange::~BitcoinExchange(){};

void BitcoinExchange::run(const std::string &dataPath){
    if(loadDatabase(CSV_PATH) == false) return;
    std::ifstream input(dataPath.c_str());
    if (!input){
        throw std::runtime_error("ファイルを開けません：" + dataPath);
    }
    std::string line;
    std::getline(input, line);
    if (line != "date | value"){
        throw std::runtime_error("1行目が「date | value」になっていません。");
    }
    while(std::getline(input, line)){
        processLine(line);
    }
    input.close();
};

void BitcoinExchange::processLine(const std::string &line){
    std::string tmp = trim(line);
    if (tmp == "") return;
    if(parseLine(line, "|") == false) return;
    findNearestDate();
};
bool BitcoinExchange::parseLine(const std::string &line, const std::string &sep){
    size_t pos = line.find(sep); 
    std::string tmpDate;
    std::string tmpValue;

    if (pos == std::string::npos || 
        line.find(sep, pos + sep.size()) != std::string::npos){
        std::cerr << "Error: bad input => " << line << std::endl;
        return false;
    }

    tmpDate = trim(line.substr(0, pos));
    tmpValue = trim(line.substr(pos + sep.size(), line.size() - pos - sep.size()));
    if (tmpDate == "" || tmpValue == ""|| 
        IsValidData(tmpDate) == false || IsNumValue(tmpValue) == false){
        std::cerr << "Error: bad input => " << line << std::endl;
        return false;
    }

    if (IsMinusValue() == false){
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }

    if (sep == "|" && IsTooBigValue() == false){
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
};

bool BitcoinExchange::IsValidData(const std::string &date){
    if (date.size() != 10){
        return false;
    }
    std::stringstream ss(date);
    int year, month, day;
    char dash1, dash2;
    if (!(ss >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-') {
        return false;
    }
    char c;
    if (ss >> c) return false;
    //year check
    if (year < 1 || year > THIS_YEAR) return false;
    //month check
    if (month < 1 || month > 12) return false;
    //day check
    static const int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int maxDay = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year)) {
        maxDay = 29;
    }

    if (day < 1 || day > maxDay) return false;
    this->_date = date;
    return true;
};

bool BitcoinExchange::isLeapYear(int year)
{
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return (year % 4 == 0);
}

bool BitcoinExchange::IsNumValue(const std::string &value){
    std::stringstream ss(trim(value));
    double tmpValue;
    if (!(ss >> tmpValue)){
        return false;
    }

    this->_value = tmpValue;
    return true;
};

bool BitcoinExchange::IsMinusValue(){
    if (this->_value < 0) return false;
    return true;
};

bool BitcoinExchange::IsTooBigValue(){
    if (this->_value > 1000) return false;
    return true;
};

bool BitcoinExchange::loadDatabase(const std::string &csvPath){
    std::ifstream data(csvPath.c_str());

    if (!data){
        throw std::runtime_error("ファイルを開けません：" + csvPath);
    }
    std::string line;
    std::getline(data, line);
    if (line != "date,exchange_rate"){
        throw std::runtime_error("1行目が「date | value」になっていません。");
    }
    while(std::getline(data, line)){
        if (parseLine(line, ",") == false){
            data.close();
            return false;
        }
        this->_dataBase.insert(std::pair<std::string, double>(this->_date, this->_value));
    }
    return true;
};

void BitcoinExchange::findNearestDate(){
    std::map<std::string, double>::iterator it = this->_dataBase.lower_bound(this->_date);
    if (it->first == this->_date){
        std::cout << this->_date << " => " << this->_value << " = " << it->second*this->_value << std::endl;
        return ;
    }
    if (it != this->_dataBase.begin()){
        it--;
        std::cout << this->_date << " => " << this->_value << " = " << it->second*this->_value << std::endl;
    }
    if (it == this->_dataBase.begin()){
        std::cout << this->_date << " => " << this->_value << " = " << it->second*this->_value << std::endl;
    }
    return ;
};

std::string BitcoinExchange::trim(const std::string line){
    const std::string spaces = " \n\r\t 　  ";
    size_t start = line.find_first_not_of(spaces);
    size_t end = line.find_last_not_of(spaces);
    if (start == std::string::npos || end == std::string::npos) return "";
    return line.substr(start, end - start + 1);
};
