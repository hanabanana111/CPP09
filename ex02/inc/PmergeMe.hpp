#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <climits>
#include <stdexcept>

class PmergeMe{
    private:
        std::vector<int> _vec;
        std::deque<int> _deq;

        void parseInput(char **av);

        void fordJohnsonVector(std::vector<int> &vec);
        void insertVector(std::vector<int> &vec, int extra);

        void fordJohnsonDeque();

    public:
        PmergeMe(char **av);
        ~PmergeMe();
        
        void run();
};

#endif
