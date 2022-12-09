#ifndef BELLMAN_FORD_SHORTEST_PATHS
#define BELLMAN_FORD_SHORTEST_PATHS

#include <Algorithms/ShortestPaths.h>

template <typename TGraph>
class BellmanFordShortestPaths : public ShortestPaths<TGraph>
{
public:
    BellmanFordShortestPaths() = delete;
    BellmanFordShortestPaths(const TGraph *graph, int source);
    ~BellmanFordShortestPaths();
};

template <typename TGraph>
BellmanFordShortestPaths<TGraph>::~BellmanFordShortestPaths()
{
}

template <typename TGraph>
BellmanFordShortestPaths<TGraph>::BellmanFordShortestPaths(const TGraph *graph, int source) : ShortestPaths<TGraph>(graph, source)
{
    std::map<int, int> pre;            // pre<a,b>表示b是a的前继
    std::map<int, int> times;          //记录一个点入队了多少次
    std::set<int> if_catched;          //存储某个点是否在队列中
    std::set<int> if_calculate_weight; //用来计算这个点是否已经计算过权重
    std::queue<int> wait_to_dealwith;  //存储将要被relax的边
    int vertex_size = graph->CountVertices();
    this->ans_TryGetDistanceTo[source] = TValue();
    if_catched.insert(source);
    if_calculate_weight.insert(source);
    wait_to_dealwith.push(source);
    /***************************************************/
    std::string s = "Bellman-Ford";
    NegativeCycleException warning(s);
    if (times.find(source) == times.end())
        times[source] = 1;
    else
        times[source]++;
    /***************************************************/
    while (!wait_to_dealwith.empty())
    {
        int now = wait_to_dealwith.front();
        wait_to_dealwith.pop();
        if_catched.erase(now);
        for (auto x : graph->GetNeighbors(now))
            if (if_calculate_weight.find(x) == if_calculate_weight.end()) //因为第一次访问而更改权重
            {
                this->ans_TryGetDistanceTo[x] = this->ans_TryGetDistanceTo[now] + graph->GetWeight(now, x);
                pre[x] = now;
                if (if_catched.find(x) == if_catched.end())
                {
                    wait_to_dealwith.push(x);
                    /********************************************************************/
                    if (times.find(x) == times.end())
                        times[x] = 1;
                    else
                        times[x]++;
                    if (times[x] > vertex_size)
                        throw warning;
                    /********************************************************************/
                    if_catched.insert(x);
                }
                if_calculate_weight.insert(x);
            }
            else if (this->ans_TryGetDistanceTo[x] > this->ans_TryGetDistanceTo[now] + graph->GetWeight(now, x)) //因为找到更小distance而更改权重
            {
                this->ans_TryGetDistanceTo[x] = this->ans_TryGetDistanceTo[now] + graph->GetWeight(now, x);
                pre[x] = now;
                if (if_catched.find(x) == if_catched.end())
                {
                    wait_to_dealwith.push(x);
                    /********************************************************************/
                    if (times.find(x) == times.end())
                        times[x] = 1;
                    else
                        times[x]++;
                    if (times[x] > vertex_size)
                        throw warning;
                    /********************************************************************/
                    if_catched.insert(x);
                }
            }
    } //用了一个SPFA
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