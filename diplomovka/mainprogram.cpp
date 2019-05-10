#include "mainprogram.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include "scanner.h"
#include "chordlesscycles.h"
#include "graphseparator.h"
#include "findpermutation.h"
#include "common.h"
#include <chrono>
#include <list>


//#ifdef WINDOWS
//    #include <direct.h>
//    #define GetCurrentDir _getcwd
//    std::string graphsDir = "\\Snarks\\";
//    std::string resultsDir = "\\Results\\";
//#else
//    #include <unistd.h>
#include <cstring>
//
//
//#define GetCurrentDir getcwd
//    std::string graphsDir = "/Snarks/";
//    std::string resultsDir = "/Results/";
//#endif

using namespace std;

/* Directory settings depending on current operation system
 * Suitable just for windows and linux-based operation systems
 * */

//string defaultFile = "PET.10"; //File used when no parameter is passed
//string getExecutionPath() {
//    char cCurrentPath[FILENAME_MAX];
//    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
//    {
//        cout << "Cannot read current execution location";
//        throw "CannotGetPath";
//    }
//    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
//    string path = string(cCurrentPath);
//    return path.substr(0, path.length() - 4); //Cut "bin/"
//}

//string getFileName(int argc, char *argv[]) {
//    if(argc > 2) {
//        //0 - executable name, 1 - file name
//        cout << "Unknown number of arguments. Expecting 1 or less";
//        throw "TooManyParams";
//    }

//    return argc == 1 ?
//           defaultFile : //No parameter passed, use default
//           string(argv[1]); //Use passed file name
//}

void mainFunction(bool permutation, bool allcycles, bool cycleperm, bool halfperm, bool cycledoublecover, bool clusters,
                  string inputFile,string fileName, string fileNameWExt, string extension, string currentDir) {
//    string basePath = getExecutionPath();
//    string fileName = getFileName(argc, argv);
//    string path = basePath + resultsDir + fileName;
//    string inputFile = basePath + graphsDir + fileName;

    /*
     * Reading input file
     * Spliting file into snarks with method scanFile()
     * */
    Scanner scanner;
    vector<Graph> graphs = scanner.scanFile(inputFile);

    /*
     * Initializing of file name suffix
     * */
    string result = "_results.txt";
    string permut = "_permutations.txt";
    string cluster = "_clusters.txt";
    string half = "_halfpermutations.txt";

    /*
     * Initializing of variables that will be printed after testing all snarks - global variables for whole file
     * */
    int numberOfPermutGraphs = 0;
    int numberOfHalfPermutGraphs = 0;
    int numberOfGraphs = 0;
    int clusterCount[10];
    for (int &l : clusterCount) {
        l =0;
    }

    /*
     * Initializing of output filenames and printing lines to them that will be over-writed
     * after testing all snarks
     * */

    //string resultPath = basePath + resultsDir + fileName + result;
    string path = currentDir + "/results/" + fileNameWExt;
    string resultPath = currentDir + "/results/" + fileNameWExt + result;
    ofstream outfile (resultPath);

    string graphsPath = currentDir + "/results/" + fileNameWExt + permut;
    ofstream permutfile (graphsPath);

    string halfPermutPath = currentDir + "/results/" + fileNameWExt + half;
    ofstream halfpermutfile (halfPermutPath);

    outfile << "Number of graphs in file: " << graphs.size() << endl;
    outfile << "NumberOfGraphs" << endl;
    outfile << "NumberOfHalfGraphs" << endl;
    outfile << endl << endl;
    permutfile << "NumberOfGraphs" << endl;
    halfpermutfile << "NumberOfHalfGraphs" << endl;

    /*
     * Testing properties for each snark in input file
     * */
    for (int i = 0; i < graphs.size(); ++i) {
        Graph G = graphs[i];

        /*
         * Finding chordless cycles in graph
         * */
        G.chordless = chordless_cycles(G);
        vector< Cycle > halfLength;
        vector< Cycle > pentLength;


        /*
         * Dividing cycles by length
         * We need cycles of length 5 and half-length cycles
         * */
        for (int j = 0; j < G.chordless->size(); ++j) {
            if ((*G.chordless)[j].size() == (G.noOfVerticies / 2)) {
                halfLength.push_back((*G.chordless)[j]);
            }
            if ((*G.chordless)[j].size() == 5) {
                pentLength.push_back((*G.chordless)[j]);
            }
        }


        /*
         * Testing if graph is permutation - contains 2 disjoint cycles of half-length
         * We need to have n%4 == 2, where n is number of vertices
         * If n%4 == 0 then half-length cycles will have odd length and we can do cyclic shift on graph coloring
         * and we will be able to color it with just 3 colors
         * findpermut() check if exist at least one permutational pair, if exist function will stop as soon as
         * one pair will be found
         * */
        if (permutation) {
            if (halfLength.size() > 0 && G.noOfVerticies % 4 == 2) findPermut2(G, halfLength);
            //if (halfLength.size()>0) findPermut(G, halfLength);

            /*
             * If graph is permutation we'll search for all permutational pairs in graph.
             */
            if (G.permut) findAllPermut(G, halfLength);
            /*
             * If graph is permutation this will output permutation cycles into file
             * and print whole graph to separate file containing just permutation snarks
             * */
            if (G.permut) {
                numberOfPermutGraphs++;
                numberOfGraphs++;

                outfile << "Graph Number: " << G.graphNumber << endl;
                outfile << "Number of Vertices: " << G.noOfVerticies << endl;
                outfile << "(n mod 8) = " << (G.noOfVerticies % 8) << endl;
                outfile << "Permutation graph" << endl;
                outfile << "Permutation cycles:" << endl;

                if (G.allPermutationCycles.size() > 1) {
                    for (int j = 0; j < G.allPermutationCycles.size(); ++j) {
                        printCycle(G.allPermutationCycles[j], outfile);
                        if (j % 2 == 1) outfile << endl;
                    }
                } else {
                    for (int j = 0; j < G.permutationCycles.size(); ++j) {
                        printCycle(G.permutationCycles[j], outfile);
                    }
                }


                permutfile << numberOfPermutGraphs << endl;
                permutfile << "{Permutation snark}" << endl;
                printGraph(G, permutfile);
            }
        }


        /*
         * If graph is not permutation this will test if it's at least half-permutation
         * */
        if (!G.permut && halfLength.size()>0) {
            halfPermut(G, halfLength);
            if (G.halfPermut) {
                numberOfHalfPermutGraphs++;
                numberOfGraphs++;
                outfile << "Graph Number: " << G.graphNumber <<  endl;
                outfile << "Number of Vertices: " << G.noOfVerticies << endl;
                outfile << "(n mod 8) = " << (G.noOfVerticies%8) << endl;
                outfile << "Half-permutation graph" << endl;
                outfile << "Half-permutation cycles:" << endl;
                for (const auto &halfPermutationCycle : G.halfPermutationCycles) {
                    printCycle(halfPermutationCycle, outfile);
                }

                halfpermutfile << numberOfHalfPermutGraphs << endl;
                halfpermutfile << "{Half-permutation snark}" << endl;
                printGraph(G, halfpermutfile);
            }
        }


        if (!G.permut && !G.halfPermut){
            numberOfGraphs++;
            outfile << "Graph Number: " << G.graphNumber <<  endl;
            outfile << "Number of Vertices: " << G.noOfVerticies << endl;
            outfile << "(n mod 8) = " << (G.noOfVerticies%8) << endl;
            outfile << "No permutation or half-permutation graph" << endl;
        }

            /*
             * Dedicating of clusters of petersens graph in current snark
             * First we separate cycles with length 5 into groups by Union-Find
             *
             * */
            auto klaster = separate_cycles_into_graphs(pentLength);
            int notInClusters = G.noOfVerticies;
            bool includedVertices[G.noOfVerticies] = {false};

            if ((*klaster).size() > 0) {
                outfile << "Clusters: " << (*klaster).size() << endl;
            }
            for (auto &k : (*klaster)) {

                std::unordered_set<int> currentVertices = countVertices(k);
                outfile << currentVertices.size() << " -> (";
                notInClusters -= currentVertices.size();

                string clusterName = specifyCluster(k,currentVertices.size(), clusterCount, G.noOfVerticies);

                if (clusterName == "Negator"){
                    vector< Cycle > negator;
                    negator = k;

                    int apex;
                    vector<int> apexNeigh;
                    for (int j = 0; j < 5; ++j) {
                        for (int l = 0; l < 5; ++l) {
                            if (negator[0][j] == negator[1][l]) {
                                apexNeigh.push_back(negator[0][j]);
                                includedVertices[negator[0][j]] = true;
                                currentVertices.erase(negator[0][j]);
                            }
                        }
                    }

                    bool stop = false;
                    for (int m = 0; m < 3 && !stop; ++m) {
                        int total = 0;
                        for (int j = 0; j < 3 && !stop; ++j) {
                            for (int l = 0; l < 3 && !stop; ++l) {
                                if (G.vertices[apexNeigh[m]].neighbors[j] == apexNeigh[l]) total++;
                                if (total == 2){
                                    apex = apexNeigh[m];
                                    apexNeigh.erase(apexNeigh.begin() + m);
                                    stop = true;
                                }
                            }
                        }
                    }

                    std::list<int> prvky;
                    prvky.push_back(apex);
                    prvky.push_back(apexNeigh[0]);
                    prvky.push_back(apexNeigh[1]);

                    for (auto j = currentVertices.begin(); j != currentVertices.end(); ++j) {
                        prvky.push_back(j.operator*());
                        includedVertices[j.operator*()] = true;
                    }

                    for (int n : prvky) {
                        outfile << n << " ";
                    }


                } else if (clusterName == "Triple Pentagon") {
                    vector<int> triad;
                    for (auto j = currentVertices.begin(); j != currentVertices.end(); ++j) {
                        triad.push_back(j.operator*());
                    }

                    bool midPoint = false;
                    int midVertex = 0;
                    for (int l = 0; l < triad.size(); ++l) {
                        int mid = triad[l];
                        int total = 0;
                        for (int j = 0; j < triad.size(); ++j) {
                            for (int m = 0; m < 3; ++m) {
                                if (G.vertices[mid].neighbors[m]==triad[j]){
                                    total++;
                                }
                            }
                        }
                        if (total == 3){
                            midPoint = true;
                            midVertex = mid;
                        }
                    }

                    if (midPoint){
                        std::list<int> prvky;
                        prvky.push_back(midVertex);
                        includedVertices[midVertex] = true;
                        currentVertices.erase(midVertex);
                        for (int j = 0; j < 3; ++j) {
                            int currentVertex = G.vertices[midVertex].neighbors[j];
                            prvky.push_back(currentVertex);
                            includedVertices[currentVertex] = true;
                            currentVertices.erase(currentVertex);
                        }

                        for (auto j = currentVertices.begin(); j != currentVertices.end(); ++j) {
                            prvky.push_back(j.operator*());
                            includedVertices[j.operator*()] = true;
                        }

                        clusterName = "Triple Pentagon";
                        for (int n : prvky) {
                            outfile << n << " ";
                        }

                    } else {

                        clusterCount[6]--;
                        clusterCount[9]++;
                        clusterName = "Tricell";
                        std::list<int> prvky;
                        for (auto j = currentVertices.begin(); j != currentVertices.end(); ++j) {
                            prvky.push_back(j.operator*());
                            includedVertices[j.operator*()] = true;
                        }

                        for (int n : prvky) {
                            outfile << n << " ";
                        }
                    }

                } else {
                    for (auto j = currentVertices.begin(); j != currentVertices.end(); ++j) {
                        outfile << j.operator*() << " ";
                        includedVertices[j.operator*()] = true;
                    }
                }


                outfile << ")";
                if (currentVertices.size() <= 10) {
                    outfile << " -> " << clusterName << endl;
                } else {
                    outfile << " -> Non-petersenian cluster" << endl;
                    clusterCount[8]++;
                }
            }


            if (notInClusters > 0) {
                outfile << "Count of non-cluster vertices: " << notInClusters << endl;
                outfile << "List of non-cluster vertices (";
                for (int j = 0; j < G.noOfVerticies; ++j) {
                    if (!includedVertices[j]){
                        outfile << j << " ";
                    }
                }
                outfile << ")" << endl;
            } else {
                outfile << "All vertices are included in clusters" << endl;
            }
        if (G.permut && G.cycleDouble){
            printCDC(outfile);
        } else {
            outfile << "This graph don't contain permutational cycle double cover" << endl;
        }
        outfile << endl;
        //}
        pentLength.clear();
        halfLength.clear();
    }


    string clustersPath = currentDir + "/results/" + fileNameWExt + cluster;
    ofstream clustersOut (clustersPath);


    outputClusterStatistics(clusterCount,outfile, clustersOut, fileName);



    editFile(numberOfPermutGraphs, numberOfHalfPermutGraphs, path, result);


    if (numberOfPermutGraphs != 0) {

        editFile(numberOfPermutGraphs, numberOfHalfPermutGraphs, path, permut);
    } else {

        std::remove(graphsPath.c_str());
    }
    if (numberOfHalfPermutGraphs != 0) {
        editFile(numberOfPermutGraphs, numberOfHalfPermutGraphs, path, half);
    } else {
        std::remove(halfPermutPath.c_str());
    }
    halfpermutfile.close();
    clustersOut.close();
    outfile.close();
    permutfile.close();
    return;
}


