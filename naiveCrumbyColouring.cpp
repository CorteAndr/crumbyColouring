// ReSharper disable CppDFAConstantConditions
// ReSharper disable CppDFAUnreachableCode


#include "graphLoader.h"
#include "checkCrumbyColouring.h"


bool naiveCrumbyColouring(const int numberOfVertices, std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const int nb_assignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices) {
    // Recursively check if colouring a vertex blue or red will result in a crumby colouring
    if (nb_assignedVertices == numberOfVertices) {
        return checkCrumbyColouring(numberOfVertices, adjacencyList, blueVertices, redVertices);
    }

    blueVertices.set(nb_assignedVertices); // nb_assignedVertices is next unused vertex
    if (naiveCrumbyColouring(numberOfVertices, adjacencyList, nb_assignedVertices + 1, blueVertices, redVertices)) {
        return true;
    }
    blueVertices.reset(nb_assignedVertices);

    redVertices.set(nb_assignedVertices);
    if (naiveCrumbyColouring(numberOfVertices, adjacencyList, nb_assignedVertices + 1, blueVertices, redVertices)) {
        return true;
    }
    redVertices.reset(nb_assignedVertices);
    return false;
}


int n;

std::vector<std::bitset<MAX_VERTICES>> adjacencyList;
std::bitset<MAX_VERTICES> blueVertices, redVertices;


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    long long numberOfGraphsRead = 0;
    int number_of_crumby_colourable_graphs = 0;

    while (getline(std::cin, line)) {
        numberOfGraphsRead++;
        n = getNumberOfVertices(line);
        loadGraph(line, n, adjacencyList);
        if (naiveCrumbyColouring(n, adjacencyList, 0, blueVertices, redVertices)) {
            number_of_crumby_colourable_graphs++;
        }
    }

    std::cout << number_of_crumby_colourable_graphs << "/" << numberOfGraphsRead << " Admit a crumby colouring" << std::endl;

    return 0;
}