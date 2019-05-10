#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

#include "scanner.h"
#include "chordlesscycles.h"
#include "findpermutation.h"
#include "graphseparator.h"
#include "findnegators.h"


using namespace std;

int main() {
    //first file must contains petersens negator
    string firstFile = "/home/rasto/Documents/all/PERM5_34.ALL";
    string secondFile = "/home/rasto/Documents/all/PERM5_34.ALL";

    //resultPath
    string path = "/home/rasto/Documents/negatsub/result/";

    string allPath = path + "neg-sub.all";
    ofstream allfile(allPath);


    Scanner scanner;

    int numberOfGraphs = 20;
    int current = 1;

    allfile << numberOfGraphs << endl;

    vector<Graph> firstFileGraphs = scanner.scanFile(firstFile);
    vector<Graph> secondFileGraphs = scanner.scanFile(secondFile);

    srand((unsigned) time(0));
    for (int l = 0; l < numberOfGraphs; ++l) {

        int graphFromFirstFile = (rand() % firstFileGraphs.size());
        int graphFromSecondFile = (rand() % secondFileGraphs.size());

        Graph firstGraph = firstFileGraphs[graphFromFirstFile];
        Graph secondGraph = secondFileGraphs[graphFromSecondFile];

        chordless_cycles(firstGraph);
        chordless_cycles(secondGraph);

        findPermut(firstGraph, firstGraph.halfCycles);
        findPermut(secondGraph, secondGraph.halfCycles);

        if (firstGraph.permut) findAllPermut(firstGraph, firstGraph.halfCycles);
        if (secondGraph.permut) findAllPermut(secondGraph, secondGraph.halfCycles);

        if (firstGraph.permut && secondGraph.permut) {

            auto klaster = separate_cycles_into_graphs(firstGraph.pentCycles);
            auto negators = findnegators(*klaster);

            if (!negators.size() > 0) { return 0; }
            int oneNegator = (rand() % negators.size());
//            int oneNegator = 1;

            // Select permutation pairs from both graphs
            int firstPermutationPair = (rand() % (firstGraph.allPermutationCycles.size() / 2));
            int secondPermutationPair = (rand() % (secondGraph.allPermutationCycles.size() / 2));

            // store permutation cycles from both graphs
            vector<int> firstPermCycle = firstGraph.allPermutationCycles[firstPermutationPair * 2];
            vector<int> secondPermCycle = firstGraph.allPermutationCycles[firstPermutationPair * 2 + 1];

            vector<int> secondGraphFirstPermCycle = secondGraph.allPermutationCycles[secondPermutationPair * 2];
            vector<int> secondGraphSecondPermCycle = secondGraph.allPermutationCycles[secondPermutationPair * 2 + 1];


            // select one negator from first graph
            auto n = negators[oneNegator];

            // determine apex and vertices which are in both negator cycles
            int apex;
            vector<int> inBothCycles;
            vector<int> connectionVertices;
            vector<int> firstCycle = n[0];
            vector<int> secondCycle = n[1];

            for (int i = 0; i < 5; ++i) {
                int current = n[0][i];
                if (elementInVector(&n[0], current) && elementInVector(&n[1], current)) {
                    inBothCycles.push_back(current);
                }
            }

            for (int j = 0; j < 5; ++j) {
                if (elementInVector(&inBothCycles, n[0][(j + 4) % 5]) &&
                    elementInVector(&inBothCycles, n[0][(j + 5) % 5]) &&
                    elementInVector(&inBothCycles, n[0][(j + 6) % 5])) {
                    apex = n[0][j];
                    break;
                }
            }

            // take longer cycle (length 6) from negator and select vertices whose edges are going out
            // from negator in ordes as they go in cycle
            // eg. if the negator is made out of 2 cycles
            // 1-2-3-4-5 and 2-3-4-7-8 where 3 is apex and 2 and 4 are his neighbors
            // we have cycle of length 6 > 1-5-4-7-8-2  we want to select vertices 1 5 7 8 in this order

            int firstNeigh;
            int secondNeigh;

            for (int k = 0; k < 5; ++k) {
                if (!elementInVector(&inBothCycles, firstCycle[k])) {
                    connectionVertices.push_back(firstCycle[k]);
                    if (connectionVertices.size() == 2) {
                        if (elementInVector(&inBothCycles, firstCycle[(k + 6) % 5])) {
                            secondNeigh = firstCycle[(k + 6) % 5];
                        } else {
                            secondNeigh = firstCycle[(k + 4) % 5];
                        }
                    } else {
                        if (elementInVector(&inBothCycles, firstCycle[(k + 6) % 5])) {
                            firstNeigh = firstCycle[(k + 6) % 5];
                        } else {
                            firstNeigh = firstCycle[(k + 4) % 5];
                        }
                    }
                }
            }

            for (int l = 0; l < 5; ++l) {
                if (secondCycle[l] == secondNeigh) {
                    if (elementInVector(&inBothCycles, secondCycle[(l + 6) % 5])) {
                        connectionVertices.push_back(secondCycle[(l + 4) % 5]);
                    } else {
                        connectionVertices.push_back(secondCycle[(l + 6) % 5]);
                    }
                    break;
                }
            }
            for (int l = 0; l < 5; ++l) {
                if (secondCycle[l] == firstNeigh) {
                    if (elementInVector(&inBothCycles, secondCycle[(l + 6) % 5])) {
                        connectionVertices.push_back(secondCycle[(l + 4) % 5]);
                    } else {
                        connectionVertices.push_back(secondCycle[(l + 6) % 5]);
                    }
                    break;
                }
            }

            // determine if apex is in first or second permutation cycle and his position in this cycle
            bool apexInFirstPerm;
            int apexPosInPerm;

            if (elementInVector(&firstPermCycle, apex)) {
                apexInFirstPerm = true;
                apexPosInPerm = positionOfElement(&firstPermCycle, apex);
            } else {
                apexInFirstPerm = false;
                apexPosInPerm = positionOfElement(&secondPermCycle, apex);
            }

            // select the one of four vertices from cycle of length 6 which is in same cycle as apex
            int vertexInSameCycle;
            int positionOfVertexInSame;
            for (int i = 0; i < 4; ++i) {
                if (apexInFirstPerm) {
                    if (elementInVector(&firstPermCycle, connectionVertices[i])) {
                        vertexInSameCycle = connectionVertices[i];
                        positionOfVertexInSame = i;
                    }
                } else {
                    if (elementInVector(&secondPermCycle, connectionVertices[i])) {
                        vertexInSameCycle = connectionVertices[i];
                        positionOfVertexInSame = i;
                    }
                }
            }
            vector<int> firstGraphFirstPath;
            vector<int> firstGraphSecondPath;
            int firstGraphNonCycleVertex;

            for (int i = 0; i < 3; ++i) {
                int apexNeigh = firstGraph.vertices[apex].neighbors[i];
                if (!(elementInVector(&n[0], apexNeigh) || elementInVector(&n[1], apexNeigh))) {
                    firstGraphFirstPath.push_back(apexNeigh);
                }
            }

            for (int i = 0; i < 3; ++i) {
                int currentNeigh = firstGraph.vertices[vertexInSameCycle].neighbors[i];
                if (!(elementInVector(&n[0], currentNeigh) || elementInVector(&n[1], currentNeigh))) {
                    firstGraphFirstPath.push_back(currentNeigh);
                }
            }

            for (int i = 0; i < 3; ++i) {
                int currentNeigh = firstGraph.vertices[connectionVertices[(positionOfVertexInSame + 3) %
                                                                          4]].neighbors[i];
                if (!(elementInVector(&n[0], currentNeigh) || elementInVector(&n[1], currentNeigh))) {
                    firstGraphSecondPath.push_back(currentNeigh);
                }
            }
            for (int i = 0; i < 3; ++i) {
                int currentNeigh = firstGraph.vertices[connectionVertices[(positionOfVertexInSame + 1) %
                                                                          4]].neighbors[i];
                if (!(elementInVector(&n[0], currentNeigh) || elementInVector(&n[1], currentNeigh))) {
                    firstGraphSecondPath.push_back(currentNeigh);
                }
            }
            for (int i = 0; i < 3; ++i) {
                int currentNeigh = firstGraph.vertices[connectionVertices[(positionOfVertexInSame + 2) %
                                                                          4]].neighbors[i];
                if (!(elementInVector(&n[0], currentNeigh) || elementInVector(&n[1], currentNeigh))) {
                    firstGraphNonCycleVertex = currentNeigh;
                }
            }

            // new vertices number in result graph
            int index = 0;
            vector<int> newVerticesFirstGraph;
            for (int m = 0; m < firstGraph.noOfVerticies; ++m) {
                if (!(elementInVector(&n[0], m) || elementInVector(&n[1], m))) {
                    newVerticesFirstGraph.push_back(index);
                    index++;
                } else {
                    newVerticesFirstGraph.push_back(-1);
                }
            }



            // select one vertex from second graph
            int firstVertexSecondGraph = (rand() % (secondGraph.noOfVerticies));

            vector<int> removeFromSecond;
            bool vertexInFirstPermCycle;
            if (elementInVector(&secondGraphFirstPermCycle, firstVertexSecondGraph)) {
                vertexInFirstPermCycle = true;
            } else {
                vertexInFirstPermCycle = false;
            }

            vector<int> secondGraphFirstPath;
            vector<int> secondGraphSecondPath;
            int secondGraphNonCycleVertex;
            int secondVertex;

            for (int i = 0; i < 3; ++i) {
                int currentNeigh = secondGraph.vertices[firstVertexSecondGraph].neighbors[i];
                if (vertexInFirstPermCycle) {
                    if (elementInVector(&secondGraphFirstPermCycle, currentNeigh)) {
                        secondGraphSecondPath.push_back(currentNeigh);
                    } else {
                        secondVertex = currentNeigh;
                    }
                } else {
                    if (elementInVector(&secondGraphSecondPermCycle, currentNeigh)) {
                        secondGraphSecondPath.push_back(currentNeigh);
                    } else {
                        secondVertex = currentNeigh;
                    }
                }
            }

            int thirdVertex;
            vector<int> secondVertexNeighbors;
            for (int i = 0; i < 3; ++i) {
                int currentNeigh = secondGraph.vertices[secondVertex].neighbors[i];
                if (currentNeigh != firstVertexSecondGraph) {
                    secondVertexNeighbors.push_back(currentNeigh);
                }
            }

            int thirdVertexInVector = (rand() % 2);
            int longPath = (thirdVertexInVector + 1) % 2;

            thirdVertex = secondVertexNeighbors[thirdVertexInVector];
            secondGraphFirstPath.push_back(secondVertexNeighbors[longPath]);

            for (int i = 0; i < 3; ++i) {
                int currentNeigh = secondGraph.vertices[thirdVertex].neighbors[i];
                if (currentNeigh != secondVertex) {
                    if (vertexInFirstPermCycle) {
                        if (elementInVector(&secondGraphSecondPermCycle, currentNeigh)) {
                            secondGraphFirstPath.push_back(currentNeigh);
                        } else {
                            secondGraphNonCycleVertex = currentNeigh;
                        }
                    } else {
                        if (elementInVector(&secondGraphFirstPermCycle, currentNeigh)) {
                            secondGraphFirstPath.push_back(currentNeigh);
                        } else {
                            secondGraphNonCycleVertex = currentNeigh;
                        }
                    }
                }
            }

            removeFromSecond.push_back(firstVertexSecondGraph);
            removeFromSecond.push_back(secondVertex);
            removeFromSecond.push_back(thirdVertex);

            vector<int> newVerticesSecondGraph;

            int secondIndex = firstGraph.noOfVerticies - 7;

            for (int i = 0; i < secondGraph.noOfVerticies; ++i) {
                if (!elementInVector(&removeFromSecond, i)) {
                    newVerticesSecondGraph.push_back(secondIndex);
                    secondIndex++;
                } else {
                    newVerticesSecondGraph.push_back(-1);
                }
            }

            int numberOfVertices = firstGraph.noOfVerticies + secondGraph.noOfVerticies - 10;

            Graph finalGraph;
            finalGraph.graphNumber = 1;
            finalGraph.noOfVerticies = numberOfVertices;

            for (int i = 0; i < firstGraph.noOfVerticies; ++i) {
                if (newVerticesFirstGraph[i] != -1) {
                    Vertex vertex;
                    vertex.number = newVerticesFirstGraph[i];
                    vector<int> neigh;
                    for (int j = 0; j < 3; ++j) {
                        int currentNeig = firstGraph.vertices[i].neighbors[j];
                        if (newVerticesFirstGraph[currentNeig] != -1) {
                            neigh.push_back(newVerticesFirstGraph[currentNeig]);
                        }
                    }
                    vertex.neighbors = neigh;
                    finalGraph.vertices.push_back(vertex);
                }
            }

            for (int i = 0; i < secondGraph.noOfVerticies; ++i) {
                if (newVerticesSecondGraph[i] != -1) {
                    Vertex vertex;
                    vertex.number = newVerticesSecondGraph[i];
                    vector<int> neigh;
                    for (int j = 0; j < 3; ++j) {
                        int currentNeig = secondGraph.vertices[i].neighbors[j];
                        if (newVerticesSecondGraph[currentNeig] != -1) {
                            neigh.push_back(newVerticesSecondGraph[currentNeig]);
                        }
                    }
                    vertex.neighbors = neigh;
                    finalGraph.vertices.push_back(vertex);
                }
            }

            int firstGraphFirstPathSwitch = (0);
            int firstGraphSecondPathSwitch = (rand() % 2);

            finalGraph.vertices[newVerticesFirstGraph[firstGraphFirstPath[firstGraphFirstPathSwitch]]].neighbors.push_back(
                    newVerticesSecondGraph[secondGraphFirstPath[0]]);
            finalGraph.vertices[newVerticesSecondGraph[secondGraphFirstPath[0]]].neighbors.push_back(
                    newVerticesFirstGraph[firstGraphFirstPath[firstGraphFirstPathSwitch]]);

            finalGraph.vertices[newVerticesFirstGraph[firstGraphFirstPath[(firstGraphFirstPathSwitch + 1) %
                                                                          2]]].neighbors.push_back(
                    newVerticesSecondGraph[secondGraphFirstPath[1]]);
            finalGraph.vertices[newVerticesSecondGraph[secondGraphFirstPath[1]]].neighbors.push_back(
                    newVerticesFirstGraph[firstGraphFirstPath[(firstGraphFirstPathSwitch + 1) % 2]]);

            finalGraph.vertices[newVerticesFirstGraph[firstGraphSecondPath[firstGraphSecondPathSwitch]]].neighbors.push_back(
                    newVerticesSecondGraph[secondGraphSecondPath[0]]);
            finalGraph.vertices[newVerticesSecondGraph[secondGraphSecondPath[0]]].neighbors.push_back(
                    newVerticesFirstGraph[firstGraphSecondPath[firstGraphSecondPathSwitch]]);

            finalGraph.vertices[newVerticesFirstGraph[firstGraphSecondPath[(firstGraphSecondPathSwitch + 1) %
                                                                           2]]].neighbors.push_back(
                    newVerticesSecondGraph[secondGraphSecondPath[1]]);
            finalGraph.vertices[newVerticesSecondGraph[secondGraphSecondPath[1]]].neighbors.push_back(
                    newVerticesFirstGraph[firstGraphSecondPath[(firstGraphSecondPathSwitch + 1) % 2]]);

            finalGraph.vertices[newVerticesFirstGraph[firstGraphNonCycleVertex]].neighbors.push_back(
                    newVerticesSecondGraph[secondGraphNonCycleVertex]);
            finalGraph.vertices[newVerticesSecondGraph[secondGraphNonCycleVertex]].neighbors.push_back(
                    newVerticesFirstGraph[firstGraphNonCycleVertex]);

            string config = std::to_string(graphFromFirstFile) + "_" + std::to_string(graphFromSecondFile) + "_" +
                            std::to_string(oneNegator) + "_" + std::to_string(firstPermutationPair) +
                            "_" + std::to_string(secondPermutationPair) + "_" + std::to_string(firstVertexSecondGraph) +
                            "_" + std::to_string(thirdVertexInVector) + std::to_string(firstGraphFirstPathSwitch) +
                            std::to_string(firstGraphSecondPathSwitch);



            string resultPath = path +  config + "." + std::to_string(finalGraph.noOfVerticies);
            ofstream outfile(resultPath);


            finalGraph.comment = "{" + config + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{Permutation graph generated using negator subtitution}\n";
            finalGraph.comment = finalGraph.comment + "{" + "First graph is from file :" + firstFile + "}" + "\n";
            finalGraph.comment =
                    finalGraph.comment + "{" + "Number of graph is :" + std::to_string(graphFromFirstFile) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Second graph is from file :" + secondFile + "}" + "\n";
            finalGraph.comment =
                    finalGraph.comment + "{" + "Number of graph is :" + std::to_string(graphFromSecondFile) + "}" +
                    "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Negator is from first graph, number of negator is :" +
                                 std::to_string(oneNegator) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Number of permutation pair from first graph is :" +
                                 std::to_string(firstPermutationPair) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Number of permutation pair from second graph is :" +
                                 std::to_string(secondPermutationPair) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Removed vertices from second graph are: " +
                                 std::to_string(firstVertexSecondGraph) + "-" + std::to_string(secondVertex) + "-" +
                                 std::to_string(thirdVertex) + "}" + "\n";

            outfile << 1 << endl << 1 << endl;
            outfile << finalGraph.comment;
            outfile << finalGraph.noOfVerticies << endl;
            for (int i = 0; i < finalGraph.noOfVerticies; ++i) {
                for (int j = 0; j < finalGraph.vertices[i].neighbors.size(); ++j) {
                    outfile << finalGraph.vertices[i].neighbors[j] << " ";
                }
                outfile << endl;
            }

            allfile << current << endl;
            allfile << finalGraph.noOfVerticies << endl;
            for (int i = 0; i < finalGraph.noOfVerticies; ++i) {
                for (int j = 0; j < finalGraph.vertices[i].neighbors.size(); ++j) {
                    allfile << finalGraph.vertices[i].neighbors[j] << " ";
                }
                allfile << endl;
            }

            current++;

        }
    }

}
