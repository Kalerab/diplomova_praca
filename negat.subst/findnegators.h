#ifndef NEGATORSUBSTITUTION_FINDNEGATORS_H
#define NEGATORSUBSTITUTION_FINDNEGATORS_H
#pragma once

#include "common.h"

std::vector< CycledGraph > findnegators(std::vector< CycledGraph > &klasters);

std::unordered_set<int> countVertices(std::vector<std::vector<int>> &cycles);

bool specifyCluster(std::vector<Cycle> &cycles, int uniqueVertices);

#endif //NEGATORSUBSTITUTION_FINDNEGATORS_H
