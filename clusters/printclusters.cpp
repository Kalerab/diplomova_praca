#include "printclusters.h"

using namespace std;

void printPentagon(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included){
    outfile << "Pentagon -> 5 : (";
    for (int i = 0; i < 5; ++i) {
        int currentVert = klaster[0][i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;
//    return klaster[0];
}

void printDoublePentagon(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included){
    vector<int> result;
    for (int i = 0; i < 5; ++i) {
        int currentVert = klaster[0][i];
        if (elementInVector(&klaster[1], currentVert)){
            result.push_back(currentVert);
        }
    }
    int first = result[0];
    int second = result[1];
    int orientation;
    int positionSecond;

    for (int k = 0; k < 2; ++k) {
        orientation = 1;
        if (abs(positionOfElement(klaster[k], first) - positionOfElement(klaster[k], second)) == 1) orientation *= -1;
        if (positionOfElement(klaster[k], first) < positionOfElement(klaster[k], second)) orientation *= -1;

        positionSecond = positionOfElement(klaster[k], second);

        for (int j = 0; j < 3; ++j) {
            result.push_back(klaster[k][(positionSecond + 5 + orientation*(j+1)) % 5]);
        }
    }

//    return result;

    outfile << "Double Pentagon -> 7 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;

}

void printNegator(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    vector<int> result;
    vector<int> apexNeigh;
    int apex;

    for (int i = 0; i < 5; ++i) {
        int currentVert = klaster[0][i];
        if (elementInVector(&klaster[1],currentVert)){
            int count = 0;
            for (int j = 0; j < 3; ++j) {
                int neigh = G.vertices[currentVert].neighbors[j];
                if (elementInVector(&klaster[0],neigh) && elementInVector(&klaster[1],neigh)){
                    count++;
                }
            }
            if (count == 2) {
                apex = currentVert;
            } else {
                apexNeigh.push_back(currentVert);
            }
        }
    }


    result.push_back(apex);
    for (int k = 0; k < 2; ++k) {
        result.push_back(apexNeigh[k]);
    }

    int first = result[1];
    int orientation;
    int positionFirst;

    for (int k = 0; k < 2; ++k) {
        orientation = 1;
        if (abs(positionOfElement(klaster[k], apex) - positionOfElement(klaster[k], first)) == 1) orientation *= -1;
        if (positionOfElement(klaster[k], apex) < positionOfElement(klaster[k], first)) orientation *= -1;

        positionFirst = positionOfElement(klaster[k], first);

        for (int j = 0; j < 2; ++j) {
            result.push_back(klaster[k][(positionFirst + 5 + orientation*(j+1)) % 5]);
        }
    }

//    return result;

    outfile << "Negator -> 7 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;
}

void printTriplePentagon(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    vector<int> result;
    int midpoint;
    int first;
    int second;
    int third;

    for (int i = 0; i < 5; ++i) {
        int currentVert = klaster[0][i];
        if (elementInVector(&klaster[1], currentVert) && elementInVector(&klaster[2], currentVert)){
            midpoint = currentVert;
            result.push_back(midpoint);
        }
    }

    vector<int> neigh = G.vertices[midpoint].neighbors;
    for (int l = 0; l < 3; ++l) {
        int currentVert = neigh[l];
        if (elementInVector(&klaster[0], currentVert) && elementInVector(&klaster[2], currentVert)){
            first = currentVert;
        }
        if (elementInVector(&klaster[0], currentVert) && elementInVector(&klaster[1], currentVert)){
            second = currentVert;
        }
        if (elementInVector(&klaster[1], currentVert) && elementInVector(&klaster[2], currentVert)){
            third = currentVert;
        }
    }

    result.push_back(first);
    result.push_back(second);
    result.push_back(third);

    int orientation;
    int position;
    for (int k = 0; k < 3; ++k) {
        orientation = 1;
        if (abs(positionOfElement(klaster[k], midpoint) - positionOfElement(klaster[k], result[k+1])) == 1) orientation *= -1;
        if (positionOfElement(klaster[k], midpoint) < positionOfElement(klaster[k], result[k+1])) orientation *= -1;

        position = positionOfElement(klaster[k], result[k+1]);

        for (int j = 0; j < 2; ++j) {
            result.push_back(klaster[k][(position + 5 + orientation*(j+1)) % 5]);
        }
    }

//    return result;

    outfile << "Triple Pentagon -> 10 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;
}

void printTricell(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    vector<int> result;
    vector<Cycle> newCluster;
    vector<int> firstCycle;
    vector<int> secondCycle;
    vector<int> thirdCycle;

    for (int i = 0; i < 3; ++i) {
        int neigh = 0;
        for (int j = 0; j < 5; ++j) {
            int currentVert = klaster[i][j];
            if (elementInVector(&klaster[(i+1)%3],currentVert) || elementInVector(&klaster[(i+2)%3],currentVert)){
                neigh++;
            }
        }

        if (neigh == 2) firstCycle = klaster[i];
        if (neigh == 5) secondCycle = klaster[i];
        if (neigh == 3) thirdCycle = klaster[i];
    }

    newCluster.push_back(firstCycle);
    newCluster.push_back(secondCycle);
    newCluster.push_back(thirdCycle);


    for (int i = 0; i < 5; ++i) {
        int currentVert = newCluster[0][i];
        if (elementInVector(&newCluster[1], currentVert)){
            result.push_back(currentVert);
        }
    }

    int first = result[0];
    int second = result[1];
    int orientation;
    int positionSecond;
    int last;
    int positionLast;

    for (int k = 0; k < 2; ++k) {
        orientation = 1;
        if (abs(positionOfElement(newCluster[k], first) - positionOfElement(newCluster[k], second)) == 1) orientation *= -1;
        if (positionOfElement(newCluster[k], first) < positionOfElement(newCluster[k], second)) orientation *= -1;

        positionSecond = positionOfElement(newCluster[k], second);

        for (int j = 0; j < 3; ++j) {
            result.push_back(newCluster[k][(positionSecond + 5 + orientation*(j+1)) % 5]);
        }
    }

    last = result.back();
    positionLast = positionOfElement(newCluster[2], last);
    if (elementInVector(&newCluster[2], (positionLast+1)%5)){
        orientation = -1;
    } else {
        orientation = 1;
    }

    result.push_back(newCluster[2][(positionLast+5+orientation)%5]);
    result.push_back(newCluster[2][(positionLast+5+orientation*2)%5]);

//    return result;

    outfile << "Tricell -> 10 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;
}


void printTriad(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    vector<int> result;

    vector<int> allVertices;

    for (int i = 0; i < klaster.size(); ++i) {
        for (int j = 0; j < 5; ++j) {
            int currentVert = klaster[i][j];
            if (!elementInVector(&allVertices, currentVert)){
                allVertices.push_back(currentVert);
            }
        }
    }

    vector<int> connectors;

    for (int i = 0; i < allVertices.size(); ++i) {
        int count = 0;
        int currentVert = allVertices[i];
        for (int j = 0; j < klaster.size(); ++j) {
            if (elementInVector(&klaster[j], currentVert)){
                count ++;
            }
        }
        if (count == 1){
            connectors.push_back(currentVert);
        }
    }

    Cycle midCycle;
    int apex;
    for (int i = 0; i < klaster.size(); ++i) {
        int count = 0;
        for (int j = 0; j < connectors.size(); ++j) {
            if (elementInVector(&klaster[i], connectors[j])) count++;
        }
        if (count == 1) midCycle = klaster[i];
    }

    for (int i = 0; i < 5; ++i) {
        if (elementInVector(&connectors,midCycle[i])) apex = midCycle[i];
    }
    result.push_back(apex);

    for (int i = 0; i < 5; ++i) {
        int currentVert = midCycle[i];
        int nonCycleNeigh;
        bool apexNeigh = false;
        for (int j = 0; j < 3; ++j) {
            int neigh = G.vertices[currentVert].neighbors[j];
            if (!elementInVector(&midCycle, neigh)) nonCycleNeigh = neigh;
            if (neigh == apex) apexNeigh = true;
        }
        if (currentVert == apex) apexNeigh = true;
        if (!apexNeigh) result.push_back(nonCycleNeigh);
    }
    int firstVertex;
    int secondVertex;


    for (int i = 0; i < connectors.size(); ++i) {
        int currentVert = connectors[i];
        if (!elementInVector(&result, currentVert)){
            int neigh = result[1];
            if (elementInVector(&G.vertices[currentVert].neighbors, neigh)){
                firstVertex = currentVert;
            } else {
                secondVertex = currentVert;
            }
        }
    }

    result.push_back(firstVertex);
    result.push_back(secondVertex);


    int nextVert;
    for (int i = 0; i < 5; ++i) {
        int currentVert = midCycle[i];
        if (elementInVector(&G.vertices[currentVert].neighbors, firstVertex)){
            nextVert = currentVert;
        }
    }

    int orientation = 1;
    if (abs(positionOfElement(midCycle, apex) - positionOfElement(midCycle, nextVert)) == 1) orientation *= -1;
    if (positionOfElement(midCycle, apex) < positionOfElement(midCycle, nextVert)) orientation *= -1;

    int position = positionOfElement(midCycle, nextVert);

    for (int j = 0; j < 4; ++j) {
        result.push_back(midCycle[(position + 5 + orientation*(j)) % 5]);
    }

    outfile << "Triad -> 9 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;

}

void printIsochrome(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    vector<int> result;
    vector<int> allVertices;
    vector<int> degThreeVert;
    vector<int> degTwoVert;
    vector<int> count;

    int currentIndex = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            int currentVert = klaster[i][j];
            if (!elementInVector(&allVertices,currentVert)){
                allVertices.push_back(currentVert);
                count.push_back(1);
            } else {
                int pos = positionOfElement(allVertices, currentVert);
                count[pos]++;
            }
        }
    }
    for (int k = 0; k < 8; ++k) {
        if (count[k] == 3){
            degThreeVert.push_back(allVertices[k]);
        } else {
            degTwoVert.push_back(allVertices[k]);
        }
    }
    int first = degTwoVert[0];
    int lastVert = first;
    result.push_back(first);
    for (int l = 0; l < 7; ++l) {
        for (int i = 0; i < 3; ++i) {
            int currentNeigh = G.vertices[lastVert].neighbors[i];
            if (elementInVector(&allVertices, currentNeigh) && !elementInVector(&result,currentNeigh) && (elementInVector(&degThreeVert, currentNeigh) != elementInVector(&degThreeVert, lastVert))){
                result.push_back(currentNeigh);
                lastVert = currentNeigh;
                i=3;
            }
        }
    }

    outfile << "Isochrome -> 8 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;

//    return result;

}

void printHeterochrome1(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    vector<int> result;
    vector<int> allVertices;
    int midPoint;
    vector<int> cubicThree;
    vector<int> inTwoCycles;
    vector<int> inOneCycle;
    vector<int> midCycle;


    for (int i = 0; i < klaster.size(); ++i) {
        for (int j = 0; j < 5; ++j) {
            int currentVert = klaster[i][j];
            if (!elementInVector(&allVertices, currentVert)){
                allVertices.push_back(currentVert);
            }
        }
    }

    for (int i = 0; i < allVertices.size(); ++i) {
        int count = 0;
        int currentVert = allVertices[i];
        for (int j = 0; j < klaster.size(); ++j) {
            if (elementInVector(&klaster[j], currentVert)){
                count ++;
            }
        }
        if (count == 4) midPoint = currentVert;
        if (count == 3) cubicThree.push_back(currentVert);
        if (count == 2) inTwoCycles.push_back(currentVert);
        if (count == 1) inOneCycle.push_back(currentVert);
    }

    for (int i = 0; i < klaster.size(); ++i) {
        int count = 0;
        for (int j = 0; j < cubicThree.size(); ++j) {
            int currentVert = cubicThree[j];
            if (elementInVector(&klaster[i], currentVert)) count++;
        }
        if (count == 4) midCycle = klaster[i];
    }

    int topVertex;
    for (int i = 0; i < cubicThree.size(); ++i) {
        int currentVert = cubicThree[i];
        if (elementInVector(&G.vertices[currentVert].neighbors, midPoint) && !elementInVector(&midCycle, currentVert)){
            topVertex = currentVert;
            result.push_back(topVertex);
            for (int j = 0; j < 3; ++j) {
                if (G.vertices[currentVert].neighbors[j] != midPoint) {
                    result.push_back(G.vertices[currentVert].neighbors[j]);
                }
            }
        }
    }

    int firstVertex = result[1];
    int secondVertex = result[2];
    int bottomFirst;
    int bottomSecond;

    int oppositeNeigh;
    int directNeigh;
    for (int i = 0; i < cubicThree.size(); ++i) {
        int currentVert = cubicThree[i];
        if (elementInVector(&G.vertices[currentVert].neighbors, secondVertex) && currentVert != topVertex){
            oppositeNeigh = currentVert;
        }
    }
    for (int i = 0; i < cubicThree.size(); ++i) {
        int currentVert = cubicThree[i];
        if (elementInVector(&G.vertices[currentVert].neighbors, oppositeNeigh)
            && !elementInVector(&G.vertices[currentVert].neighbors, firstVertex)) {
            directNeigh = currentVert;
        }
    }

    for (int i = 0; i < inOneCycle.size(); ++i) {
        int currentVert = inOneCycle[i];
        if (elementInVector(&G.vertices[currentVert].neighbors, directNeigh)){
            bottomFirst = currentVert;
        } else {
            bottomSecond = currentVert;
        }
    }

    result.push_back(bottomFirst);
    result.push_back(bottomSecond);

    int orientation = 1;
    if (abs(positionOfElement(midCycle, midPoint) - positionOfElement(midCycle, directNeigh)) == 1) orientation *= -1;
    if (positionOfElement(midCycle, midPoint) < positionOfElement(midCycle, directNeigh)) orientation *= -1;

    int position = positionOfElement(midCycle, midPoint);

    for (int j = 0; j < 5; ++j) {
        result.push_back(midCycle[(position + 5 + orientation*(j)) % 5]);
    }

    outfile << "Heterochrome 1 -> 10 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;
}

void printHeterochrome2(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    vector<int> allVertices;
    vector<int> result;

    for (int i = 0; i < klaster.size(); ++i) {
        for (int j = 0; j < 5; ++j) {
            int currentVert = klaster[i][j];
            if (!elementInVector(&allVertices, currentVert)){
                allVertices.push_back(currentVert);
            }
        }
    }

    vector<int> inTwoCycles;
    vector<int> connectors;
    vector<int> inAllCycles;

    for (int i = 0; i < allVertices.size(); ++i) {
        int currentVert = allVertices[i];
        int count = 0;
        for (int j = 0; j < klaster.size(); ++j) {
            if (elementInVector(&klaster[j], currentVert)) count++;
        }
        if (count == 2) inTwoCycles.push_back(currentVert);
        if (count == 1) connectors.push_back(currentVert);
        if (count == 4) inAllCycles.push_back(currentVert);
    }

    int midPoint = inAllCycles[0];
    for (int i = 0; i < 3; ++i) {
        int neigh = G.vertices[midPoint].neighbors[i];
        if (!elementInVector(&inAllCycles, neigh)){
            result.push_back(neigh);
        }
    }

    int firstVertex = result[0];
    for (int i = 0; i < 3; ++i) {
        int neigh = G.vertices[firstVertex].neighbors[i];
        if (neigh != midPoint) result.push_back(neigh);
    }
    int secondVertex = result[1];
    int thirdVertNeig;

    for (int i = 0; i < 3; ++i) {
        int neigh = G.vertices[result[2]].neighbors[i];
        if (elementInVector(&inTwoCycles, neigh) && neigh != firstVertex){
            thirdVertNeig = neigh;
        }
    }

    int firstBottomVert;
    int secondBottomVert;
    for (int i = 0; i < 3; ++i) {
        int neigh = G.vertices[secondVertex].neighbors[i];
        if (neigh != midPoint && !elementInVector(&G.vertices[thirdVertNeig].neighbors, neigh)){
            firstBottomVert = neigh;
        } else if (neigh != midPoint) {
            secondBottomVert = neigh;
        }
    }

    result.push_back(firstBottomVert);
    result.push_back(secondBottomVert);
    result.push_back(midPoint);
    result.push_back(thirdVertNeig);

    for (int i = 0; i < allVertices.size(); ++i) {
        int currentVert = allVertices[i];
        if (!elementInVector(&result, currentVert) && currentVert != inAllCycles[1]){
            result.push_back(currentVert);
        }
    }

    result.push_back(inAllCycles[1]);

    outfile << "Heterochrome 2 -> 10 : (";
    for (int i = 0; i < result.size(); ++i) {
        int currentVert = result[i];
        outfile << currentVert << " ";
        included[currentVert] = true;
    }
    outfile << ")" << endl;
}

void printNonpeters(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G){
    outfile << "Non-petersenian cluster -> ";

    vector<int> uniqueVertices;
    for (int j = 0; j < klaster.size(); ++j) {
        for (int l = 0; l < 5; ++l) {
            if (!elementInVector(&uniqueVertices, klaster[j][l])) {
                uniqueVertices.push_back(klaster[j][l]);
            }
        }
    }
    outfile << uniqueVertices.size() << " (";
    for (int i = 0; i < uniqueVertices.size(); ++i) {
        outfile << uniqueVertices[i] << " ";
    }
    outfile << ")" << endl;

    vector<vector<int>> output;
    vector<int> usedVertices;
    for (int m = 0; m < klaster.size(); ++m) {
        for (int j = 0; j < 5; ++j) {
            if (!elementInVector(&usedVertices, klaster[m][j])) {
                usedVertices.push_back(klaster[m][j]);
                vector<int> currentVertNeigh;
                currentVertNeigh.push_back(klaster[m][(j + 4) % 5]);
                currentVertNeigh.push_back(klaster[m][(j + 1) % 5]);
                output.push_back(currentVertNeigh);
            } else {
                int position = positionOfElement(usedVertices, klaster[m][j]);
                int currentVertex = klaster[m][j];
                if (!elementInVector(&output[position], klaster[m][(j + 1) % 5])) {
                    output[position].push_back(klaster[m][(j + 1) % 5]);
                }
                if (!elementInVector(&output[position], klaster[m][(j + 4) % 5])) {
                    output[position].push_back(klaster[m][(j + 4) % 5]);
                }
            }
        }
    }
    for (int n = 0; n < usedVertices.size(); ++n) {
        outfile << usedVertices[n] << " > ";
        for (int j = 0; j < output[n].size(); ++j) {
            outfile << output[n][j] << " ";
            included[output[n][j]] = true;
        }
        for (int l = 0; l < 3; ++l) {
            int neigh = G.vertices[usedVertices[n]].neighbors[l];
            if (!elementInVector(&output[n], neigh) && elementInVector(&usedVertices, neigh)) {
                outfile << "; " << neigh;
            }
        }
        outfile << endl;
    }
}

void outputClusterStatistics(int *count, std::ofstream &outfile, std::ofstream &clusters, std::string filename){
    std::string clusterName[10];
    clusterName[0] = "Pentagons";
    clusterName[1] = "Double Pentagons";
    clusterName[2] = "Negator";
    clusterName[3] = "Triple Pentagon";
    clusterName[4] = "Tricell";
    clusterName[5] = "Triad";
    clusterName[6] = "Isochrome";
    clusterName[7] = "Heterochrome-1";
    clusterName[8] = "Heterochrome-2";
    clusterName[9] = "Non-petersenian cluster";
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

    clusters.close();

}





