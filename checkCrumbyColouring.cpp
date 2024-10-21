#include <bits/stdc++.h>
#include "checkCrumbyColouring.h"

bool checkCrumbyColouring(const int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
const std::bitset<MAX_VERTICES> &blueVertices, const std::bitset<MAX_VERTICES> &redVertices) {

    u_long bitsetL;
    int w;
    for (int v = 0; v < numberOfVertices; v++) {
        if (blueVertices.test(v)) {
            // v is coloured blue
            if ((blueVertices & adjacencyList[v]).count() > 1) return false;
        } else {
            // v is coloured red
            std::bitset<MAX_VERTICES> redInducedAdjacency = redVertices & adjacencyList[v];
            switch (redInducedAdjacency.count()) {
                case 0:
                    return false;
                case 1:
                    break;
                case 2:
                    bitsetL = redInducedAdjacency.to_ulong();
                while (bitsetL) { // Neighbour iteration for sparse bitset
                    w = __builtin_ctzl(bitsetL);
                    if ((redVertices & adjacencyList[w]).count() <= 2) { // V or Triangle
                        // No neighbours of w aren't neighbours of v
                        if ((~(redVertices & adjacencyList[v]) & (redVertices & adjacencyList[w])).any()) return false;
                    }
                    bitsetL = bitsetL & (bitsetL - 1);
                }
                break;
                case 3:
                    bitsetL = (redVertices & adjacencyList[v]).to_ulong();
                while (bitsetL) { // Neighbour iteration for sparse bitset
                    w = __builtin_ctzl(bitsetL); // Neighbour of v
                    if ((redVertices & adjacencyList[w]).count() > 1) return false;
                    bitsetL = bitsetL & (bitsetL - 1);
                }
                break;
                default:
                    printf("Error: Not a sub-cubic graph");
                abort();
            }
        }
    }

    return true;
}