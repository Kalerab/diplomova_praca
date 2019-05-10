#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include "common.h"

using namespace std;

int positionOfElement(vector<int> *vector, int element){
    std::vector<int>::iterator itr = std::find(vector->begin(), vector->end(), element);
    int index = std::distance(vector->begin(), itr);
    return index;
}

bool elementInVector(vector<int> *vector, int element){
    if (vector->empty()) {
        return false;
    } else {
        if (find(vector->begin(), vector->end(), element) != vector->end())
            return true;
        else
            return false;
    }
}
