#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe(char **av):_cnt(0){
    parseInput(av);
};

PmergeMe::~PmergeMe(){};

void PmergeMe::run(){
    std::cout << "Before: ";
    for (size_t i = 0; i < this->_vec.size(); i++) {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;

    clock_t start = clock();
    fordJohnsonVector(this->_vec);
    clock_t end = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < this->_vec.size(); i++) {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;
    
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << duration*1000000 << "us" << std::endl;
    std::cout << "Count : " << this->_cnt << std::endl;


    start = clock();
    fordJohnsonDeque(this->_deq);
    end = clock();

     duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << _vec.size() << " elements with std::deque : " << duration*1000000 << "us" << std::endl;
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


// vector
void PmergeMe::fordJohnsonVector(std::vector<int> &vec){
    int n = vec.size();

    if (n <= 1){
        return;
    }
    // odd
    bool hasExtra = false;
    int extra;
    if (n%2 != 0){
        extra = vec.back();
        vec.pop_back();
        hasExtra = true;
    }

    std::vector<int> winners;
    std::vector<std::pair<int, int> > pairs;

    // win or lose
    for (size_t i = 0; i < vec.size(); i += 2) {
        this->_cnt++;
        if (vec[i] < vec[i + 1]) {
            winners.push_back(vec[i+1]);
            pairs.push_back(std::make_pair(vec[i+1], vec[i]));
        } else {
            winners.push_back(vec[i]);
            pairs.push_back(std::make_pair(vec[i], vec[i+1]));
        }
    }

    fordJohnsonVector(winners);

    // put the smallest num
    int firstWinner = winners[0];
    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first == firstWinner) {
            winners.insert(winners.begin(), pairs[i].second);
            pairs.erase(pairs.begin() + i);
            break;
        }
    }

    //insert pairs
    std::vector<int> insertionOrder = buildInsertionOrderVector(pairs.size());
    for (size_t i = 0; i < insertionOrder.size(); i++){
        int idx = insertionOrder[i];
        if (idx >= (int)pairs.size()){
            continue;
        }
        int tgWinner = pairs[idx].first;
        int val = pairs[idx].second;

        std::vector<int>::iterator it = std::find(winners.begin(), winners.end(), tgWinner);
        int upTo = std::distance(winners.begin(), it);

        insertAtBinarySearchVector(winners, val, upTo);
    }

    if (hasExtra) {
        insertAtBinarySearchVector(winners, extra, winners.size());
    }
    vec = winners;
}

int PmergeMe::binarySearchInsertPositionVector(const std::vector<int>& winners, int val, int upTo) {
    int left = 0;
    int right = upTo;

    while (left < right) {
        this->_cnt++;
        int mid = left + (right - left) / 2;

        if (winners[mid] < val) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

void PmergeMe::insertAtBinarySearchVector(std::vector<int>& winners, int val, int upTo) {
    int position = binarySearchInsertPositionVector(winners, val, upTo);
    winners.insert(winners.begin() + position, val);
}

std::vector<int> PmergeMe::buildInsertionOrderVector(int pairsSize) {
    std::vector<int> insertionOrder;
    std::vector<int> jacob = buildJacobsthalVector(pairsSize);

    int prev = 1;
    insertionOrder.push_back(0); 

    for (size_t k = 2; k < jacob.size(); ++k) {
        int j = jacob[k];
        if (j >= pairsSize) {
            break;
        }
        insertionOrder.push_back(j);
        for (int i = j - 1; i > prev; --i) {
            insertionOrder.push_back(i);
        }
        prev = j;
    }

    // leftovers
    for (int i = pairsSize - 1; i > prev; --i) {
        insertionOrder.push_back(i);
    }

    return insertionOrder;
}

std::vector<int> PmergeMe::buildJacobsthalVector(int max)
{
    std::vector<int> jacob;

    jacob.push_back(0);
    jacob.push_back(1);

    while (true) {
        int next = jacob[jacob.size() - 1]
                 + 2 * jacob[jacob.size() - 2];
        if (next > max)
            break;
        jacob.push_back(next);
    }
    return jacob;
}

// deque
void PmergeMe::fordJohnsonDeque(std::deque<int> &vec){
    int n = vec.size();

    if (n <= 1){
        return;
    }
    // odd
    bool hasExtra = false;
    int extra;
    if (n%2 != 0){
        extra = vec.back();
        vec.pop_back();
        hasExtra = true;
    }

    std::deque<int> winners;
    std::deque<std::pair<int, int> > pairs;

    // win or lose
    for (size_t i = 0; i < vec.size(); i += 2) {
        if (vec[i] < vec[i + 1]) {
            winners.push_back(vec[i+1]);
            pairs.push_back(std::make_pair(vec[i+1], vec[i]));
        } else {
            winners.push_back(vec[i]);
            pairs.push_back(std::make_pair(vec[i], vec[i+1]));
        }
    }

    fordJohnsonDeque(winners);

    // put the smallest num
    int firstWinner = winners[0];
    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first == firstWinner) {
            winners.insert(winners.begin(), pairs[i].second);
            pairs.erase(pairs.begin() + i);
            break;
        }
    }

    //insert pairs
    std::deque<int> insertionOrder = buildInsertionOrderDeque(pairs.size());
    for (size_t i = 0; i < insertionOrder.size(); i++){
        int idx = insertionOrder[i];
        if (idx >= (int)pairs.size()){
            continue;
        }
        int tgWinner = pairs[idx].first;
        int val = pairs[idx].second;

        std::deque<int>::iterator it = std::find(winners.begin(), winners.end(), tgWinner);
        int upTo = std::distance(winners.begin(), it);

        insertAtBinarySearchDeque(winners, val, upTo);
    }

    if (hasExtra) {
        insertAtBinarySearchDeque(winners, extra, winners.size());
    }
    vec = winners;
}

int PmergeMe::binarySearchInsertPositionDeque(const std::deque<int>& winners, int val, int upTo) {
    int left = 0;
    int right = upTo;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (winners[mid] < val) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

void PmergeMe::insertAtBinarySearchDeque(std::deque<int>& winners, int val, int upTo) {
    int position = binarySearchInsertPositionDeque(winners, val, upTo);
    winners.insert(winners.begin() + position, val);
}

std::deque<int> PmergeMe::buildJacobsthalDeque(int max)
{
    std::deque<int> jacob;

    jacob.push_back(0);
    jacob.push_back(1);

    while (true) {
        int next = jacob[jacob.size() - 1]
                 + 2 * jacob[jacob.size() - 2];
        if (next > max)
            break;
        jacob.push_back(next);
    }
    return jacob;
}

std::deque<int> PmergeMe::buildInsertionOrderDeque(int pairsSize) {
    std::deque<int> insertionOrder;

    std::deque<int> jacob = buildJacobsthalDeque(pairsSize);

    int prev = 1;
    insertionOrder.push_back(0); 

    for (size_t k = 2; k < jacob.size(); ++k) {
        int j = jacob[k];
        if (j >= pairsSize) {
            break;
        }

        insertionOrder.push_back(j);
        for (int i = j - 1; i > prev; --i) {
            insertionOrder.push_back(i);
        }
        prev = j;
    }

    for (int i = pairsSize - 1; i > prev; --i) {
        insertionOrder.push_back(i);
    }

    return insertionOrder;
}
