#ifndef CHECKCRUMBYCOLOURING_H
#define CHECKCRUMBYCOLOURING_H

#include "graphLoader.h"

#include <bits/stdc++.h>

// Checker for full
bool checkCrumbyColouring(int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices);


bool checkVertex(uint vertex, int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices);

bool hasIsolatedRedNeighbour(uint vertex, int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices);

bool isIsolatedRed(uint vertex, int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices);

#endif //CHECKCRUMBYCOLOURING_H
