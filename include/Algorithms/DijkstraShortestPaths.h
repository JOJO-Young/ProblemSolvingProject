#ifndef DIJKSTRA_SHORTEST_PATHS
#define DIJKSTRA_SHORTEST_PATHS

#include <set>
#include <map>
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
    std::set<int> if_calculate_weight; //用来计算这个点是否已经计算过权重
    std::map<int, int> pre;            // pre<a, b>表示b是a的前继
    std::priority_queue<std::pair<TValue, int>, std::vector<std::pair<TValue, int>>, std::greater<std::pair<TValue, int>>> q;
    this->ans_TryGetDistanceTo[source] = TValue();
    q.push(std::make_pair(TValue(), source));
    if_calculate_weight.insert(source);
    while (!q.empty())
    {
        std::pair<TValue, int> now = q.top();
        q.pop();
        if (this->ans_HasPathTo.find(now.second) != this->ans_HasPathTo.end())
            continue;
        this->ans_HasPathTo.insert(now.second);
        for (auto x : graph->GetNeighbors(now.second))
            if (if_calculate_weight.find(x) == if_calculate_weight.end()) //因为第一次访问而更改权重
            {
                this->ans_TryGetDistanceTo[x] = this->ans_TryGetDistanceTo[now.second] + graph->GetWeight(now.second, x);
                pre[x] = now.second;
                q.push(std::make_pair(this->ans_TryGetDistanceTo[x], x));
                if_calculate_weight.insert(x);
            }
            else if (this->ans_TryGetDistanceTo[x] > this->ans_TryGetDistanceTo[now.second] + graph->GetWeight(now.second, x)) //因为找到更小distance而更改权重
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