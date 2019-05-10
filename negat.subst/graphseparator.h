#ifndef NEGATORSUBSTITUTION_GRAPHSEPARATOR_H
#define NEGATORSUBSTITUTION_GRAPHSEPARATOR_H
#pragma once

#include "common.h"

std::shared_ptr< std::vector< CycledGraph > > separate_cycles_into_graphs(const std::vector< Cycle > &cycles);

#endif //NEGATORSUBSTITUTION_GRAPHSEPARATOR_H
