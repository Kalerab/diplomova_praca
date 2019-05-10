#include "findpermutation.h"

using namespace std;

void findPermut(Graph &G, vector<vector<int>> &cycles) {
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


void findAllPermut(Graph &G, vector<vector<int>> &cycles) {
    bool used[G.noOfVerticies];
    int currentVert = 0;
    int startVert = 0;
    int length;
    unordered_set<string> usedCycles;

    for (int i = 0; i < cycles.size(); ++i) {
        vector<int> secondCycle;
        Cycle cycle = cycles[i];
        length = 0;

        long sumFirst = 0;
        long productFirst = 1;
        for(int m = 0; m < cycle.size(); ++m){
            sumFirst = sumFirst+cycle[m];
            productFirst = productFirst*(cycle[m]+1);
        }
        string firstCycleString = to_string(productFirst) + "_" + to_string(sumFirst);
        if (usedCycles.count(firstCycleString)>0) break;


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
            long sumSecond = 0;
            long productSecond = 1;
            for(int m = 0; m < cycle.size(); ++m){
                sumSecond = sumSecond+secondCycle[m];
                productSecond = productSecond*(secondCycle[m]+1);
            }
            string secondCycleString = to_string(productSecond) + "_" +  to_string(sumSecond);

//            cout << secondCycleString << endl;
//            cout << firstCycleString << endl;
//            cout << endl;


            usedCycles.insert(secondCycleString);
            usedCycles.insert(firstCycleString);

            G.allPermutationCycles.push_back(cycle);
            G.allPermutationCycles.push_back(secondCycle);
        }
    }
}