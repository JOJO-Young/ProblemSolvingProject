#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include <DataStructures/Graph.h>

class UndirectedGraph:public Graph
{
private:
    int num_selfring;
    std::map<int, int> vertex_to_selfring;

public:
    UndirectedGraph();
    ~UndirectedGraph();

public:
    bool AddEdge(int vertex1, int vertex2) override;
    bool RemoveEdge(int vertex1, int vertex2) override;

public:
    int CountEdges() const override;
    std::vector<Edge> GetEdges() const override;
    int GetDegree(int vertex) const override;
    
};
#endif
