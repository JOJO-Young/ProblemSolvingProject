#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
  Edge(int source, int destination);
  ~Edge();

public:
  int GetSource() const;
  int GetDestination() const;
  bool operator== (const Edge& x) const;

private:
  int source;
  int destination;
};
#endif
