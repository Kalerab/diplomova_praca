#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <list>

#include "mainprogram.h"
#include "scanner.h"
#include "chordlesscycles.h"
#include "graphseparator.h"
#include "printclusters.h"
#include "specifyclusters.h"

#include <cstring>

using namespace std;


void mainFunction(string inputFile, string fileName, string fileNameWExt, string extension, string currentDir, bool printclusters) {

    /*
     * Reading input file
     * Spliting file into snarks with method scanFile()
     * */
    Scanner scanner;
    vector<Graph> graphs = scanner.scanFile(inputFile);

    /*
     * Initializing of file name suffix
     * */
    string result = "_results.";

    /*
     * Initializing of variables that will be printed after testing all snarks - global variables for whole file
     * */
    int numberOfGraphs = 0;
    int clusterCount[10];
    for (int &l : clusterCount) {
        l = 0;
    }

    /*
     * Initializing of output filenames and printing lines to them that will be over-writed
     * after testing all snarks
     * */

    //string resultPath = basePath + resultsDir + fileName + result;
    string path = currentDir + "/results/" + fileName;
    string resultPath = currentDir + "/results/" + fileName + result + extension;
    ofstream outfile(resultPath);


    outfile << "Number of graphs in file: " << graphs.size() << endl;
    outfile << endl;

    /*
     * Testing properties for each snark in input file
     * */
    for (int i = 0; i < graphs.size(); ++i) {
        Graph G = graphs[i];
        outfile << "Graph number: " << G.graphNumber << endl;


        /*
         * Finding chordless cycles in graph
         * */
        chordless_cycles(G);
        vector<Cycle> pentLength;


        /*
         * Dividing cycles by length
         * We need cycles of length 5 and half-length cycles
         * */
        for (int j = 0; j < G.chordless.size(); ++j) {
            if ((G.chordless)[j].size() == 5) {
                pentLength.push_back((G.chordless)[j]);
            }
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

//                printTriad(k, outfile, includedVertices, G);

            std::unordered_set<int> currentVertices = countVertices(k);
//                outfile << currentVertices.size() << " -> (";
            notInClusters -= currentVertices.size();

//                string clusterName = specifyCluster(k, currentVertices.size(), clusterCount, G.noOfVerticies);
            int clusterType = specifyClusterType(k, currentVertices.size(), clusterCount, G.noOfVerticies);

            switch (clusterType){
                case 0: printPentagon(k, outfile, includedVertices); break;
                case 1: printDoublePentagon(k, outfile, includedVertices); break;
                case 2: printNegator(k, outfile, includedVertices, G); break;
                case 3: printTriplePentagon(k, outfile, includedVertices, G); break;
                case 4: printTricell(k, outfile, includedVertices, G); break;
                case 5: printTriad(k, outfile, includedVertices, G); break;
                case 6: printIsochrome(k, outfile, includedVertices, G); break;
                case 7: printHeterochrome1(k, outfile, includedVertices, G); break;
                case 8: printHeterochrome2(k, outfile, includedVertices, G); break;
                case 9: printNonpeters(k, outfile, includedVertices, G); break;
            }
        }

        if (notInClusters > 0) {
            outfile << "Count of non-cluster vertices: " << notInClusters << endl;
            outfile << "List of non-cluster vertices (";
            for (int j = 0; j < G.noOfVerticies; ++j) {
                if (!includedVertices[j]) {
                    outfile << j << " ";
                }
            }
            outfile << ")" << endl;
        } else {
            outfile << "All vertices are included in clusters" << endl;
        }


        outfile << endl;
        //}
        pentLength.clear();

    }
    if (printclusters){
        string cluster = "_clustersum.";
        string clustersPath = currentDir + "/results/" + fileName + cluster + extension;
        ofstream clustersOut(clustersPath);
        outputClusterStatistics(clusterCount, outfile, clustersOut, fileNameWExt);
    }

    outfile.close();

    return;
}


