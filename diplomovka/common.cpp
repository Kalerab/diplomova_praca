#include <unordered_map>
#include <unordered_set>
#include <map>
#include "common.h"

using namespace std;


void printCycle(const std::vector<int> &cycle, std::ofstream &outfile) {
    outfile << cycle.size() << " -> "  << "(";
    for (int i = 0; i < cycle.size(); i++) {
        outfile << cycle[i] << " ";
    }
    outfile << ")" << endl;
}

void printCDC(std::ofstream &outfile) {
    outfile << "CDC" << endl;
}

template<typename T>
bool elementInVector(std::vector<T> vector, T element){
    std::vector<T>::iterator it = std::find(vector.begin(), vector.end(), element);
    if (it != vector.end()) return true;
    else return false;
}

template<typename T>
int positionOfElement(std::vector<T> vector, T element){
    std::vector<T>::iterator it = std::find(vector.begin(), vector.end(), element);
    int index = std::distance(vector.begin(), it);
    return index;
}


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
            G.permut = true;
        }
    }
}

void editFile(int number, int halfpermut, string fileName, string extension) {
    string currentName = fileName + extension;
    string newName = fileName + "_tmp.txt";

    const char *oldName = currentName.c_str();
    const char *tmpName = newName.c_str();
    rename(oldName, tmpName);
    string readout;
    string search = "NumberOfGraphs";
    string search2 = "NumberOfHalfGraphs";
    string replaceWith;
    string replaceWithHalf;

    ifstream input;
    input.open(tmpName);
    ofstream output;
    output.open(oldName);
    if (number != 0) {
        if (extension == "_permutations.txt") {
            replaceWith = std::to_string(number);
        } else {
            replaceWith = "Permutation graphs: " + std::to_string(number);
        }
    } else {
        replaceWith = "No permutation graphs in this file.";
    }

    if (halfpermut != 0) {
        if (extension == "_halfpermutations.txt") {
            replaceWithHalf = std::to_string(halfpermut);
        } else {
            replaceWithHalf = "Half-permutation graphs: " + std::to_string(halfpermut);
        }
    } else {
        replaceWithHalf = "No Half-permutation graphs in this file.";
    }

    while (getline(input, readout)) {
        if (readout == search) {
            output << replaceWith << endl;
        }
        else if (readout == search2) {
            output << replaceWithHalf << endl;
        } else {
            output << readout << endl;
        }
    }
    input.close();
    output.close();

    //remove(tmpName);

    //std::remove(oldName);
    std::remove(tmpName);
}

void printGraph(Graph graph, std::ofstream &outfile) {
    if (graph.comment.length() > 0) {
        outfile << graph.comment << endl;
    }
    outfile << graph.noOfVerticies << endl;
    for (int i = 0; i < graph.noOfVerticies; ++i) {
        for (int j = 0; j < 2; ++j) {
            outfile << graph.vertices[i].neighbors[j] << " ";
        }
        outfile << graph.vertices[i].neighbors[2] << endl;
    }

}

void halfPermut(Graph &G, vector<vector<int>> &cycles) {
        bool used[G.noOfVerticies];


    for (int i = 0; i < cycles.size(); ++i) {
        Cycle cycle = cycles[i];
        bool isPermut = true;

        for (int j = 0; j < G.noOfVerticies; ++j) {
            used[j] = false;
        }

        for (int k = 0; k < cycle.size(); ++k) {
            used[cycle[k]] = true;
        }

        for (int l = 0; l < G.noOfVerticies; ++l) {
            if (!used[l]) {
                int neighbour;
                int numberOfNeighbours = 0;
                for (int j = 0; j < 3; ++j) {
                    neighbour = G.vertices[l].neighbors[j];
                    if (used[neighbour]) numberOfNeighbours++;
                }
                if (numberOfNeighbours != 1) {
                    isPermut = false;
                    break;
                }
            }
        }

        // je half permut
        if (!isPermut) {
            continue;
        }

        unordered_set<int> notUsed;
        for (int m = 0; m < G.noOfVerticies; ++m) {
            if (!used[m]) {
                notUsed.insert(m);
            }
        }

        G.halfPermutationCycles.push_back(cycle);

        while (notUsed.size() > 0) {
            Cycle newCycle;
            int currentVert = *notUsed.begin();
            notUsed.erase(currentVert);
            newCycle.push_back(currentVert);
            bool hasNext = true;

            while (hasNext) {
                hasNext = false;
                for (int j = 0; j < 3; ++j) {
                    int neighbour = G.vertices[currentVert].neighbors[j];
                    if (!used[neighbour] && notUsed.find(neighbour) != notUsed.end()) {
                        currentVert = neighbour;
                        notUsed.erase(currentVert);
                        newCycle.push_back(currentVert);
                        hasNext = true;
                        break;
                    }
                }
            }

            G.halfPermutationCycles.push_back(newCycle);
        }
        G.halfPermut = true;
        return;
    }
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


std::string specifyCluster(std::vector<Cycle> &cycles, int uniqueVertices, int *count, int numberOfVert){
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

    if (v == 5 && e == 5 && c == 1){
        count[0]++;
        return "Pentagon";
    }

    if (v == 8 && e == 9 && c == 2){
        count[1]++;
        return "Double Pentagon";
    }

    if (v == 7 && e == 8 && c == 2){
        count[2]++;
        return "Dyad";
    }

    if (v == 10 && e == 13 && c == 5){
        count[3]++;
        return "Heterochromatic - distance 1";
    }

    if (v == 10 && e == 13 && c == 4){
        count[4]++;
        return "Heterochromatic - distance 2";
    }

    if (v == 8 && e == 10 && c == 4){
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
            count[5]++;
            return "Isochromatic";
        }
    }

    if (v == 10 && e == 12 && c == 3){
        count[6]++;
        return "Triple Pentagon";
    }

    if (v == 9 && e == 11 && c == 3){
        count[7]++;
        return "Triad";
    }

    if (v == 10 && e == 15 && c == 12){
        return "Petersens graph";
    }

    count[8]++;
    return "Non-petersenian cluster";
}


void outputClusterStatistics(int *count, std::ofstream &outfile, std::ofstream &clusters, std::string filename){
    std::string clusterName[10];
    clusterName[0] = "Pentagons";
    clusterName[1] = "Double Pentagons";
    clusterName[2] = "Dyad";
    clusterName[3] = "Heterochromatic - distance 1";
    clusterName[4] = "Heterochromatic - distance 2";
    clusterName[5] = "Isochromatics";
    clusterName[6] = "Triple Pentagon";
    clusterName[7] = "Triad";
    clusterName[8] = "Non-petersenian clusters";
    clusterName[9] = "Tricell";
    clusters << "Count of clusters in " << filename << endl << endl;
    outfile << endl << "Count of clusters in this file" << endl;
    int max = 0;
    for (int i = 0; i < 10; ++i) {
        if (count[i]>count[max]) max = i;
        clusters << "Count of " << clusterName[i] << ": " << count[i] << endl;
        outfile << "Count of " << clusterName[i] << ": " << count[i] << endl;
    }
    clusters << endl;
    outfile << endl;

    clusters << "Most common clusters: " << clusterName[max] << " (" << count[max] << ")" << endl;
    outfile << "Most common clusters: " << clusterName[max] << " (" << count[max] << ")" << endl;

}
