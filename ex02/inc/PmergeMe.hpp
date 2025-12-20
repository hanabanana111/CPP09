#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>

class PmergeMe{
    private:
        std::vector<int> _vec;
        std::deque<int> _deq;

        void parseInput(char **av);

        void sortVector();
        void sortDeque();

        void fordJohnsonVector();
        void fordJohnsonDeque();

    public:
        PmergeMe(char **av);
        ~PmergeMe();
        
        void run();
};

#endif
