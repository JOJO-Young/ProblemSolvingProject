#ifndef UNDIRECTEDWEIGHTEDGRAPH_H
#define UNDIRECTEDWEIGHTEDGRAPH_H

#include <DataStructures/WeightedGraph.h>

template <class T>
class UndirectedWeightedGraph:public WeightedGraph<T>
{
private:
    int num_selfring;
    std::map<int, int> vertex_to_selfring;

public:
    UndirectedWeightedGraph();
    ~UndirectedWeightedGraph();

public:
    bool AddEdge(int vertex1, int vertex2, T weight);
    bool RemoveEdge(int vertex1, int vertex2);

public:
    int CountEdges() const override;
    std::vector<WeightedEdge<T>> GetEdges() const override;
    int GetDegree(int vertex) const override;


};

#endif