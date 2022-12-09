#ifndef FLOYD_SHORTEST_PATHS
#define FLOYD_SHORTEST_PATHS

#include <Algorithms/MultiSourceShortestPaths.h>

template <typename TGraph>
class FloydShortestPaths : public MultiSourceShortestPaths<TGraph>
{
public:
    FloydShortestPaths() = delete;
    explicit FloydShortestPaths(TGraph *graph);
    ~FloydShortestPaths();
};

template <typename TGraph>
FloydShortestPaths<TGraph>::~FloydShortestPaths()
{
}

template <typename TGraph>
FloydShortestPaths<TGraph>::FloydShortestPaths(TGraph *graph) : MultiSourceShortestPaths<TGraph>(graph)
{
    std::set<std::pair<int, int>> if_calculate;
    std::map<int, std::set<int>> neighbors;
    std::map<std::pair<int, int>, int> pre_record;
    /*****************************************************/
    std::string s = "Floyd";
    NegativeCycleException warning(s);
    /*****************************************************/
    for (auto x : graph->GetVertices())
        for (auto p : graph->GetNeighbors(x))
            neighbors[x].insert(p);
    for (auto x : graph->GetVertices())
        for (auto y : graph->GetVertices())
        {
            if (x == y)
            {
                this->ans_TryGetDistanceOf[std::make_pair(x, y)] = TValue();
                if_calculate.insert(std::make_pair(x, y));
            }
            else if (neighbors[x].find(y) != neighbors[x].end())
            {
                this->ans_TryGetDistanceOf[std::make_pair(x, y)] = graph->GetWeight(x, y);
                if_calculate.insert(std::make_pair(x, y));
                pre_record[std::make_pair(x, y)] = x;
            }
        }
    for (auto mid : graph->GetVertices())
        for (auto x : graph->GetVertices())
        {
            for (auto y : graph->GetVertices())
            {
                if (if_calculate.find(std::make_pair(x, mid)) != if_calculate.end() && if_calculate.find(std::make_pair(mid, y)) != if_calculate.end())
                {
                    if (if_calculate.find(std::make_pair(x, y)) == if_calculate.end())
                    {
                        this->ans_TryGetDistanceOf[std::make_pair(x, y)] = this->ans_TryGetDistanceOf[std::make_pair(x, mid)] + this->ans_TryGetDistanceOf[std::make_pair(mid, y)];
                        pre_record[std::make_pair(x, y)] = pre_record[std::make_pair(mid, y)];
                        if_calculate.insert(std::make_pair(x, y));
                    }
                    else if (this->ans_TryGetDistanceOf[std::make_pair(x, y)] > this->ans_TryGetDistanceOf[std::make_pair(x, mid)] + this->ans_TryGetDistanceOf[std::make_pair(mid, y)])
                    {
                        this->ans_TryGetDistanceOf[std::make_pair(x, y)] = this->ans_TryGetDistanceOf[std::make_pair(x, mid)] + this->ans_TryGetDistanceOf[std::make_pair(mid, y)];
                        pre_record[std::make_pair(x, y)] = pre_record[std::make_pair(mid, y)];
                    }
                }
            }
            /***********************************************************************************/
            if (this->ans_TryGetDistanceOf[std::make_pair(x, x)] + this->epsilon() < TValue())
                throw warning;
            /***********************************************************************************/
        }

    for (auto x : graph->GetVertices())
        for (auto y : graph->GetVertices())
        {
            if (if_calculate.find(std::make_pair(x, y)) != if_calculate.end())
            {
                int record_x = x;
                int record_y = y;
                std::vector<int> ans_v;
                while (x != y)
                {
                    ans_v.push_back(y);
                    y = pre_record[std::make_pair(x, y)];
                }
                ans_v.push_back(x);
                std::reverse(ans_v.begin(), ans_v.end());
                this->ans_TryGetShortestPathOf[std::make_pair(record_x, record_y)] = ans_v;
            }
        }
}
#endif