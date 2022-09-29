#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <DataStructures/WeightedEdge.h>

template <class T>
class WeightedGraph
{
private:
    std::set<int> vertices;
    std::map<int, std::vector<WeightedEdge<T>>> edges;

public:
    WeightedGraph();
    ~WeightedGraph();

public:
    bool AddVertex(int vertex);
    bool RemoveVertex(int vertex);
    virtual bool AddEdge(int vertex1, int vertex2, T weight);
    virtual bool RemoveEdge(int vertex1, int vertex2);

public:
    int CountVertices() const;
    virtual int CountEdges() const;
    bool ContainsVertex(int vertex) const;
    bool ContainsEdge(int vertex1, int vertex2) const;
    T GetWeight(int vertex1, int vertex2) const;
    std::vector<int> GetVertices() const;
    virtual std::vector<WeightedEdge<T>> GetEdges() const;
    std::vector<WeightedEdge<T>> GetIncomingEdges(int vertex) const;
    std::vector<WeightedEdge<T>> GetOutgoingEdges(int vertex) const;
    virtual int GetDegree(int vertex) const;
    std::vector<int> GetNeighbors(int vertex) const;
};

#endif
