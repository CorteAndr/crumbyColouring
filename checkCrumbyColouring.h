#ifndef CHECKCRUMBYCOLOURING_H
#define CHECKCRUMBYCOLOURING_H

#include "PARAMETERS.h"

bool checkCrumbyColouring(int numberOfVertices, std::vector<std::bitset<MAX_VERTICES>> adjacencyList,
    int nb_assignedVertices, std::bitset<MAX_VERTICES> blueVertices, std::bitset<MAX_VERTICES> redVertices);

#endif //CHECKCRUMBYCOLOURING_H
