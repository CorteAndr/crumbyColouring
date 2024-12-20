// ReSharper disable CppDFAConstantConditions
// ReSharper disable CppDFAUnreachableCode


#include "naiveCrumbyColouring.h"
#include "checkCrumbyColouring.h"


int countNaiveCrumbyColourings(const int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const int nb_assignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices) {
    // Recursively check if colouring a vertex blue or red will result in a crumby colouring
    if (nb_assignedVertices == numberOfVertices) {
        return checkCrumbyColouring(numberOfVertices, adjacencyList, blueVertices, redVertices);
    }

    blueVertices.set(nb_assignedVertices); // nb_assignedVertices is next unused vertex

    int blueV = countNaiveCrumbyColourings(numberOfVertices, adjacencyList, nb_assignedVertices + 1,
        blueVertices, redVertices);
    blueVertices.reset(nb_assignedVertices);

    redVertices.set(nb_assignedVertices);
    int redV = countNaiveCrumbyColourings(numberOfVertices, adjacencyList, nb_assignedVertices + 1,
        blueVertices, redVertices);
    redVertices.reset(nb_assignedVertices);

    return blueV + redV;
}


bool hasNaiveCrumbyColouring(int numberOfVertices, const std::vector<std::bitset<48> > &adjacencyList,
    int nb_assignedVertices, std::bitset<48> &blueVertices, std::bitset<48> &redVertices) {

    if (nb_assignedVertices == numberOfVertices) {
        return checkCrumbyColouring(numberOfVertices, adjacencyList, blueVertices, redVertices);
    }

    blueVertices.set(nb_assignedVertices);
    if (hasNaiveCrumbyColouring(numberOfVertices, adjacencyList, nb_assignedVertices + 1, blueVertices, redVertices)) {
        return true;
    }
    blueVertices.reset(nb_assignedVertices);

    redVertices.set(nb_assignedVertices);
    if (hasNaiveCrumbyColouring(numberOfVertices, adjacencyList, nb_assignedVertices + 1, blueVertices, redVertices)) {
        return true;
    }
    redVertices.reset(nb_assignedVertices);
    return false;
}
