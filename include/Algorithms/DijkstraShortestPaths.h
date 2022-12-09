#ifndef DIJKSTRA_SHORTEST_PATHS
#define DIJKSTRA_SHORTEST_PATHS

#include <Algorithms/ShortestPaths.h>

template <typename TGraph>
class DijkstraShortestPaths : public ShortestPaths<TGraph>
{
public:
    DijkstraShortestPaths() = delete;
    DijkstraShortestPaths(const TGraph *graph, int source);
    ~DijkstraShortestPaths();
};

template <typename TGraph>
DijkstraShortestPaths<TGraph>::~DijkstraShortestPaths()
{
}

template <typename TGraph>
DijkstraShortestPaths<TGraph>::DijkstraShortestPaths(const TGraph *graph, int source) : ShortestPaths<TGraph>(graph, source)
{
    std::set<int> if_calculate_weight; //用来计算这个点是否已经计算过权重
    std::set<int> if_catched;          //用来计算这个点是否到达过
    std::map<int, int> pre;            // pre<a, b>表示b是a的前继
    std::priority_queue<std::pair<TValue, int>, std::vector<std::pair<TValue, int>>, std::greater<std::pair<TValue, int>>> q;
    this->ans_TryGetDistanceTo[source] = TValue();
    q.push(std::make_pair(TValue(), source));
    if_calculate_weight.insert(source);
    while (!q.empty())
    {
        std::pair<TValue, int> now = q.top();
        q.pop();
        if (if_catched.find(now.second) != if_catched.end())
            continue;
        if_catched.insert(now.second);
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
    }
}
#endif