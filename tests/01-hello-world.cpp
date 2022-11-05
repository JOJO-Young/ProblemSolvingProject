#include <Algorithms/DijkstraShortestPaths.h>
#include <DataStructures/WeightedGraph.h>
#include <DataStructures/UndirectedWeightedGraph.h>
#include <stdio.h>
using namespace std;
int main()
{
    auto *g = new UndirectedWeightedGraph<int>();
    for (int i = 1; i <= 6; ++i)
    {
        g->AddVertex(i);
    }
    g->AddEdge(1, 2, 1);
    g->AddEdge(2, 3, 9);
    g->AddEdge(1, 3, 3);
    g->AddEdge(3, 4, 1);
    g->AddEdge(1, 4, 4);
    g->AddEdge(4, 1, 4);
    g->AddEdge(5, 6, 5);
    g->AddEdge(6, 1, 2);

    ShortestPaths<UndirectedWeightedGraph, int> *p = nullptr;
    for (int i = 1; i <= 6; ++i)
    {
        p = new DijkstraShortestPaths<UndirectedWeightedGraph, int>(g, i);
        for (int j = 1; j <= 6; ++j)
        {
            if (j > 1)
                printf(",");
            const auto o_path = p->TryGetShortestPathTo(j);
            if (o_path.has_value())
            {
                int distance = 0;
                const auto &path = o_path.value();
                for (int k = 1; k < path.size(); ++k)
                {
                    distance += g->GetWeight(path[k - 1], path[k]);
                    printf("yzy%d\n", path[k - 1]);
                }
                printf("%d", distance);
            }
            else
            {
                printf("-1");
            }
        }
        printf("\n");
        delete p;
    }
    delete g;
}