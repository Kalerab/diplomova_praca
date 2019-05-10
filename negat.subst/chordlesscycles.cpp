#include "chordlesscycles.h"

using namespace std;

/*
 * Check if two vertices V1 and V2 are adjacent
 * */
bool adjacent(const Vertex &V1, const Vertex &V2) {
    for (int i = 0; i < 3; i++) {
        if (V1.neighbors[i] == V2.number)
            return true;
    }
    for (int i = 0; i < 3; i++) {
        if (V2.neighbors[i] == V1.number)
            return true;
    }
    return false;
}
/*
 * Implementation from http://stackoverflow.com/questions/4022662/find-all-chordless-cycles-in-an-undirected-graph
 */
void chordless_cycles(Graph &G) {
    // list which will be returned with chordless cycles
    vector< Cycle > cycles;
    int halfLength = G.noOfVerticies/2;
//    auto cycles = shared_ptr< vector< Cycle > >(new vector<Cycle>());

    // List of vertices whose all cycles has been already found, so we don't need to check them anymore
    bool removed[G.noOfVerticies];
    for (int i = 0; i < G.noOfVerticies; i++)
        removed[i] = false;

    for (int i = 0; i < G.noOfVerticies; i++) {
        Vertex firstV = G.vertices[i];
        //Iterating pair of neighbors for every vertex
        for (int j = 1; j < 3; j++) {
            for (int k = 0; k < j; k++) {
                if (removed[firstV.neighbors[j]]
                    || removed[firstV.neighbors[k]])
                    continue;
                Cycle currentCycle;
                currentCycle.push_back(i);
                currentCycle.push_back(firstV.neighbors[j]);
                if (adjacent(G.vertices[firstV.neighbors[j]],
                             G.vertices[firstV.neighbors[k]])) {
                    //Cycle of length 3
                    currentCycle.push_back(firstV.neighbors[k]);
                    cycles.push_back(currentCycle);
                    if (currentCycle.size() == 5){
                        G.pentCycles.push_back(currentCycle);
                    }
                    if (currentCycle.size() == halfLength){
                        G.halfCycles.push_back(currentCycle);
                    }
                    continue;
                }

                vector< Cycle > candidates;
                candidates.push_back(currentCycle);

                while (!candidates.empty()) {
                    Cycle line = candidates.back();
                    candidates.pop_back();
                    Vertex currentV = G.vertices[line.back()];

                    for (int x = 0; x < 3; x++) {
                        if (removed[currentV.neighbors[x]])
                            continue;
                        //We have already found all cycles containing vertex x, so now we need to check if cycles contain chord
                        bool haschord = false;
                        for (int q = 1; q < line.size() - 1; q++) {
                            if (adjacent(G.vertices[line[q]],
                                         G.vertices[currentV.neighbors[x]]))
                                haschord = true;
                        }
                        if (haschord)
                            continue;
                        //To prevent returning from second vertex (and 'cycles' like 1-2-1)
                        if (firstV.number == currentV.neighbors[x]) {
                            continue;
                        }
                        if (currentV.neighbors[x] != firstV.neighbors[j]
                            && currentV.neighbors[x] != firstV.neighbors[k]
                            && adjacent(G.vertices[currentV.neighbors[x]],
                                        firstV)) {
                            // We would like to use just cycles containing vertices firstV, firstV.neighbors[j] a firstV.neighbors[k]
                            continue;
                        }

                        if (currentV.neighbors[x] == firstV.neighbors[k]) {
                            //If it's chordless cycle push it to list of suitable cycles
                            Cycle newCycle = line;
                            newCycle.push_back(currentV.neighbors[x]);
                            cycles.push_back(newCycle);
                            if (newCycle.size() == 5){
                                G.pentCycles.push_back(newCycle);
                            }
                            if (newCycle.size() == halfLength){
                                G.halfCycles.push_back(newCycle);
                            }
                            continue;
                        }

                        vector<int> newline = line;
                        //Previous version
                        //if (newline.size() > 4 * log2(G.noOfVerticies + 1)) {

                        //We don't need cycles bigger than n/2
                        if (newline.size() > (G.noOfVerticies / 2 - 1)) {
                            continue;
                        }
                        newline.push_back(currentV.neighbors[x]);
                        candidates.push_back(newline);
                    }
                }
            }
        }

        removed[i] = true;
    }
    G.chordless = cycles;
}