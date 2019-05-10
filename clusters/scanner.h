#pragma once
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include "common.h"

class Scanner {
public:
    Scanner();

    std::vector<Graph> scanFile(std::string file);

    Graph scanGraph(std::fstream &input);

    std::string readComment(std::fstream &input);
};

#endif //DIPLOMOVKA_SCANNER_H
