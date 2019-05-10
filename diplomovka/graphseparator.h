#pragma once
#ifndef GRAPHSEPARATOR_H
#define GRAPHSEPARATOR_H

#include "common.h"

std::shared_ptr< std::vector< CycledGraph > > separate_cycles_into_graphs(const std::vector< Cycle > &cycles);

#endif //BAKALARKA_GRAPHSEPARATOR_H
