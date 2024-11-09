#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H

#include <bits/stdc++.h>

#define MAX_VERTICES 32

// Unsafe because no defined behaviour if character = 0. ctz and clz work with 32bit numbers.
#define unsafePrev(character, current) (__builtin_ctz(character) - current >= 0 ? -1 : current -__builtin_clz((character) << (32 - current)) - 1)

#define prev(character,current) (character ? unsafePrev(character,current) : -1)


int getNumberOfVertices(const std::string &graphString);

void loadGraph(const std::string &graphString, int numberOfVertices, std::vector<std::bitset<MAX_VERTICES>> &adjacencyList);


#endif // GRAPHLOADER_H
