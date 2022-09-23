#ifndef UNDIRECTEDWEIGHTEDGRAPH_H
#define UNDIRECTEDWEIGHTEDGRAPH_H

#include <DataStructures/WeightedGraph.h>

class UndirectedWeightedGraph:public WeightedGraph
{
private:
    int num_selfring;
    std::map<int, int> vertex_to_selfring;

public:
    UndirectedWeightedGraph();
    ~UndirectedWeightedGraph();

public:
    bool AddEdge(int vertex1, int vertex2, int weight);
    bool RemoveEdge(int vertex1, int vertex2);

public:
    int CountEdges() const override;
    std::vector<WeightedEdge> GetEdges() const override;
    int GetDegree(int vertex) const override;


};
#endif