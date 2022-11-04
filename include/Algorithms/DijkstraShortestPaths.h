#ifndef DIJKSTRA_SHORTEST_PATHS
#define DIJKSTRA_SHOATEST_PATHS

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <ShortestPaths.h>

template <template <typename> class TGraph, typename TValue>
class DijkstraShortestPaths : public ShortestPaths
{
public:
    DijkstraShortestPaths();
    DijkstraShortestPaths(const TGraph<TValue> *graph, int source);
    ~DijkstraShortestPaths();
};

template <template <typename> class TGraph, typename TValue>
DijkstraShortestPaths<TGraph, TValue>::DijkstraShortestPaths(const TGraph<TValue> *graph, int source) : ShortestPaths(const TGraph<TValue> *graph, int source)
{
    std::set<int> if_reach; //用来记录这个点是否到达过，相当于vis
    std::map<int, int> pre; // pre<a, b>表示b是a的前继
    std::priority_queue<pair<int, int>> q;
    ans_TryGetDistanceTo[source] = 0;
    q.push(std::make_pair(0, source));
    if_reach.insert(source);
    while (!q.empty())
    {
        std::pair<int, int> now = q.top();
        q.pop();
        if (if_reach.find(now.second) != if_reach.end())
            continue;
        if_reach.insert(now.second);
        for (auto x : graph->GetNeighbors(now.second))
            if (ans_TryGetDistanceTo[x] - graph->GetWeight(now.second, x) > ans_TryGetDistanceTo[now.second])
            {
                ans_TryGetDistanceTo[x] = ans_TryGetDistanceTo[now.second] + graph->GetWeight(now.second, x);
                pre[x] = now.second;
                q.push(std::make_pair(-1 * ans_TryGetDistanceTo[x], x));
            }
    }
    for (auto x : graph->GetVertices())
        if (ans_TryGetDistanceTo[x] == INT_MAX)
            ans_TryGetDistanceTo[x] = std::nullopt;
    for (auto x : graph->GetVertices())
    {
        int record = x;
        std::stack<int> s;
        s.push(x);
        while (x != source)
        {
            if (pre.find(x) != pre.end())
            {
                x = pre[x];
                s.push(x);
            }
            else
                break;
        }
        if (x == source)
        {
            s.push(x);
            std::vector<int> ans;
            while (!s.empty())
            {
                ans.push_back(s.top());
                s.pop();
            }
            ans_TryGetShortestPathTo[record] = ans;
        }
        else
            ans_TryGetShortestPathTo[record] = std::nullopt;
    }
}

#endif