#include <bits/stdc++.h>
#include "checkCrumbyColouring.h"

bool checkCrumbyColouring(const int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices) {

    for (int v = 0; v < numberOfVertices; v++) {
        if (blueVertices.test(v)) {
            // v is coloured blue
            if ((blueVertices & adjacencyList[v]).count() > 1) return false;
        } else if (redVertices.test(v)) {
            // v is coloured red
            std::bitset<MAX_VERTICES> redInducedAdjacency = redVertices & adjacencyList[v];
            switch (redInducedAdjacency.count()) {
                case 0:
                    return false;
                case 1:
                    break;
                case 2: // V or Triangle
                    for (unsigned int w = redInducedAdjacency._Find_next(v); // Everything before v is already checked
                        w < numberOfVertices;
                        w = redInducedAdjacency._Find_next(w)) {

                        if ((redVertices & (~adjacencyList[v] & adjacencyList[w])).count() != 1) {
                            // Red neighbours not of v that are neighbours of w can only be v
                            return false;
                        }
                    }
                    break;

                default: // Degrees 3 or higher require star-shape
                    for (unsigned w = redInducedAdjacency._Find_next(v); // Everything before v is already checked
                        w < numberOfVertices;
                        w = redInducedAdjacency._Find_next(w)) {

                        if ((redVertices & adjacencyList[w]).count() > 1) return false;
                }
            }
        }
    }

    return true;
}