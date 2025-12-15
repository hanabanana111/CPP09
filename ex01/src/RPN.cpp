#include "../inc/RPN.hpp"

int RPN::evaluate(const std::string str){
    std::stack<long> nums;
    std::string token;
    std::string operators = "+-/*";
    long result, tmp, a, b;

    std::stringstream ss(str);
    while(ss >> token){
        if (token.size() != 1){
            throw std::runtime_error("Error");
        }
        if (std::isdigit(token[0])){
            std::istringstream iss(token);
            iss >> tmp;
            nums.push(tmp);
        } else if (operators.find(token[0]) != std::string::npos){
            if (nums.size() < 2)
                throw std::runtime_error("Error");
            b = nums.top();
            nums.pop();
            a = nums.top();
            nums.pop();
            if (token[0] == '+'){
                result = (a + b);
            } else if (token[0] == '-'){
                result = (a - b);
            } else if (token[0] == '/'){
                if (b == 0)
                    throw std::runtime_error("Error");
                result = (a / b);
            } else if (token[0] == '*'){
                result = (a * b);
            }
        if (result > std::numeric_limits<int>::max()
            || result < std::numeric_limits<int>::min())
        {
            throw std::runtime_error("Error");
        }
            nums.push(result);
        }else{
            throw std::runtime_error("Error");
        }
    }
    if (nums.size() != 1){
        throw std::runtime_error("Error");
    }
    return nums.top();
};
