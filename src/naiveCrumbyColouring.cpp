// ReSharper disable CppDFAConstantConditions
// ReSharper disable CppDFAUnreachableCode


#include "graphLoader.h"
#include "checkCrumbyColouring.h"


int naiveCrumbyColouring(const int numberOfVertices, const std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const int nb_assignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices) {
    // Recursively check if colouring a vertex blue or red will result in a crumby colouring
    if (nb_assignedVertices == numberOfVertices) {
        return checkCrumbyColouring(numberOfVertices, adjacencyList, blueVertices, redVertices);
    }

    blueVertices.set(nb_assignedVertices); // nb_assignedVertices is next unused vertex

    int blueV = naiveCrumbyColouring(numberOfVertices, adjacencyList, nb_assignedVertices + 1,
        blueVertices, redVertices);
    blueVertices.reset(nb_assignedVertices);

    redVertices.set(nb_assignedVertices);
    int redV = naiveCrumbyColouring(numberOfVertices, adjacencyList, nb_assignedVertices + 1,
        blueVertices, redVertices);
    redVertices.reset(nb_assignedVertices);

    return blueV + redV;
}


int main() {
    auto t_start = std::chrono::high_resolution_clock::now();
    std::vector<std::bitset<MAX_VERTICES>> adjacencyList;
    std::bitset<MAX_VERTICES> blueVertices, redVertices;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    long long numberOfGraphsRead = 0;
    int number_of_crumby_colourable_graphs = 0;

    while (getline(std::cin, line)) {
        numberOfGraphsRead++;
        int n = getNumberOfVertices(line);
        loadGraph(line, n, adjacencyList);
        int num_of_colourings = naiveCrumbyColouring(n, adjacencyList, 0, blueVertices, redVertices);
        if (num_of_colourings) {
            number_of_crumby_colourable_graphs++;
            std::cout << "GRAPH: " << line << " has " << num_of_colourings << " crumby colourings\n";
        } else {
            std::cout << "GRAPH: " << line << " has no crumby colouring\n";
        }

    }

    std::cout << number_of_crumby_colourable_graphs << "/" << numberOfGraphsRead << " Graphs admit a crumby colouring in "
    << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-t_start)).count()
    << "ms" << std::endl;

    return 0;
}