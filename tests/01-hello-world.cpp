#include <Algorithms/DijkstraShortestPaths.h>
#include <DataStructures/WeightedGraph.h>
#include <stdio.h>
using namespace std;
int main()
{
    auto *g = new WeightedGraph<int>();
    for (int i = 1; i <= 6; ++i)
    {
        g->AddVertex(i);
    }
    g->AddEdge(1, 2, 1);
    g->AddEdge(2, 3, 2);
    g->AddEdge(3, 4, 3);
    g->AddEdge(4, 1, 4);
    g->AddEdge(5, 6, 5);
    g->AddEdge(6, 5, 6);

    ShortestPaths<WeightedGraph, int> *p = nullptr;
    for (int i = 1; i <= 6; ++i)
    {
        p = new DijkstraShortestPaths<WeightedGraph, int>(g, i);
        for (int j = 1; j <= 6; ++j)
        {
            // printf("%d", p->HasPathTo(j));
            if (p->TryGetShortestPathTo(j).has_value())
            {
                for (auto x : p->TryGetShortestPathTo(j).value())
                    printf("%d\n", x);
            }
            printf("\n");
            delete p;
        }
        delete g;
    }