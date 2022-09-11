#include <DataStructures/Graph.h>
#include <algorithm>
Graph::Graph()
{
}
Graph::~Graph()
{
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
bool Graph::AddVertex(int vertex)
{
    if (find(vertices.begin(), vertices.end(), vertex) == vertices.end())
    {
        vertices.push_back(vertex);
        return true;
    }
    return false;
}

bool Graph::RemoveVertex(int vertex)
{
    std::vector<int>::iterator it = find(vertices.begin(), vertices.end(), vertex);
    if (it == vertices.end())
        return false;
    vertices.erase(it);
    return true;
}

bool Graph::AddEdge(int vertex1, int vertex2)
{
    for (auto e : edges)
        if (e.GetSource() == vertex1 && e.GetDestination() == vertex2)
            return false;
    std::vector<int>::iterator it1 = find(vertices.begin(), vertices.end(), vertex1);
    std::vector<int>::iterator it2 = find(vertices.begin(), vertices.end(), vertex2);
    if (it1 == vertices.end() || it2 == vertices.end())
        return false;
    edges.push_back(Edge(vertex1, vertex2));
    return true;
}

bool Graph::RemoveEdge(int vertex1, int vertex2)
{
    std::vector<Edge>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        if (it->GetSource() == vertex1 && it->GetDestination() == vertex2)
        {
            edges.erase(it);
            return true;
        }
    }
    return false;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int Graph::CountVertices() const
{
    return vertices.size();
}

int Graph::CountEdges() const
{
    return edges.size();
}

bool Graph::ContainsVertex(int vertex) const
{
    if (find(vertices.begin(), vertices.end(), vertex) == vertices.end())
        return false;
    return true;
}

bool Graph::ContainsEdge(int vertex1, int vertex2) const
{
    std::vector<Edge>::const_iterator it; //在常函数里，使用const_iterator
    for (it = edges.begin(); it != edges.end(); it++)
        if (it->GetSource() == vertex1 && it->GetDestination() == vertex2)
            return true;
    return false;
}

std::vector<int> Graph::GetVertices() const
{
    return vertices;
}

std::vector<Edge> Graph::GetEdges() const
{
    return edges;
}

std::vector<Edge> Graph::GetIncomingEdges(int vertex) const
{
    std::vector<Edge> new_vector;
    for (auto e : edges)
    {
        if (e.GetDestination() == vertex)
            new_vector.push_back(e);
    }
    return new_vector;
}

std::vector<Edge> Graph::GetOutgoingEdges(int vertex) const
{
    std::vector<Edge> new_vector;
    for (auto e : edges)
        if (e.GetSource() == vertex)
            new_vector.push_back(e);
    return new_vector;
}

int Graph::GetDegree(int vertex) const
{
    if (!ContainsVertex(vertex))
        return 0;
    return GetOutgoingEdges(vertex).size();
}

std::vector<int> Graph::GetNeighbors(int vertex) const
{
    std::vector<Edge> edge_vector = GetOutgoingEdges(vertex);
    std::vector<int> vertex_vector;
    for (auto e : edge_vector)
        vertex_vector.push_back(e.GetDestination());
    return vertex_vector;
}