#include <DataStructures/WeightedGraph.h>
#include <algorithm>
WeightedGraph::WeightedGraph()
{
}
WeightedGraph::~WeightedGraph()
{
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
bool WeightedGraph::AddVertex(int vertex)
{
    if (ContainsVertex(vertex))
        return false;
    vertices.insert(vertex);
    return true;
}

bool WeightedGraph::RemoveVertex(int vertex)
{
    std::set<int>::iterator it;
    it = vertices.find(vertex);
    if (it == vertices.end())
        return false;
    vertices.erase(it);
    return true;
}

bool WeightedGraph::AddEdge(int vertex1, int vertex2, int weight)
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::map<int, std::vector<WeightedEdge>>::iterator it = edges.find(vertex1);
    if (it == edges.end())
        edges[vertex1].push_back(WeightedEdge(vertex1, vertex2, weight));
    else
    {
        for (auto x : edges[vertex1])
            if (x.GetDestination() == vertex2)
                return false;
        edges[vertex1].push_back(WeightedEdge(vertex1, vertex2, weight));
    }
    return true;
}

bool WeightedGraph::RemoveEdge(int vertex1, int vertex2)
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::map<int, std::vector<WeightedEdge>>::iterator it = edges.find(vertex1);
    if (it == edges.end())
        return false;
    else
    {
        for (std::vector<WeightedEdge>::iterator i = edges[vertex1].begin(); i != edges[vertex1].end(); i++)
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
int WeightedGraph::CountVertices() const
{
    return vertices.size();
}

int WeightedGraph::CountEdges() const
{
    int ans = 0;
    for (std::map<int, std::vector<WeightedEdge>>::const_iterator i = edges.begin(); i != edges.end(); i++)
        ans = ans + i->second.size();
    return ans;
}
bool WeightedGraph::ContainsVertex(int vertex) const
{
    if (vertices.find(vertex) == vertices.end())
        return false;
    return true;
}

bool WeightedGraph::ContainsEdge(int vertex1, int vertex2) const
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::map<int, std::vector<WeightedEdge>>::const_iterator it;
    it = edges.find(vertex1);
    if (it == edges.end())
        return false;
    for (auto x : it->second)
        if (x.GetDestination() == vertex2)
            return true;
    return false;
}

int WeightedGraph::GetWeight(int vertex1, int vertex2) const
{
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2))
        return false;
    std::map<int, std::vector<WeightedEdge>>::const_iterator it;
    it = edges.find(vertex1);
    if (it == edges.end())
        return -1;
    for (std::vector<WeightedEdge>::const_iterator i = edges.at(vertex1).begin(); i != edges.at(vertex1).end(); i++)
        if (i->GetDestination() == vertex2)
            return i->GetWeight();
    return -1;
}

std::vector<int> WeightedGraph::GetVertices() const
{
    std::set<int>::const_iterator it = vertices.begin();
    std::vector<int> v;
    for (; it != vertices.end(); it++)
        v.push_back(*it);
    return v;
}

std::vector<WeightedEdge> WeightedGraph::GetEdges() const
{
    std::vector<WeightedEdge> ans_v;
    std::map<int, std::vector<WeightedEdge>>::const_iterator it;
    it = edges.begin();
    for (; it != edges.end(); it++)
    {
        for (auto x : it->second)
            ans_v.push_back(x);
    }
    return ans_v;
}

std::vector<WeightedEdge> WeightedGraph::GetIncomingEdges(int vertex) const
{
    std::vector<WeightedEdge> ans_v;
    if (!ContainsVertex(vertex))
        return ans_v;
    std::map<int, std::vector<WeightedEdge>>::const_iterator it;
    it = edges.begin();
    for (; it != edges.end(); it++)
    {
        for (auto x : it->second)
            if (x.GetDestination() == vertex)
                ans_v.push_back(x);
    }
    return ans_v;
}

std::vector<WeightedEdge> WeightedGraph::GetOutgoingEdges(int vertex) const
{
    std::vector<WeightedEdge> ans_v;
    if (!ContainsVertex(vertex))
        return ans_v;
    std::map<int, std::vector<WeightedEdge>>::const_iterator it;
    it = edges.find(vertex);
    if (it != edges.end())
        return edges.at(vertex);
    return ans_v;
}

int WeightedGraph::GetDegree(int vertex) const
{
    if (!ContainsVertex(vertex))
        return 0;
    return GetOutgoingEdges(vertex).size();
}

std::vector<int> WeightedGraph::GetNeighbors(int vertex) const
{
    std::vector<WeightedEdge> temp;
    std::vector<int> ans_v;
    temp = GetOutgoingEdges(vertex);
    for (auto x : temp)
        ans_v.push_back(x.GetDestination());
    return ans_v;
}