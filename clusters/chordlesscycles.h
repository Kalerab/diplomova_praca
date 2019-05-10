#pragma once
#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include "common.h"

bool adjacent(const Vertex &V1, const Vertex &V2);
void chordless_cycles(Graph &G);

#endif
