#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <climits>
#include <stdexcept>
#include <algorithm>

class PmergeMe{
    private:
        std::vector<int> _vec;
        std::deque<int> _deq;

        void parseInput(char **av);

        void fordJohnsonVector(std::vector<int> &vec);
        std::vector<int> buildJacobsthalVector(int max);
        std::vector<int> buildInsertionOrderVector(int losersSize);
        void insertAtBinarySearchVector(std::vector<int>& winners, int val, int upTo);
        int binarySearchInsertPositionVector(const std::vector<int>& winners, int val, int upTo);


        void fordJohnsonDeque(std::deque<int> &vec);
        std::deque<int> buildJacobsthalDeque(int max);
        std::deque<int> buildInsertionOrderDeque(int losersSize);
        void insertAtBinarySearchDeque(std::deque<int>& winners, int val, int upTo);
        int binarySearchInsertPositionDeque(const std::deque<int>& winners, int val, int upTo);

    public:
        PmergeMe(char **av);
        ~PmergeMe();
        
        void run();
};

#endif
