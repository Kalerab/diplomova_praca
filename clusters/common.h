#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <memory>
#include <unordered_set>

//Aliased types
typedef std::vector<int> Cycle;
typedef std::vector< Cycle > CycledGraph;

//Custom types
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
} Graph;

int positionOfElement(std::vector<int> vector, int element);
bool elementInVector(std::vector<int> *vector, int element);

//Functions

std::unordered_set<int> countVertices(std::vector< Cycle > &cycles);


#endif
