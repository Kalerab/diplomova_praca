#ifndef DIPLOMOVKA_PRINTCLUSTERS_H
#define DIPLOMOVKA_PRINTCLUSTERS_H
#pragma once

#include "common.h"

void printPentagon(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included);

void printDoublePentagon(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included);

void printNegator(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void printTriplePentagon(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void printTricell(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void printTriad(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void printIsochrome(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void printHeterochrome1(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void printHeterochrome2(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void printNonpeters(std::vector<Cycle> &klaster, std::ofstream &outfile, bool *included, Graph &G);

void outputClusterStatistics(int *count, std::ofstream &outfile, std::ofstream &clusters, std::string filename);



#endif //DIPLOMOVKA_PRINTCLUSTERS_H
