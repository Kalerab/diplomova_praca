#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <vector>
#include "mainprogram.h"

void computeFiles(const std::vector<std::string> files, bool permutation, bool allcycles, bool cycleperm,
                  bool halfperm, bool cycledoublecover, bool clusters, std::string currentDir);

#endif // PRINT_H
