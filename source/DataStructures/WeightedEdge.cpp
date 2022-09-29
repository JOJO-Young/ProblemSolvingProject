
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

