#ifndef WEIGHTEDGE_H
#define WEIGHTEDGE_H

#include <DataStructures/Edge.h>
class WeightedEdge : public Edge
{
public:
    WeightedEdge(int source, int destination, int weight);
    ~WeightedEdge();

public:
    int GetWeight() const;

private:
    int weight;
};
#endif
