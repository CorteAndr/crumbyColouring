// ReSharper disable CppDFAConstantConditions

// ReSharper disable CppDFAUnreachableCode
#include "graphLoader.h"

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

    adjacencyList.reserve(numberOfVertices);
    for (int vertex = 0; vertex < numberOfVertices; vertex++) { // Initialize adjacencyList
        adjacencyList[vertex] = std::bitset<MAX_VERTICES>(0);
    }

    int currVertex = 1;
    int sum = 0;
    for (int index = startIndex; index < graphString.size(); index++) {
        for (int i = prev(graphString[index] - 63, 6); i != -1; i = prev(graphString[index] - 63, i)) {
            while (5-i + (index - startIndex)*6 - sum >= 0) {
                sum += currVertex;
                currVertex++;
            }
            sum -= --currVertex;
            const int neighbour = 5-i+(index - startIndex)*6 - sum;
            adjacencyList[currVertex].set(neighbour);
            adjacencyList[neighbour].set(currVertex);
        }
    }
}
