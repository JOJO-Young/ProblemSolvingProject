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


#endif
