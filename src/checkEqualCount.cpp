#include "naiveCrumbyColouring.h"
#include "prunedCrumbyColouring.h"

int main() {
    auto t_start = std::chrono::high_resolution_clock::now();
    std::vector<std::bitset<MAX_VERTICES>> adjacencyList;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    long long numberOfGraphsRead = 0;
    long numEqualResults = 0;

    while (getline(std::cin, line)) {
        std::bitset<MAX_VERTICES> blueVertices, redVertices = std::bitset<MAX_VERTICES>();
        numberOfGraphsRead++;
        int n = getNumberOfVertices(line);
        loadGraph(line, n, adjacencyList);
        auto t1 = std::chrono::high_resolution_clock::now();
        int naiveCount = countNaiveCrumbyColourings(n, adjacencyList, 0, blueVertices, redVertices);
        blueVertices.reset();
        redVertices.reset();

        std::bitset<MAX_VERTICES> unassignedVertices = std::bitset<MAX_VERTICES>();
        for (int i=0; i<n; i++) {
            unassignedVertices.set(i);
        }

        int prunedCount = countPrunedCrumbyColourings(n, adjacencyList, unassignedVertices, blueVertices, redVertices);
        if (naiveCount == prunedCount)
        {
           numEqualResults++;
        } else {
            std::cout << line << " " << naiveCount << " " << prunedCount << std::endl;
        }

    }
}