#include "checkCrumbyColouring.h"
#include "prunedCrumbyColouring.h"


using namespace std;

unsigned int findMostConstrainingVertex(const int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    const bitset<MAX_VERTICES> &unassignedVertices) {

    uint w = unassignedVertices._Find_first();
    uint constraining_value = (adjacencyList[w] & unassignedVertices).count();

    for (unsigned int v = unassignedVertices._Find_next(w); v < numberOfVertices; v = unassignedVertices._Find_next(v)) {
        // constraining_value = (for now) degree in subgraph of unassignedVertices
        unsigned int degree = (adjacencyList[v] & unassignedVertices).count();
        if (degree < constraining_value) {
            constraining_value = degree;
            w = v;
        }
    }
    return w;
}

int findLeastConstrainingVertex();


int colourVertexBlue(uint vertex, int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    bitset<MAX_VERTICES> &unassignedVertices, bitset<MAX_VERTICES> &blueVertices, bitset<MAX_VERTICES> &redVertices)
{


    // Check if possible problems with blue vertices
    uint blueNeighbourCount = (adjacencyList[vertex] & blueVertices).count();

    if (blueNeighbourCount == 0) {

        unassignedVertices.reset(vertex);
        blueVertices.set(vertex);
        if (hasIsolatedRedNeighbour(vertex, numberOfVertices, adjacencyList, blueVertices, redVertices))
        {
            blueVertices.reset(vertex);
            unassignedVertices.set(vertex);
            return 0;
        }

        int blueV = prunedCrumbyColouring(numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);
        blueVertices.reset(vertex);
        unassignedVertices.set(vertex);
        return blueV;


    }
    if (blueNeighbourCount == 1) {

        unassignedVertices.reset(vertex);
        blueVertices.set(vertex);
        const uint w = (adjacencyList[vertex] & blueVertices)._Find_first(); // The blue neighbour of vertex

        if  ((adjacencyList[w] & blueVertices).count() > 1)
        {
            blueVertices.reset(vertex);
            unassignedVertices.set(vertex);
            return 0;
        }
        // Colour all unassigned neighbours of vertex and w red
        bitset<MAX_VERTICES> adjacentUnassigned = (adjacencyList[vertex] | adjacencyList[w]) & unassignedVertices;
        redVertices |= adjacentUnassigned; // Colour red
        unassignedVertices &= ~adjacentUnassigned; // Remove from unassigned


        // Check if vertex or w has any isolated red neighbours
        if (hasIsolatedRedNeighbour(vertex, numberOfVertices, adjacencyList, blueVertices, redVertices) ||
            hasIsolatedRedNeighbour(w, numberOfVertices, adjacencyList, blueVertices, redVertices))
        {
            blueVertices.reset(vertex);
            unassignedVertices.set(vertex);
            return 0;
        }

        int blueV = prunedCrumbyColouring(numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);
        blueVertices.reset(vertex);
        unassignedVertices.set(vertex);

        unassignedVertices |= adjacentUnassigned;
        redVertices &= ~adjacentUnassigned;

        return blueV;

    }

    blueVertices.reset(vertex);
    unassignedVertices.set(vertex);
    return 0;
}


int colourVertexRed(uint vertex, int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    bitset<MAX_VERTICES> &unassignedVertices, bitset<MAX_VERTICES> &blueVertices, bitset<MAX_VERTICES> &redVertices)
{
    unassignedVertices.reset(vertex);
    redVertices.set(vertex);

    if (!checkVertex(vertex, numberOfVertices, adjacencyList, blueVertices, redVertices))
    {
        unassignedVertices.set(vertex);
        redVertices.reset(vertex);
        return 0;
    }

    int redV = prunedCrumbyColouring(numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);

    unassignedVertices.set(vertex);
    redVertices.reset(vertex);

    return redV;
}


int prunedCrumbyColouring(const int numberOfVertices, const vector<bitset<MAX_VERTICES>> &adjacencyList,
    bitset<MAX_VERTICES> &unassignedVertices, bitset<MAX_VERTICES> &blueVertices, bitset<MAX_VERTICES> &redVertices) {

    if (unassignedVertices.count() + blueVertices.count() + redVertices.count() < numberOfVertices)
    {
        // Every vertex must be colourable
        return 0;
    }

    if (unassignedVertices.any()) { // Check for any unassigned vertices
        // Better next choice vertex?
        uint v = findMostConstrainingVertex(numberOfVertices, adjacencyList, unassignedVertices);

        // Colour v
        int blueV = colourVertexBlue(v, numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);

        int redV = colourVertexRed(v, numberOfVertices, adjacencyList, unassignedVertices, blueVertices, redVertices);

        return blueV + redV;
    }

    if(checkCrumbyColouring(numberOfVertices, adjacencyList, blueVertices, redVertices))
        return 1;

    return 0;
}