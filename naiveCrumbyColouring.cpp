// ReSharper disable CppDFAConstantConditions
// ReSharper disable CppDFAUnreachableCode


#include <bits/stdc++.h>

#include "PARAMETERS.h"
#include "checkCrumbyColouring.h"

// Unsafe because no defined behaviour if character = 0. ctz and clz work with 32 bit numbers.
#define unsafePrev(character, current) (__builtin_ctz(character) - current >= 0 ? -1 : current -__builtin_clz((character) << (32 - current)) - 1)

#define prev(character,current) (character ? unsafePrev(character,current) : -1)


int getNumberOfVertices(const std::string &graphString) {
    if (graphString.empty()) {
        printf("Error: String is empty.\n");
        abort();
    }
    if ((graphString[0] < 63 || graphString[0] > 126) && graphString[0] != '>') {
        printf("Error: Invalid start of graphString.\n");
        abort();
    }

    int index = 0;
    if (graphString[index] == '>') { // Skip >>graph6<< header
        index += 10;
    }

    if (graphString[index] < 126) { // 0 <= N <= 62
        return (graphString[index] - 63);
    }

    int i;
    if (graphString[++index] < 126) {
        i = 2;
    }
    else if (graphString[++index] < 126) {
        i = 5;
    } else {
        printf("Error: Exceeded number of vertices allowed in format");
        abort();
    }

    int number = 0;
    for (; i >= 0; i--) {
        number |= (graphString[index++] - 63 ) << i*6;
    }
    return number;
}

void loadGraph(const std::string &graphString, int numberOfVertices, std::vector<std::bitset<MAX_VERTICES>> &adjacencyList) {
    int startIndex = 0;

    if (graphString[startIndex] == '>') { // Skip >>graph6<< header
        startIndex += 10;
    }
    if (numberOfVertices < 63) {
        startIndex += 1;
    } else if (numberOfVertices <= MAX_VERTICES) {
        startIndex += 4;
    } else {
        printf("Error: Program can only handle graphs with %d or less vertices ", MAX_VERTICES);
        abort();
    }

    for (int vertex = 0; vertex < numberOfVertices; vertex++) { // Initialize adjacencyList
        adjacencyList.emplace_back();
    }

    int currVertex = 1;
    int sum = 0;
    for (int index = startIndex; index < graphString.size(); index++) {
        for (int i = prev(graphString[index] - 63, 6); i != -1; i = prev(graphString[index], i)) {
            while (5-i + (index - startIndex)*6 - sum >= 0) {
                sum += currVertex;
                currVertex++;
            }
            sum -= currVertex;
            const int neighbour = 5-i+(index - startIndex)*6 - sum;
            adjacencyList[currVertex].set(neighbour);
            adjacencyList[neighbour].set(currVertex);
        }
    }
}


int naiveCrumbyColouring(const int numberOfVertices, std::vector<std::bitset<MAX_VERTICES>> &adjacencyList,
    const int nb_assignedVertices, std::bitset<MAX_VERTICES> &blueVertices, std::bitset<MAX_VERTICES> &redVertices) {
    // Recursively check if colouring a vertex blue or red will result in a crumby colouring
    if (nb_assignedVertices == numberOfVertices) {
        return checkCrumbyColouring(numberOfVertices, adjacencyList, nb_assignedVertices, blueVertices, redVertices);
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
    int numberOfFoundCrumbyColourings = 0;

    while (getline(std::cin, line)) {
        numberOfGraphsRead++;
        n = getNumberOfVertices(line);
        loadGraph(line, n, adjacencyList);
        if (naiveCrumbyColouring(n, adjacencyList, 0, blueVertices, redVertices)) {
            numberOfFoundCrumbyColourings++;
        }
    }

    std::cout << numberOfFoundCrumbyColourings << "/" << numberOfGraphsRead << " Admit a crumby colouring" << std::endl;

    return 0;
}