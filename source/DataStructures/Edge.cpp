#include <DataStructures/Edge.h>
Edge::Edge(int source, int destination)
{
    this->source = source;
    this->destination = destination;
}
Edge::~Edge()
{
}
int Edge::GetSource() const
{
    return source;
}
int Edge::GetDestination() const
{
    return destination;
}