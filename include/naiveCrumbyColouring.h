//
// Created by andrew on 11/11/24.
//

#ifndef NAIVECRUMBYCOLOURING_H
#define NAIVECRUMBYCOLOURING_H

#include "graphLoader.h"

int countNaiveCrumbyColourings(int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    int nb_assignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices);

bool hasNaiveCrumbyColouring(int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    int nb_assignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices);

#endif //NAIVECRUMBYCOLOURING_H
