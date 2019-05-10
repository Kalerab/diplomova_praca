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
    int * neighbors;
    //array of vertex neighbours index
} Vertex;

typedef struct Graph {
    int graphNumber;
    int noOfVerticies;
    std::vector< Vertex > vertices;
    std::string comment;
    std::shared_ptr< std::vector< Cycle > > chordless;
    std::vector< Cycle > permutationCycles;
    std::vector< Cycle > allPermutationCycles;
    std::vector< Cycle > halfPermutationCycles;
    std::vector< Cycle > CDCcycle;
    bool permut;
    bool halfPermut;
    bool cycleDouble;
} Graph;



template<typename T>
int positionOfElement(std::vector<T> vector, T element);
template<typename T>
bool elementInVector(std::vector<T> vector, T element);


//Functions
void printCycle(const std::vector<int> &cycle, std::ofstream &outfile);

void printCDC(std::ofstream &outfile);

void findPermut(Graph &G, std::vector< Cycle > &cycles);

void findAllPermut(Graph &G, std::vector< Cycle > &cycles);

void editFile(int permut, int halfpermut, std::string filename, std::string extension);

void printGraph(Graph graph, std::ofstream &outfile);

std::unordered_set<int> countVertices(std::vector< Cycle > &cycles);

void halfPermut(Graph &G, std::vector< Cycle > &cycles);

std::string specifyCluster(std::vector<Cycle> &cycles, int uniqueVertices, int *count, int numberOfVert);

void outputClusterStatistics(int *count, std::ofstream &outfile, std::ofstream &clusters, std::string filename);

#endif
