#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>

class RPN{
    public :
        static int evaluate(const std::string str);
};

#endif