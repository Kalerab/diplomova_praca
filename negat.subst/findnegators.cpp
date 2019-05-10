#include "findnegators.h"

using namespace std;

std::vector< CycledGraph > findnegators(std::vector< CycledGraph > &klasters) {
    vector<CycledGraph> negators;
    for (auto k : (klasters)) {
        std::unordered_set<int> currentVertices = countVertices(k);
        if (specifyCluster(k, currentVertices.size())){
            negators.push_back(k);
        }
    }
    return negators;
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


bool specifyCluster(std::vector<Cycle> &cycles, int uniqueVertices){
    vector<std::tuple<int, int>> edges;
    std::unordered_set<int> uniqueEdges;

    for (int i = 0; i < cycles.size(); ++i) {
        for (int j = 0; j < 5; ++j) {
            int a = cycles[i][j];
            int b = -1;
            if (j != 4) {
                b = cycles[i][j + 1];
            } else {
                b = cycles[i][0];
            }
            int vertex_hash = min(a, b) * 255 + max(a, b);
            if (uniqueEdges.find(vertex_hash) == uniqueEdges.end()) {
                uniqueEdges.insert(vertex_hash);
                auto edge = std::make_tuple(a, b);
                edges.push_back(edge);
            }
        }
    }

    int v = uniqueVertices;
    long e = edges.size();
    long c = cycles.size();

    if (v == 7 && e == 8 && c == 2){
        return true;
    } else {
        return false;
    }
}