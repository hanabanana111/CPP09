#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe(char **av){
    parseInput(av);
};

PmergeMe::~PmergeMe(){};

void PmergeMe::run(){
    std::cout << "Before: ";
    for (int i = 0; i < _vec.size(); i++) {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;

    clock_t start = clock();
    fordJohnsonVector(this->_vec);
    clock_t end = clock();

    std::cout << "After: ";
    for (int num : _vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << _vec.size() << "elements with std::vector : " << duration*1000000 << "us" << std::endl;

    start = clock();
    fordJohnsonDeque();
    end = clock();
     duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << _vec.size() << "elements with std::deque : " << duration*1000000 << "us" << std::endl;
};

void PmergeMe::parseInput(char **av){
    for (int i = 1; av[i] != NULL; i++){
        char *endPtr;
        long num = std::strtol(av[i], &endPtr, 10);

        if (*endPtr != '\0') {
            throw std::invalid_argument("Invalid argument (not a number)");
        }
        if (num <= 0) {
            throw std::invalid_argument("Non-positive number encountered");
        }
        if (num > INT_MAX) {
            throw std::out_of_range("Value exceeds INT_MAX");
        }
        _vec.push_back(static_cast<int>(num));
        _deq.push_back(static_cast<int>(num));
    }
};

void PmergeMe::fordJohnsonVector(std::vector<int> &vec){
    int n = vec.size();

    if (n <= 1){
        return;
    }
    // odd
    if (n%2 == 1){
        int extra = vec.back();
        vec.pop_back();
        fordJohnsonVector(vec);
        insertVector(vec, extra);
        return;
    }

    std::vector<int> winners;
    std::vector<std::pair<int, int>> losers;
    int specialLoser;

    // smallest num
    if (vec[0] < vec[1]){
        winners.push_back(vec[1]);
        specialLoser = vec[0];
    }else{
        winners.push_back(vec[0]);
        specialLoser = vec[1];
    }

    size_t i = 0;
    // win or lose
    while (i + 1 < vec.size()) {
        if (vec[i] < vec[i + 1]) {
            winners.push_back(vec[i+1]);
            losers.push_back(std::make_pair(vec[i+1], vec[i]));
        } else {
            winners.push_back(vec[i]);
            losers.push_back(std::make_pair(vec[i], vec[i+1]));
        }
        i += 2;
    }
    fordJohnsonVector(winners);
    // put the smallest num
    winners.insert(winners.begin(), specialLoser);

    //insert losers

    vec = winners;
}

void PmergeMe::insertVector(std::vector<int> &vec, int extra) {

}

void PmergeMe::fordJohnsonDeque(){

    std::cout << "After: ";
    for (int num : _vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
};
