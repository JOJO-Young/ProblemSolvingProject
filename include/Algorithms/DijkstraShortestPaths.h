#ifndef DIJKSTRA_SHORTEST_PATHS
#define DIJKSTRA_SHORTEST_PATHS

#include <set>
#include <map>
#include <stdio.h>
#include <queue>
#include <stack>
#include <vector>
#include <Algorithms/ShortestPaths.h>

template <template <typename> class TGraph, typename TValue>
class DijkstraShortestPaths : public ShortestPaths<TGraph, TValue>
{
public:
    DijkstraShortestPaths() = delete;
    DijkstraShortestPaths(const TGraph<TValue> *graph, int source);
    ~DijkstraShortestPaths();
};
template <template <typename> class TGraph, typename TValue>
DijkstraShortestPaths<TGraph, TValue>::~DijkstraShortestPaths()
{
}

template <template <typename> class TGraph, typename TValue>
DijkstraShortestPaths<TGraph, TValue>::DijkstraShortestPaths(const TGraph<TValue> *graph, int source) : ShortestPaths<TGraph, TValue>(graph, source)
{
    std::set<int> if_reach; //用来记录这个点是否到达过，相当于vis
    std::map<int, int> pre; // pre<a, b>表示b是a的前继
    std::priority_queue<std::pair<TValue, int>, std::vector<std::pair<TValue, int>>, std::greater<std::pair<TValue, int>>> q;
    this->ans_TryGetDistanceTo[source] = TValue();
    q.push(std::make_pair(TValue(), source));
    while (!q.empty())
    {
        std::pair<TValue, int> now = q.top();
        q.pop();
        if (if_reach.find(now.second) != if_reach.end())
            continue;
        if_reach.insert(now.second);
        for (auto x : graph->GetNeighbors(now.second))
            if (if_reach.find(x) == if_reach.end())
            {
                this->ans_TryGetDistanceTo[x] = this->ans_TryGetDistanceTo[now.second] + graph->GetWeight(now.second, x);
                pre[x] = now.second;
                printf("yzy%d %d\n", x, now.second);
                q.push(std::make_pair(this->ans_TryGetDistanceTo[x], x));
            }
            else if (this->ans_TryGetDistanceTo[x] > this->ans_TryGetDistanceTo[now.second] + graph->GetWeight(now.second, x))
            {
                this->ans_TryGetDistanceTo[x] = this->ans_TryGetDistanceTo[now.second] + graph->GetWeight(now.second, x);
                pre[x] = now.second;
                q.push(std::make_pair(this->ans_TryGetDistanceTo[x], x));
            }
    }
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
            std::vector<int> ans;
            while (!s.empty())
            {
                ans.push_back(s.top());
                s.pop();
            }
            this->ans_TryGetShortestPathTo[record] = ans;
        }
        else
            this->ans_TryGetShortestPathTo[record] = std::nullopt;
    }
}
#endif