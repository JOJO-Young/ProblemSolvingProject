#include <DataStructures/UndirectedGraph.h>

UndirectedGraph::UndirectedGraph()
{
    num_selfring = 0;
}
UndirectedGraph::~UndirectedGraph()
{
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
bool UndirectedGraph::AddEdge(int vertex1, int vertex2)
{
    bool flag1 = Graph::AddEdge(vertex1, vertex2);
    bool flag2 = Graph::AddEdge(vertex2, vertex1);
    bool flag = flag1 || flag2;
    if (flag && vertex1 == vertex2)
    {
        num_selfring++;
        if (vertex_to_selfring.find(vertex1) == vertex_to_selfring.end())
            vertex_to_selfring[vertex1] = 1;
        else
            vertex_to_selfring[vertex1]++;
    }
    return flag;
}
bool UndirectedGraph::RemoveEdge(int vertex1, int vertex2)
{
    bool flag1 = Graph::RemoveEdge(vertex1, vertex2);
    bool flag2 = Graph::RemoveEdge(vertex2, vertex1);
    bool flag = flag1 || flag2;
    if (flag && vertex1 == vertex2)
    {
        num_selfring--;
        vertex_to_selfring[vertex1]--;
    }
    return flag;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int UndirectedGraph::CountEdges() const
{
    return (Graph::CountEdges() + num_selfring) / 2;
}
std::vector<Edge> UndirectedGraph::GetEdges() const
{
    std::vector<Edge> ans_v;
    std::map<int, std::vector<Edge>> record_map;
    std::vector<Edge> ans_set = Graph::GetEdges();
    for (auto x : ans_set)
    {
        if (record_map.find(x.GetSource()) == record_map.end())
        {
            record_map[x.GetDestination()].push_back(x);
            ans_v.push_back(x);
        }
        else
        {
            int flag = 1;
            for (auto y : record_map[x.GetSource()])
            {
                if (y.GetSource() == x.GetDestination())
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                record_map[x.GetDestination()].push_back(x);
                ans_v.push_back(x);
            }
        }
    }
    return ans_v;
}
int UndirectedGraph::GetDegree(int vertex) const
{
    if (vertex_to_selfring.find(vertex) == vertex_to_selfring.end())
        return Graph::GetDegree(vertex);
    else
        return Graph::GetDegree(vertex) + vertex_to_selfring.at(vertex);
}
