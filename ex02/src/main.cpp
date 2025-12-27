#include "../inc/PmergeMe.hpp"

int main(int ac, char **av){
    if (ac == 1){
        std::cerr << "Error: No arg" << std::endl;
        return 1;
    }
    try{
        PmergeMe pergeMe(av);
        pergeMe.run();
    } catch(std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
};