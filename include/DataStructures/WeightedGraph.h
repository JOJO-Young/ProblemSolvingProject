#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <DataStructures/WeightedEdge.h>

template <typename T>
class WeightedGraph
{
private:
    std::set<int> vertices;
    std::map<int, std::vector<WeightedEdge<T>>> edges;

public:
    WeightedGraph();
    ~WeightedGraph();
    typedef T value_type; //定义一个类型名称，方便在ShortestPaths中萃取出T，这个数据类型

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

template <typename T>
WeightedGraph<T>::WeightedGraph()
{
}
template <typename T>
WeightedGraph<T>::~WeightedGraph()
{
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
template <typename T>
bool WeightedGraph<T>::AddVertex(int vertex)
{
    if (ContainsVertex(vertex))
        return false;
    vertices.insert(vertex);
    return true;
}

template <typename T>
bool WeightedGraph<T>::RemoveVertex(int vertex)
{
    std::set<int>::iterator it;
    it = vertices.find(vertex);
    if (it == vertices.end())
        return false;
    vertices.erase(it);
    return true;
}

template <typename T>
bool WeightedGraph<T>::AddEdge(int vertex1, int vertex2, T weight)
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    class std::map<int, std::vector<WeightedEdge<T>>>::iterator it = edges.find(vertex1);
    if (it == edges.end())
        edges[vertex1].push_back(WeightedEdge<T>(vertex1, vertex2, weight));
    else
    {
        for (auto x : edges[vertex1])
            if (x.GetDestination() == vertex2)
                return false;
        edges[vertex1].push_back(WeightedEdge<T>(vertex1, vertex2, weight));
    }
    return true;
}

template <typename T>
bool WeightedGraph<T>::RemoveEdge(int vertex1, int vertex2)
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    class std::map<int, std::vector<WeightedEdge<T>>>::iterator it = edges.find(vertex1);
    if (it == edges.end())
        return false;
    else
    {
        for (class std::vector<WeightedEdge<T>>::iterator i = edges[vertex1].begin(); i != edges[vertex1].end(); i++)
        {
            if (i->GetDestination() == vertex2)
            {
                edges[vertex1].erase(i);
                return true;
            }
        }
        return false;
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
template <typename T>
int WeightedGraph<T>::CountVertices() const
{
    return vertices.size();
}

template <typename T>
int WeightedGraph<T>::CountEdges() const
{
    int ans = 0;
    for (class std::map<int, std::vector<WeightedEdge<T>>>::const_iterator i = edges.begin(); i != edges.end(); i++)
        ans = ans + i->second.size();
    return ans;
}

template <typename T>
bool WeightedGraph<T>::ContainsVertex(int vertex) const
{
    if (vertices.find(vertex) == vertices.end())
        return false;
    return true;
}

template <typename T>
bool WeightedGraph<T>::ContainsEdge(int vertex1, int vertex2) const
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    class std::map<int, std::vector<WeightedEdge<T>>>::const_iterator it;
    it = edges.find(vertex1);
    if (it == edges.end())
        return false;
    for (auto x : it->second)
        if (x.GetDestination() == vertex2)
            return true;
    return false;
}

template <typename T>
T WeightedGraph<T>::GetWeight(int vertex1, int vertex2) const
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return 0;
    class std::map<int, std::vector<WeightedEdge<T>>>::const_iterator it;
    it = edges.find(vertex1);
    if (it == edges.end())
        return 0;
    for (class std::vector<WeightedEdge<T>>::const_iterator i = edges.at(vertex1).begin(); i != edges.at(vertex1).end(); i++)
        if (i->GetDestination() == vertex2)
            return i->GetWeight();
    return 0; //实际上是UB
}

template <typename T>
std::vector<int> WeightedGraph<T>::GetVertices() const
{
    std::set<int>::const_iterator it = vertices.begin();
    std::vector<int> v;
    for (; it != vertices.end(); it++)
        v.push_back(*it);
    return v;
}

template <typename T>
std::vector<WeightedEdge<T>> WeightedGraph<T>::GetEdges() const
{
    std::vector<WeightedEdge<T>> ans_v;
    class std::map<int, std::vector<WeightedEdge<T>>>::const_iterator it;
    it = edges.begin();
    for (; it != edges.end(); it++)
    {
        for (auto x : it->second)
            ans_v.push_back(x);
    }
    return ans_v;
}

template <typename T>
std::vector<WeightedEdge<T>> WeightedGraph<T>::GetIncomingEdges(int vertex) const
{
    std::vector<WeightedEdge<T>> ans_v;
    if (!ContainsVertex(vertex))
        return ans_v;
    class std::map<int, std::vector<WeightedEdge<T>>>::const_iterator it;
    it = edges.begin();
    for (; it != edges.end(); it++)
    {
        for (auto x : it->second)
            if (x.GetDestination() == vertex)
                ans_v.push_back(x);
    }
    return ans_v;
}

template <typename T>
std::vector<WeightedEdge<T>> WeightedGraph<T>::GetOutgoingEdges(int vertex) const
{
    std::vector<WeightedEdge<T>> ans_v;
    if (!ContainsVertex(vertex))
        return ans_v;
    class std::map<int, std::vector<WeightedEdge<T>>>::const_iterator it;
    it = edges.find(vertex);
    if (it != edges.end())
        return edges.at(vertex);
    return ans_v;
}

template <typename T>
int WeightedGraph<T>::GetDegree(int vertex) const
{
    if (!ContainsVertex(vertex))
        return 0;
    return GetOutgoingEdges(vertex).size();
}

template <typename T>
std::vector<int> WeightedGraph<T>::GetNeighbors(int vertex) const
{
    std::vector<WeightedEdge<T>> temp;
    std::vector<int> ans_v;
    temp = GetOutgoingEdges(vertex);
    for (auto x : temp)
        ans_v.push_back(x.GetDestination());
    return ans_v;
}
#endif
