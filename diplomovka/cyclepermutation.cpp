#include "cyclepermutation.h"
#include "common.h"
#include <vector>

using namespace std;

void cyclePermutation(Graph &G, ofstream &outfile){
    bool used[G.noOfVerticies/2] = {false};
    vector<vector<int>> result;
    vector current;
    int currentCycle = 0;
    int currentVertex = 0;
    vector firstCycle = G.permutationCycles[0];
    vector secondCycle = G.permutationCycles[1];
    for (int i=0; i < G.noOfVerticies/2; i++){
        if (elementInVector(result[currentCycle], currentVertex)){
            currentCycle++;
            for (int j = 0; j < G.noOfVerticies/2; ++j) {
                if (!used[j]){
                    currentVertex = j;
                    break;
                }
            }
        }

    }
}