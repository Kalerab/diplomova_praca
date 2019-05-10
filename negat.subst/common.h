#ifndef NEGATORSUBSTITUTION_COMMON_H
#define NEGATORSUBSTITUTION_COMMON_H
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <memory>
#include <unordered_set>


typedef std::vector<int> Cycle;
typedef std::vector< Cycle > CycledGraph;

typedef struct Vertex {
    int number;
    std::vector<int> neighbors;
    //array of vertex neighbours index
} Vertex;

typedef struct Graph {
    int graphNumber;
    int noOfVerticies;
    std::vector< Vertex > vertices;
    std::string comment;
    std::vector< Cycle > chordless;
    std::vector< Cycle > permutationCycles;
    std::vector< Cycle > pentCycles;
    std::vector< Cycle > halfCycles;
    std::vector< Cycle > allPermutationCycles;
    bool permut;
} Graph;

int positionOfElement(std::vector<int> *vector, int element);

bool elementInVector(std::vector<int> *vector, int element);


#endif //NEGATORSUBSTITUTION_COMMON_H
