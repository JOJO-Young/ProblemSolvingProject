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
    if (ContainsVertex(vertex))
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
    std::map<int, std::vector<Edge>>::iterator it = edges.find(vertex1);
    if (it == edges.end())
        edges[vertex1].push_back(Edge(vertex1, vertex2));
    else
    {
        for (auto x : edges[vertex1])
            if (x.GetDestination() == vertex2)
                return false;
        edges[vertex1].push_back(Edge(vertex1, vertex2));
    }
    return true;
}

bool Graph::RemoveEdge(int vertex1, int vertex2)
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::map<int, std::vector<Edge>>::iterator it = edges.find(vertex1);
    if (it == edges.end())
        return false;
    else
    {
        for (std::vector<Edge>::iterator i = edges[vertex1].begin(); i != edges[vertex1].end(); i++)
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
int Graph::CountVertices() const
{
    return vertices.size();
}

int Graph::CountEdges() const
{
    int ans = 0;
    for (std::map<int, std::vector<Edge>>::const_iterator i = edges.begin(); i != edges.end(); i++)
        ans = ans + i->second.size();
    return ans;
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
    std::map<int, std::vector<Edge>>::const_iterator it;
    it = edges.find(vertex1);
    if (it == edges.end())
        return false;
    for (auto x : it->second)
        if (x.GetDestination() == vertex2)
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
    std::vector<Edge> ans_v;
    std::map<int, std::vector<Edge>>::const_iterator it;
    it = edges.begin();
    for (; it != edges.end(); it++)
    {
        for (auto x : it->second)
            ans_v.push_back(x);
    }
    return ans_v;
}

std::vector<Edge> Graph::GetIncomingEdges(int vertex) const
{
    std::vector<Edge> ans_v;
    if (!ContainsVertex(vertex))
        return ans_v;
    std::map<int, std::vector<Edge>>::const_iterator it;
    it = edges.begin();
    for (; it != edges.end(); it++)
    {
        for (auto x : it->second)
            if (x.GetDestination() == vertex)
                ans_v.push_back(x);
    }
    return ans_v;
}

std::vector<Edge> Graph::GetOutgoingEdges(int vertex) const
{
    std::vector<Edge> ans_v;
    if (!ContainsVertex(vertex))
        return ans_v;
    std::map<int, std::vector<Edge>>::const_iterator it;
    it = edges.find(vertex);
    if (it != edges.end())
        return edges.at(vertex);
    return ans_v;
}

int Graph::GetDegree(int vertex) const
{
    if (!ContainsVertex(vertex))
        return 0;
    return GetOutgoingEdges(vertex).size();
}

std::vector<int> Graph::GetNeighbors(int vertex) const
{
    std::vector<Edge> temp;
    std::vector<int> ans_v;
    temp = GetOutgoingEdges(vertex);
    for(auto x : temp)
        ans_v.push_back(x.GetDestination());
    return ans_v;
}