#include  "../inc/BitcoinExchange.hpp"

int main(int argc, char **args){
    if (argc != 2){
        std::cerr << "Error: Invalid arg." << std::endl;
        return 0;
    }
    try{    
        BitcoinExchange BE = BitcoinExchange();
        BE.run(args[1]);
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
};
