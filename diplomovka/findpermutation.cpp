#include "findpermutation.h"
#include <vector>

using namespace std;

void findPermut2(Graph &G, vector<vector<int>> &cycles) {
    bool used[G.noOfVerticies];
    int currentVert = 0;
    int startVert = 0;
    int length;

    for (int i = 0; i < cycles.size(); ++i) {
        vector<int> secondCycle;
        Cycle cycle = cycles[i];
        length = 0;

        for (int j = 0; j < G.noOfVerticies; ++j) {
            used[j] = false;
        }

        for (int k = 0; k < cycle.size(); ++k) {
            used[cycle[k]] = true;
        }

        for (int l = 0; l < G.noOfVerticies; ++l) {
            if (!used[l]) {
                currentVert = l;
                startVert = l;
                break;
            }
        }

        while (true) {
            for (int j = 0; j < 3; ++j) {
                int neighbor = G.vertices[currentVert].neighbors[j];
                if (!used[neighbor]) {
                    secondCycle.push_back(currentVert);
                    used[currentVert] = true;
                    currentVert = neighbor;
                    length++;
                    if (length == G.noOfVerticies / 2 - 1) {
                        for (int k = 0; k < 3; ++k) {
                            if (G.vertices[currentVert].neighbors[k] == startVert) {
                                length++;
                                secondCycle.push_back(currentVert);
                                goto goOut;
                            }
                        }
                    }
                    if (length == G.noOfVerticies / 2) goto goOut;
                    break;
                }
                if (j == 2) goto goOut;
            }
        }

        goOut:;
        if (length == G.noOfVerticies / 2) {
            G.permutationCycles.push_back(cycle);
            G.permutationCycles.push_back(secondCycle);
            G.permut = true;
            goto finish;
        }

    }

    finish:;
}