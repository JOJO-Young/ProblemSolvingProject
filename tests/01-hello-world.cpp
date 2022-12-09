#include <Algorithms/DijkstraShortestPaths.h>
#include <DataStructures/WeightedGraph.h>
#include <DataStructures/UndirectedWeightedGraph.h>
#include <Algorithms/BellmanFordShortestPaths.h>
#include <Algorithms/FloydShortestPaths.h>
#include <stdio.h>
using namespace std;
int main()
{
    // auto *g = new WeightedGraph<int>();
    // for (int i = 1; i <= 4; ++i)
    // {
    //     g->AddVertex(i);
    // }
    // g->AddEdge(1, 2, -2);
    // g->AddEdge(2, 4, -1);
    // g->AddEdge(1, 4, 0);
    // g->AddEdge(4, 1, 4);
    // g->AddEdge(1, 3, -4);
    // g->AddEdge(3, 4, 100);
    // MultiSourceShortestPaths<WeightedGraph<int>> *p = nullptr;
    // p = new FloydShortestPaths<WeightedGraph<int>>(g);
    // for (int i = 1; i <= 4; ++i)
    // {
    //     for (int j = 1; j <= 4; ++j)
    //     {
    //         // if (j > 1)
    //         //     printf(",");
    //         const auto o_path = p->TryGetShortestPathOf(i, j);
    //         if (o_path.has_value())
    //         {
    //             int distance = 0;
    //             const auto &path = o_path.value();
    //             // for (int k = 1; k < path.size(); ++k)
    //             //     distance += g->GetWeight(path[k - 1], path[k]);
    //             for (int k = 0; k < path.size(); k++)
    //                 printf("%d ", path[k]);
    //             // printf("%d", distance);
    //         }
    //         else
    //             printf("-1");
    //         printf("\n");
    //     }
    // }
    // printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    // ShortestPaths<WeightedGraph<int>> *q = nullptr;
    // for (int i = 1; i <= 4; ++i)
    // {
    //     q = new BellmanFordShortestPaths<WeightedGraph<int>>(g, i);
    //     for (int j = 1; j <= 4; ++j)
    //     {
    //         // if (j > 1)
    //         //     printf(",");
    //         const auto o_path = q->TryGetShortestPathTo(j);
    //         if (o_path.has_value())
    //         {
    //             int distance = 0;
    //             const auto &path = o_path.value();
    //             // for (int k = 1; k < path.size(); ++k)
    //             //     distance += g->GetWeight(path[k - 1], path[k]);
    //             // printf("%d", distance);
    //             for (int k = 0; k < path.size(); k++)
    //                 printf("%d ", path[k]);
    //         }
    //         else
    //             printf("-1");
    //         printf("\n");
    //     }
    // }
    auto *g = new UndirectedWeightedGraph<double>();
    for (int i = 1; i <= 4; ++i)
    {
        g->AddVertex(i);
    }
    g->AddEdge(1, 1, -1e-6);
    try
    {
        MultiSourceShortestPaths<UndirectedWeightedGraph<double>> *p = nullptr;
        p = new FloydShortestPaths<UndirectedWeightedGraph<double>>(g);
    }
    catch (NegativeCycleException &e)
    {
        cout << e;
    }
}