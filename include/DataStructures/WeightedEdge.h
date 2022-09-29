#ifndef WEIGHTEDGE_H
#define WEIGHTEDGE_H

#include <DataStructures/Edge.h>
template<class T>
class WeightedEdge : public Edge
{
public:
    WeightedEdge(int source, int destination, T weight);
    ~WeightedEdge();

public:
    T GetWeight() const;

private:
    T weight;
};

#include <DataStructures/WeightedEdge.h>
template <class T>
WeightedEdge<T>::WeightedEdge(int source, int destination, T weight) : Edge(source, destination), weight(weight)
{
}

template<class T>
WeightedEdge<T>::~WeightedEdge()
{
}

template<class T>
T WeightedEdge<T>::GetWeight() const
{
    return weight;
}

#endif
