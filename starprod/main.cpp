#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

#include "scanner.h"
#include "chordlesscycles.h"
#include "findpermutation.h"


using namespace std;

int main() {

    // all files will be combined and files will be created from them
    vector<string> allFiles;
    allFiles.push_back("/home/rasto/Documents/snarks/5-SUVISLE/PERM5V01.42");
    allFiles.push_back("/home/rasto/Documents/snarks/5-SUVISLE/PERM5V01.50");
    allFiles.push_back("/home/rasto/Documents/snarks/5-SUVISLE/PERM5V02.42");
    allFiles.push_back("/home/rasto/Documents/snarks/5-SUVISLE/PERM5VA1.42");
    allFiles.push_back("/home/rasto/Documents/snarks/5-SUVISLE/PERM5VA2.42");

//    string firstFile = "/home/kalerab/Documents/Snarks - all/PERM5_34.ALL";
//    string secondFile = "/home/kalerab/Documents/Snarks - all/PS.10";


    // set result path
    string path = "/home/rasto/Documents/starprod/";



    Scanner scanner;
    int numberOfGraphs = 20;
    int current = 1;



    //result file name
    string allPath = path + "star-prod.all";

    ofstream allfile(allPath);
    allfile << numberOfGraphs << endl;

    srand((unsigned) time(0));
    for (int l = 0; l < numberOfGraphs; ++l) {
        int fG = (rand() % (allFiles.size()));
        int sG = (rand() % (allFiles.size()));

//        vector<Graph> firstFileGraphs = scanner.scanFile(firstFile);
//        vector<Graph> secondFileGraphs = scanner.scanFile(secondFile);
        vector<Graph> firstFileGraphs = scanner.scanFile(allFiles[fG]);
        vector<Graph> secondFileGraphs = scanner.scanFile(allFiles[sG]);

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

        if (firstGraph.permut && secondGraph.permut && firstGraph.pentCycles.size() > 0 && secondGraph.pentCycles.size() > 0) {

            int randPentFirst = (rand() % (firstGraph.pentCycles.size()));
            int randPentSecond = (rand() % (secondGraph.pentCycles.size()));


            // Select permutation pairs from both graphs
            int firstPermutationPair = (rand() % (firstGraph.allPermutationCycles.size() / 2));
            int secondPermutationPair = (rand() % (secondGraph.allPermutationCycles.size() / 2));

            // store permutation cycles from both graphs
            vector<int> firstPermCycle = firstGraph.allPermutationCycles[firstPermutationPair * 2];
            vector<int> secondPermCycle = firstGraph.allPermutationCycles[firstPermutationPair * 2 + 1];

            vector<int> secondGraphFirstPermCycle = secondGraph.allPermutationCycles[secondPermutationPair * 2];
            vector<int> secondGraphSecondPermCycle = secondGraph.allPermutationCycles[secondPermutationPair * 2 + 1];

            Cycle pentagonFirstGraph = firstGraph.pentCycles[randPentFirst];
            Cycle pentagonSecondGraph = secondGraph.pentCycles[randPentSecond];


            vector<int> firstGraphFirstPath;
            vector<int> firstGraphOneCycle;
            vector<int> firstGraphSecondPath;
            vector<int> firstGraphSecondCycle;
            int firstGraphSpoke;
            int middleVertexFirstGraph;


            for (int k = 0; k < 5; ++k) {
                int neighInSame = 0;
                int currentVert = pentagonFirstGraph[k];
                for (int i = 0; i < 3; ++i) {
                    int neigh = firstGraph.vertices[currentVert].neighbors[i];
                    if (elementInVector(&pentagonFirstGraph, neigh)
                        && elementInVector(&firstPermCycle, neigh) == elementInVector(&firstPermCycle, currentVert)){
                        neighInSame++;
                    }
                }
                if (neighInSame==2){
                    middleVertexFirstGraph = currentVert;
                }
            }

            for (int k = 0; k < 3; ++k) {
                int neigh = firstGraph.vertices[middleVertexFirstGraph].neighbors[k];
                if (!elementInVector(&pentagonFirstGraph, neigh)){
                    firstGraphSpoke = neigh;
                }
            }

            for (int k = 0; k < 5; ++k) {
                int currentVert = pentagonFirstGraph[k];
                if (elementInVector(&firstGraph.vertices[middleVertexFirstGraph].neighbors, currentVert)){
                    firstGraphOneCycle.push_back(currentVert);
                } else {
                    if (currentVert != middleVertexFirstGraph){
                        firstGraphSecondCycle.push_back(currentVert);
                    }
                }
            }

            for (int k = 0; k < 2; ++k) {
                int currentVert = firstGraphOneCycle[k];
                for (int i = 0; i < 3; ++i) {
                    int neigh = firstGraph.vertices[currentVert].neighbors[i];
                    if (!elementInVector(&pentagonFirstGraph, neigh)){
                        firstGraphFirstPath.push_back(neigh);
                    }
                }
            }

            for (int k = 0; k < 2; ++k) {
                int tmpVert = firstGraphOneCycle[k];
                int currentVert;
                if (elementInVector(&firstGraph.vertices[tmpVert].neighbors, firstGraphSecondCycle[0])){
                    currentVert = firstGraphSecondCycle[0];
                } else {
                    currentVert = firstGraphSecondCycle[1];
                }

                for (int i = 0; i < 3; ++i) {
                    int neigh = firstGraph.vertices[currentVert].neighbors[i];
                    if (!elementInVector(&pentagonFirstGraph, neigh)){
                        firstGraphSecondPath.push_back(neigh);
                    }
                }
            }


            vector<int> secondGraphFirstPath;
            vector<int> secondGraphOneCycle;
            vector<int> secondGraphSecondPath;
            vector<int> secondGraphSecondCycle;
            int secondGraphSpoke;
            int middleVertexSecondGraph;


            for (int k = 0; k < 5; ++k) {
                int neighInSame = 0;
                int currentVert = pentagonSecondGraph[k];
                for (int i = 0; i < 3; ++i) {
                    int neigh = secondGraph.vertices[currentVert].neighbors[i];
                    if (elementInVector(&pentagonSecondGraph, neigh)
                        && elementInVector(&secondGraphFirstPermCycle, neigh) == elementInVector(&secondGraphFirstPermCycle, currentVert)){
                        neighInSame++;
                    }
                }
                if (neighInSame==2){
                    middleVertexSecondGraph = currentVert;
                }
            }

            for (int k = 0; k < 3; ++k) {
                int neigh = secondGraph.vertices[middleVertexSecondGraph].neighbors[k];
                if (!elementInVector(&pentagonSecondGraph, neigh)){
                    secondGraphSpoke = neigh;
                }
            }

            for (int k = 0; k < 5; ++k) {
                int currentVert = pentagonSecondGraph[k];
                if (elementInVector(&secondGraph.vertices[middleVertexSecondGraph].neighbors, currentVert)){
                    secondGraphSecondCycle.push_back(currentVert);
                } else {
                    if (currentVert != middleVertexSecondGraph){
                        secondGraphOneCycle.push_back(currentVert);
                    }
                }
            }

            for (int k = 0; k < 2; ++k) {
                int currentVert = secondGraphOneCycle[k];
                for (int i = 0; i < 3; ++i) {
                    int neigh = secondGraph.vertices[currentVert].neighbors[i];
                    if (!elementInVector(&pentagonSecondGraph, neigh)){
                        secondGraphFirstPath.push_back(neigh);
                    }
                }
            }

            for (int k = 0; k < 2; ++k) {
                int tmpVert = secondGraphOneCycle[k];
                int currentVert;
                if (elementInVector(&secondGraph.vertices[tmpVert].neighbors, secondGraphSecondCycle[0])){
                    currentVert = secondGraphSecondCycle[0];
                } else {
                    currentVert = secondGraphSecondCycle[1];
                }


                for (int i = 0; i < 3; ++i) {
                    int neigh = secondGraph.vertices[currentVert].neighbors[i];
                    if (!elementInVector(&pentagonSecondGraph, neigh)){
                        secondGraphSecondPath.push_back(neigh);
                    }
                }
            }


            // new vertices number in result graph
            int index = 0;
            vector<int> newVerticesFirstGraph;
            for (int m = 0; m < firstGraph.noOfVerticies; ++m) {
                if (!elementInVector(&pentagonFirstGraph,m)){
                    newVerticesFirstGraph.push_back(index);
                    index++;
                } else {
                    newVerticesFirstGraph.push_back(-1);
                }
            }


            vector<int> newVerticesSecondGraph;
            int secondIndex = firstGraph.noOfVerticies - 5;

            for (int i = 0; i < secondGraph.noOfVerticies; ++i) {
                if (!elementInVector(&pentagonSecondGraph, i)) {
                    newVerticesSecondGraph.push_back(secondIndex);
                    secondIndex++;
                } else {
                    newVerticesSecondGraph.push_back(-1);
                }
            }

            int numberOfVertices = firstGraph.noOfVerticies + secondGraph.noOfVerticies - 10;

            Graph finalGraph;
            finalGraph.graphNumber = current;
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


            int firstGraphSecondPathSwitch = (rand() % 2);
            int firstGraphFirstPathSwitch = (firstGraphSecondPathSwitch+1)%2;
//        int secondGraphSecondPathSwitch = (rand()%2);

            int g1f0 = newVerticesFirstGraph[firstGraphFirstPath[firstGraphFirstPathSwitch]];
            int g1f1 = newVerticesFirstGraph[firstGraphFirstPath[(firstGraphFirstPathSwitch+1)%2]];

            int g1s0 = newVerticesFirstGraph[firstGraphSecondPath[firstGraphSecondPathSwitch]];
            int g1s1 = newVerticesFirstGraph[firstGraphSecondPath[(firstGraphSecondPathSwitch+1)%2]];

            int g1spoke = newVerticesFirstGraph[firstGraphSpoke];



            int g2f0 = newVerticesSecondGraph[secondGraphFirstPath[0]];
            int g2f1 = newVerticesSecondGraph[secondGraphFirstPath[1]];

            int g2s0 = newVerticesSecondGraph[secondGraphSecondPath[0]];
            int g2s1 = newVerticesSecondGraph[secondGraphSecondPath[1]];

            int g2spoke = newVerticesSecondGraph[secondGraphSpoke];

            finalGraph.vertices[g1f0].neighbors.push_back(g2f0);
            finalGraph.vertices[g2f0].neighbors.push_back(g1f0);

            finalGraph.vertices[g1f1].neighbors.push_back(g2f1);
            finalGraph.vertices[g2f1].neighbors.push_back(g1f1);

            finalGraph.vertices[g1s0].neighbors.push_back(g2s0);
            finalGraph.vertices[g2s0].neighbors.push_back(g1s0);

            finalGraph.vertices[g1s1].neighbors.push_back(g2s1);
            finalGraph.vertices[g2s1].neighbors.push_back(g1s1);

            finalGraph.vertices[g1spoke].neighbors.push_back(g2spoke);
            finalGraph.vertices[g2spoke].neighbors.push_back(g1spoke);


            string config = std::to_string(graphFromFirstFile) + "_" + std::to_string(graphFromSecondFile) + "_" +
                            std::to_string(randPentFirst) + "_" + std::to_string(firstPermutationPair) +
                            "_" + std::to_string(randPentSecond) + "_" + std::to_string(secondPermutationPair) + " "
                            + std::to_string(firstGraphFirstPathSwitch) + std::to_string(firstGraphSecondPathSwitch);
//            cout << config << endl;

            string resultPath = path + "/single/" + "star-" + config + "." + std::to_string(finalGraph.noOfVerticies);
//            cout << resultPath << endl;


            string origComment = finalGraph.comment;

            finalGraph.comment = "{" + config + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{Permutation graph generated using negator subtitution}\n";
            finalGraph.comment = finalGraph.comment + "{" + "First graph is from file :" + allFiles[fG] + "}" + "\n";
            finalGraph.comment =
                    finalGraph.comment + "{" + "Number of graph is :" + std::to_string(graphFromFirstFile) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Second graph is from file :" + std::to_string(allFiles[sG]) + "}" + "\n";
            finalGraph.comment =
                    finalGraph.comment + "{" + "Number of graph is :" + std::to_string(graphFromSecondFile) + "}" +
                    "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Number of pentagon from first graph is :" +
                                 std::to_string(randPentFirst) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Number of pentagon from second graph is :" +
                                 std::to_string(randPentSecond) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Number of permutation pair from first graph is :" +
                                 std::to_string(firstPermutationPair) + "}" + "\n";
            finalGraph.comment = finalGraph.comment + "{" + "Number of permutation pair from second graph is :" +
                                 std::to_string(secondPermutationPair) + "}" + "\n";


            //if you want to write each also to separate file
            ofstream outfile(resultPath);
            outfile << 1 << endl << 1 << endl;
            outfile << finalGraph.comment;
            outfile << finalGraph.noOfVerticies << endl;
            for (int i = 0; i < finalGraph.noOfVerticies; ++i) {
                for (int j = 0; j < finalGraph.vertices[i].neighbors.size(); ++j) {
                    outfile << finalGraph.vertices[i].neighbors[j] << " ";
                }
                outfile << endl;
            }
            // if not comment out previous section


            allfile << current << endl;
            allfile <<  "{" + config + "}" << endl;
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
