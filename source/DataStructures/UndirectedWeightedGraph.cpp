#include <DataStructures/UndirectedWeightedGraph.h>

UndirectedWeightedGraph::UndirectedWeightedGraph()
{
    num_selfring = 0;
}
UndirectedWeightedGraph::~UndirectedWeightedGraph()
{
}

bool UndirectedWeightedGraph::AddEdge(int vertex1, int vertex2, int weight)
{
    bool flag1 = WeightedGraph::AddEdge(vertex1, vertex2, weight);
    bool flag2 = WeightedGraph::AddEdge(vertex2, vertex1, weight);
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
bool UndirectedWeightedGraph::RemoveEdge(int vertex1, int vertex2)
{
    bool flag1 = WeightedGraph::RemoveEdge(vertex1, vertex2);
    bool flag2 = WeightedGraph::RemoveEdge(vertex2, vertex1);
    bool flag = flag1 || flag2;
    if (flag && vertex1 == vertex2)
    {
        num_selfring--;
        vertex_to_selfring[vertex1]--;
    }
    return flag;
}

int UndirectedWeightedGraph::CountEdges() const
{
    return (WeightedGraph::CountEdges() + num_selfring) / 2;
}
std::vector<WeightedEdge> UndirectedWeightedGraph::GetEdges() const
{
    std::vector<WeightedEdge> ans_v;
    std::map<int, std::vector<WeightedEdge>> record_map;
    std::vector<WeightedEdge> ans_set = WeightedGraph::GetEdges();
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
int UndirectedWeightedGraph::GetDegree(int vertex) const
{
    if (vertex_to_selfring.find(vertex) == vertex_to_selfring.end())
        return WeightedGraph::GetDegree(vertex);
    else
        return WeightedGraph::GetDegree(vertex) + vertex_to_selfring.at(vertex);
}