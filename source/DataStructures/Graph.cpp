#include <DataStructures/Graph.h>
#include <algorithm>
Graph::Graph()
{
}
Graph::~Graph()
{
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
bool Graph::AddVertex(int vertex)
{
    if(ContainsVertex(vertex))
        return false;
    vertices.insert(vertex);
    return true;
}

bool Graph::RemoveVertex(int vertex)
{
    std::set<int>::iterator it;
    it = vertices.find(vertex);
    if (it == vertices.end())
        return false;
    vertices.erase(it);
    return true;
}

bool Graph::AddEdge(int vertex1, int vertex2)
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::multimap<int, int>::iterator it = s_to_d.find(vertex1);
    for (; it != s_to_d.end() && it->first == vertex1; it++)
        if (it->second == vertex2)
            return false;
    s_to_d.insert(std::pair(vertex1, vertex2));
    d_to_s.insert(std::pair(vertex2, vertex1));
    return true;
}

bool Graph::RemoveEdge(int vertex1, int vertex2)
{
    int flag = 0;
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::multimap<int, int>::iterator it;
    it = s_to_d.find(vertex1);
    for (; it != s_to_d.end() && it->first == vertex1; it++)
        if (it->second == vertex2)
        {
            s_to_d.erase(it);
            flag = 1;
            break;
        }
    it = d_to_s.find(vertex2);
    for (; it != d_to_s.end() && it->first == vertex2; it++)
        if (it->second == vertex1)
        {
            d_to_s.erase(it);
            flag = 1;
            break;
        }
    if (flag == 1)
        return true;
    return false;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int Graph::CountVertices() const
{
    return vertices.size();
}

int Graph::CountEdges() const
{
    return s_to_d.size();
}

bool Graph::ContainsVertex(int vertex) const
{
    if (vertices.find(vertex) == vertices.end())
        return false;
    return true;
}

bool Graph::ContainsEdge(int vertex1, int vertex2) const
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::multimap<int, int>::const_iterator it;
    it = s_to_d.find(vertex1);
    for (; it != s_to_d.end() && it->first == vertex1; it++)
        if (it->second == vertex2)
            return true;
    return false;
}

std::vector<int> Graph::GetVertices() const
{
    std::set<int>::const_iterator it = vertices.begin();
    std::vector<int> v;
    for (; it != vertices.end(); it++)
        v.push_back(*it);
    return v;
}

std::vector<Edge> Graph::GetEdges() const
{
    std::multimap<int, int>::const_iterator it = s_to_d.begin();
    std::vector<Edge> v;
    for (; it != s_to_d.end(); it++)
        v.push_back(Edge(it->first, it->second));
    return v;
}

std::vector<Edge> Graph::GetIncomingEdges(int vertex) const
{
    std::vector<Edge> new_vector;
    if (!ContainsVertex(vertex))
        return new_vector;
    std::multimap<int, int>::const_iterator it = d_to_s.find(vertex);
    for (; it != d_to_s.end() && it->first == vertex; it++)
        new_vector.push_back(Edge(it->second, it->first));
    return new_vector;
}

std::vector<Edge> Graph::GetOutgoingEdges(int vertex) const
{
    std::vector<Edge> new_vector;
    if (!ContainsVertex(vertex))
        return new_vector;
    std::multimap<int, int>::const_iterator it = s_to_d.find(vertex);
    for (; it != s_to_d.end() && it->first == vertex; it++)
        new_vector.push_back(Edge(it->first, it->second));
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
    std::vector<int> new_vector;
    if (!ContainsVertex(vertex))
        return new_vector;
    std::multimap<int, int>::const_iterator it = s_to_d.find(vertex);
    for (; it != s_to_d.end() && it->first == vertex; it++)
        new_vector.push_back(it->second);
    return new_vector;
}