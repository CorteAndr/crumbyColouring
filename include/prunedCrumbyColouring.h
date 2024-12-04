#ifndef PRUNEDCRUMBYCOLOURING_H
#define PRUNEDCRUMBYCOLOURING_H

#include "graphLoader.h"

int countPrunedCrumbyColourings(int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    std::bitset<MAX_VERTICES> &unassignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices);

bool hasPrunedCrumbyColouring(int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    std::bitset<MAX_VERTICES> &unassignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices);
#endif //PRUNEDCRUMBYCOLOURING_H
