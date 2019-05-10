#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include "common.h"

using namespace std;

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

int positionOfElement(vector<int> vector, int element){
    std::vector<int>::iterator itr = std::find(vector.begin(), vector.end(), element);
    int index = std::distance(vector.begin(), itr);
    return index;
}

std::unordered_set<int> countVertices(vector<vector<int>> &cycles) {
    std::unordered_set<int> uniqueVertices;
    for (int i = 0; i < cycles.size(); ++i) {
        for (int j = 0; j < 5; ++j) {
            int vertice = cycles[i][j];
            if (uniqueVertices.find(vertice) == uniqueVertices.end()) {
                uniqueVertices.insert(vertice);
            }
        }
    }

    return uniqueVertices;
}


