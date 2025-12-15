#include "../inc/RPN.hpp"

int main(int argc, char **argv){
    if (argc != 2){
        std::cerr << "Error" << std::endl;
        return 1;
    }
    try{
        int result;
        result = RPN::evaluate(argv[1]);
        std::cout << result << std::endl;
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
};

// "8 9 * 9 - 9 - 9 - 4 - 1 +"
// 42
// "7 7 * 7 -"
// 42
// "1 2 * 2 / 2 * 2 4 - +"
// 0
// "(1 + 1)"
// Error

// ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +" ; \
// ./RPN "7 7 * 7 -" ; \
// ./RPN "1 2 * 2 / 2 * 2 4 - +" ; \
// ./RPN "(1 + 1)"
