#ifndef NEGATORSUBSTITUTION_SCANNER_H
#define NEGATORSUBSTITUTION_SCANNER_H

#pragma once

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

#endif //NEGATORSUBSTITUTION_SCANNER_H
