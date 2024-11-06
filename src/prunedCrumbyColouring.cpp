#include <bitset>
#include <vector>

#include "graphLoader.h"
#include "checkCrumbyColouring.h"
#include "prunedCrumbyColouring.h"


using namespace std;

unsigned int findMostConstrainingVertex(const int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    const bitset<MAX_VERTICES> unassignedVertices) {

    unsigned int w = 0, constraining_value = 0;
    for (unsigned int v = unassignedVertices._Find_first(); v < numberOfVertices; v = unassignedVertices._Find_next(v)) {
        // constraining_value = (for now) degree in subgraph of unassignedVertices
        unsigned int degree = (adjacencyList[v] & unassignedVertices).count();
        if (degree > constraining_value) {
            constraining_value = degree;
            w = v;
        }
    }
    return w;
}

int findLeastConstrainingVertex();


int colourVertexBlue(uint vertex, int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    bitset<MAX_VERTICES> unassignedVertices, bitset<MAX_VERTICES> blueVertices, bitset<MAX_VERTICES> redVertices) {

    unassignedVertices.reset(vertex);

    // Check if possible problems with blue vertices
    uint blueNeighbourCount = (adjacencyList[vertex] & blueVertices).count();
    if (blueNeighbourCount == 0) {
        blueVertices.set(vertex);
    } else if (blueNeighbourCount == 1) {
        blueVertices.set(vertex);
        const uint w = (adjacencyList[vertex] & blueVertices)._Find_first(); // The blue neighbour of vertex

        if  ((adjacencyList[w] & blueVertices).count() > 1)
            return 0;

        // Colour all unassigned neighbours of vertex and w red
        const bitset<MAX_VERTICES> adjacentUnassigned = (adjacencyList[vertex] | adjacencyList[w]) & unassignedVertices;
        unassignedVertices &= ~adjacentUnassigned; // Remove from unassigned
        redVertices |= adjacentUnassigned; // Colour red

        // Check if w has any isolated red neighbours
        if (hasIsolatedRedNeighbour(w, numberOfVertices, adjacencyList, blueVertices, redVertices))
            return 0;
    } else {
        return 0;
    }
    // Check if vertex has any isolated red neighbours
    if (hasIsolatedRedNeighbour(vertex, numberOfVertices, adjacencyList, blueVertices, redVertices))
        return 0;

    return prunedCrumbyColouring(numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);
}


int colourVertexRed(uint vertex, int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    bitset<MAX_VERTICES> unassignedVertices, bitset<MAX_VERTICES> blueVertices, bitset<MAX_VERTICES> redVertices) {

    unassignedVertices.reset(vertex);
    redVertices.set(vertex);
    if (!checkVertex(vertex, numberOfVertices, adjacencyList, blueVertices, redVertices))
        return 0;

    return prunedCrumbyColouring(numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);
}


int prunedCrumbyColouring(const int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    bitset<MAX_VERTICES> unassignedVertices, bitset<MAX_VERTICES> blueVertices, bitset<MAX_VERTICES> redVertices) {

    if (unassignedVertices.count() + blueVertices.count() + redVertices.count() < numberOfVertices)
        // Every vertex must be colourable
        return false;

    if (unassignedVertices.any()) { // Check for any unassigned vertices

        // Better next choice vertex?
        uint v = findMostConstrainingVertex(numberOfVertices, adjacencyList, unassignedVertices);

        // Colour v blue
        int blueV = colourVertexBlue(v, numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);

        int redV = colourVertexRed(v, numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);

        return blueV + redV;
    }

    return checkCrumbyColouring(numberOfVertices, adjacencyList, blueVertices, redVertices);
}

int main() {
    std::vector<std::bitset<MAX_VERTICES>> adjacencyList;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    long long numberOfGraphsRead = 0;
    int number_of_crumby_colourable_graphs = 0;

    while (getline(std::cin, line)) {
        std::bitset<MAX_VERTICES> blueVertices, redVertices;
        numberOfGraphsRead++;
        int n = getNumberOfVertices(line);
        loadGraph(line, n, adjacencyList);

        if (prunedCrumbyColouring(n, adjacencyList, 0, blueVertices, redVertices)) {
            number_of_crumby_colourable_graphs++;
        }
    }

    std::cout << number_of_crumby_colourable_graphs << "/" << numberOfGraphsRead << " Admit a crumby colouring" << std::endl;

    return 0;
}