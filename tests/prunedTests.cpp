#include <gtest/gtest.h>
#include "prunedCrumbyColouring.h"
#include "naiveCrumbyColouring.h"

TEST(PrunedTest, ThomasBellittoCounterExample)
{
    std::bitset<MAX_VERTICES> blueVertices, redVertices, unassignedVertices;
    std::vector<std::bitset<MAX_VERTICES>> adjacencyList;

    std::string graph = "oqKoOKA?W@?A?B?B??O?B??G??G??O??G??B???o??@???B???A???@_???O???@????C????G???@G???Ac??O????@??G????@?????A?????B?????B??????O?????B??????G??????W??????O??????G??????B???????o??????@???????B";

    int n = getNumberOfVertices(graph);
    loadGraph(graph, n, adjacencyList);

    for (int i=0; i < n; i++)
        unassignedVertices.set(i);

    EXPECT_FALSE(prunedCrumbyColouring(n, adjacencyList, unassignedVertices, blueVertices, redVertices));
}

TEST(PrunedTest, equalsNaiveForSubCubicBipartiteGraphs)
{
    // Graphs found in HouseOfGraphs of sub-cubic connected bipartite graphs
    std::vector<std::string> graphs{"N????????@`aKOOoOS?","N????GA??OE@?EoC?KO","N?????A@?_C@ADOQOK?",
        "N???G?G?GAa?G@O_oG_", "N?CGGC@?G?_@?@G?y??", "N???GG??OOaCG_OGR??", "R???????OC???@B?W?@`??AG?aG?i?",
        "O????????a`E@ce?CSAI?", "O?GO?@?_@CAG@AA@?IGDC", "N????GAOC?ACGOBA@Q?", "O???OG@?_?_CC@GAH?CG@",
        "O???`?CA???@_GOC?GoCQ", "R??????_@?G?C_@O@C????cC@CO@O_", "O?????GCCGCOOO@??QGBA", "N??_??OAA?O`?q?o?EG",
        "O?????G?_GG?GACPOA_BC", "O????GA?GA@@CCH?GOCo?", "N???????G@WAAQ@aEA?", "O?????@?`?A?@AA@gBC@G",
        "O????A??WDG?C@G@@AOGQ", "O@???CCQ?_@_?Q?H?O\\?O", "Q???????GA?_?_G?@?g_EOBA?Q?",
        "S?????????_C?_?OA?@?@@?cG@a?KC?Q?", "S???????C??B?IO?A?H?AA?GC?OACOCGG", "S@??G?@???h?C?B??GOCA?GG?GO?_\\?C?"};

    for (const std::string& graph: graphs)
    {
        std::bitset<MAX_VERTICES> blueVertices, redVertices, unassignedVertices = std::bitset<MAX_VERTICES>();
        std::vector<std::bitset<MAX_VERTICES>> adjacencyList;

        int n = getNumberOfVertices(graph);
        loadGraph(graph, n, adjacencyList);

        for (int i=0; i < n; i++)
            unassignedVertices.set(i);

        int pruned = prunedCrumbyColouring(n, adjacencyList, unassignedVertices, blueVertices, redVertices);
        int naive = naiveCrumbyColouring(n, adjacencyList, 0, blueVertices, redVertices);

        // Test if pruned gives
        ASSERT_EQ(pruned, naive);
    }
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}