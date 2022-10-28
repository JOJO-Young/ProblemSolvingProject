#ifndef UNDIRECTEDWEIGHTEDGRAPH_H
#define UNDIRECTEDWEIGHTEDGRAPH_H

#include <DataStructures/WeightedGraph.h>

template <class T>
class UndirectedWeightedGraph : public WeightedGraph<T>
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

template <class T>
UndirectedWeightedGraph<T>::UndirectedWeightedGraph()
{
    num_selfring = 0;
}
template <class T>
UndirectedWeightedGraph<T>::~UndirectedWeightedGraph()
{
}

template <class T>
bool UndirectedWeightedGraph<T>::AddEdge(int vertex1, int vertex2, T weight)
{
    bool flag1 = WeightedGraph<T>::AddEdge(vertex1, vertex2, weight);
    bool flag2 = WeightedGraph<T>::AddEdge(vertex2, vertex1, weight);
    bool flag = flag1 || flag2;
    if (flag && vertex1 == vertex2)
    {
        num_selfring++;
        if (vertex_to_selfring.find(vertex1) == vertex_to_selfring.end())
            vertex_to_selfring[vertex1] = 1;
        else
            vertex_to_selfring[vertex1]++;
    }
    return flag;
}

template <class T>
bool UndirectedWeightedGraph<T>::RemoveEdge(int vertex1, int vertex2)
{
    bool flag1 = WeightedGraph<T>::RemoveEdge(vertex1, vertex2);
    bool flag2 = WeightedGraph<T>::RemoveEdge(vertex2, vertex1);
    bool flag = flag1 || flag2;
    if (flag && vertex1 == vertex2)
    {
        num_selfring--;
        vertex_to_selfring[vertex1]--;
    }
    return flag;
}

template <class T>
int UndirectedWeightedGraph<T>::CountEdges() const
{
    return (WeightedGraph<T>::CountEdges() + num_selfring) / 2;
}

template <class T>
std::vector<WeightedEdge<T>> UndirectedWeightedGraph<T>::GetEdges() const
{
    std::vector<WeightedEdge<T>> ans_v;
    std::map<int, std::vector<WeightedEdge<T>>> record_map;
    std::vector<WeightedEdge<T>> ans_set = WeightedGraph<T>::GetEdges();
    for (auto x : ans_set)
    {
        if (record_map.find(x.GetSource()) == record_map.end())
        {
            record_map[x.GetDestination()].push_back(x);
            ans_v.push_back(x);
        }
        else
        {
            int flag = 1;
            for (auto y : record_map[x.GetSource()])
            {
                if (y.GetSource() == x.GetDestination())
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                record_map[x.GetDestination()].push_back(x);
                ans_v.push_back(x);
            }
        }
    }
    return ans_v;
}

template <class T>
int UndirectedWeightedGraph<T>::GetDegree(int vertex) const
{
    if (vertex_to_selfring.find(vertex) == vertex_to_selfring.end())
        return WeightedGraph<T>::GetDegree(vertex);
    else
        return WeightedGraph<T>::GetDegree(vertex) + vertex_to_selfring.at(vertex);
}
#endif