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

// False iff that vertex causes for an impossible constraint
bool checkVertex(uint vertex, int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices) {
    if (blueVertices.test(vertex)) {
        // vertex is blue
        if ((adjacencyList[vertex] & blueVertices).count() > 1)
            return false;
        if (hasIsolatedRedNeighbour(vertex, numberOfVertices, adjacencyList, blueVertices, redVertices))
            return false;

        return true;

    }
    if (redVertices.test(vertex)) {
        // vertex is red
        const std::bitset<MAX_VERTICES> redInducedAdjacency = redVertices & adjacencyList[vertex];

        switch (redInducedAdjacency.count()) {
            case 0:
                return !isIsolatedRed(vertex, numberOfVertices, adjacencyList, blueVertices, redVertices);
            case 1:
                return true;
            case 2:
                for (unsigned int w = redInducedAdjacency._Find_first();
                       w < numberOfVertices;
                       w = redInducedAdjacency._Find_next(w)) {

                    if ((redVertices & (~adjacencyList[vertex] & adjacencyList[w])).count() != 1) {
                        // Red neighbours not of vertex that are neighbours of w can only be vertex
                        return false;
                    }
                       }
                break;
            default:
                for (uint w = redInducedAdjacency._Find_first();
                    w < numberOfVertices;
                    w = redInducedAdjacency._Find_next(w)) {

                    if ((redVertices & adjacencyList[w]).count() > 1)
                        return false;
                }
        }
    }
    return true;
}

bool hasIsolatedRedNeighbour(uint vertex, int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices) {
    if (blueVertices.test(vertex)) {
        const std::bitset<MAX_VERTICES> redNeighbours = redVertices & adjacencyList[vertex];

        for (uint w = redNeighbours._Find_first();
            w < numberOfVertices;
            w = redNeighbours._Find_next(w)) {

            if (isIsolatedRed(w, numberOfVertices, adjacencyList, blueVertices, redVertices))
                return true;
        }
    }
    return false;
}

bool isIsolatedRed(uint vertex, int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices) {
    if (redVertices.test(vertex)) {
        return adjacencyList[vertex] == blueVertices; // vertex has no neighbours that are not blue
    }
    printf("Error: Vertex %d is not coloured red", vertex);
    abort();
}

