#include "specifyclusters.h"

#include <vector>

using namespace std;

int specifyClusterType(std::vector<Cycle> &cycles, int uniqueVertices, int *count, int numberOfVert){
    vector<std::tuple<int, int>> edges;
    std::unordered_set<int> uniqueEdges;

    bool isoch = false;
    int vertDeg[numberOfVert];
    int vert = -1;

    if (uniqueVertices == 8 && cycles.size() == 4){
        isoch = true;
        for (int i = 0; i < numberOfVert; ++i) {
            vertDeg[i] = 0;
        }
    }

    for (int i = 0; i < cycles.size(); ++i) {
        for (int j = 0; j < 5; ++j) {
            int a = cycles[i][j];
            int b = cycles[i][(j+1)%5];
            int vertex_hash = min(a, b) * 193 + max(a, b) * 197;
            if (uniqueEdges.find(vertex_hash) == uniqueEdges.end()) {
                uniqueEdges.insert(vertex_hash);
                auto edge = std::make_tuple(a, b);
                edges.push_back(edge);

                if (isoch){
                    vertDeg[a]++;
                    vertDeg[b]++;
                    if (vertDeg[a] == 3){
                        vert = a;
                    }
                }
            }
        }
    }

    int v = uniqueVertices;
    long e = edges.size();
    long c = cycles.size();

    if ( v == 5 && e == 5 && c == 1){
        count[0]++;
        return 0;
    }

    if ( v == 8 && e == 9 && c == 2){
        count[1]++;
        return 1;
    }

    if ( v == 7 && e == 8 && c == 2){
        count[2]++;
        return 2;
    }

    if ( v == 10 && e == 12 && c == 3){
        bool triplepent = false;
        for (int i = 0; i < 5; ++i) {
            int currentVert = cycles[0][i];
            if (elementInVector(&cycles[1], currentVert) && elementInVector(&cycles[2], currentVert)){
                triplepent = true;
            }
        }
        if (triplepent){
            count[3]++;
            return 3;
        } else {
            count[4]++;
            return 4;
        }
    }

    if (v == 9 && e == 11 && c == 3){
        count[5]++;
        return 5;
    }

    if (v == 8 && e == 10 && c == 4) {
        int cubicNeighbors = 0;
        for (int i = 0; i < edges.size(); ++i) {
            int a = std::get<0>(edges[i]);
            int b = std::get<1>(edges[i]);

            if (a == vert){
                if (vertDeg[b] == 3){
                    cubicNeighbors++;
                }
            } else if (b == vert) {
                if (vertDeg[a] == 3){
                    cubicNeighbors++;
                }
            }
        }

        if (cubicNeighbors == 1) {
            count[6]++;
            return 6;
        }
    }

    if (v == 10 && e == 13 && c == 5){
        count[7]++;
        return 7;
    }

    if (v == 10 && e == 13 && c == 4){
        count[8]++;
        return 8;
    }

    count[9]++;
    return 9;

    }
