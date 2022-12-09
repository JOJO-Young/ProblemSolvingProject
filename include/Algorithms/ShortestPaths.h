#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <optional>
#include <type_traits>
#include <Exceptions/NegativeCycleException.h>

template <typename TGraph>
class ShortestPaths
{
public:
#define TValue typename TGraph::value_type //定义一个宏，方便在DijkstraShortestPaths中萃取出TValue
  static_assert(std::is_default_constructible<TValue>::value, "TValue requires default constructor");

protected:
  std::set<int> ans_HasPathTo;                              //用来记录哪些点可到达
  std::map<int, TValue> ans_TryGetDistanceTo;               //用来表示点int的最短路，相当于dis
  std::map<int, std::vector<int>> ans_TryGetShortestPathTo; //用来记录路径

public:
  ShortestPaths() = delete;
  ShortestPaths(const TGraph *graph, int source);
  virtual ~ShortestPaths();

public:
  bool HasPathTo(int destination) const;
  std::optional<TValue> TryGetDistanceTo(int destination) const;
  std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const;
};
template <typename TGraph>
ShortestPaths<TGraph>::~ShortestPaths()
{
  ans_HasPathTo.clear();
  ans_TryGetDistanceTo.clear();
  ans_TryGetShortestPathTo.clear();
}

template <typename TGraph>
ShortestPaths<TGraph>::ShortestPaths(const TGraph *graph, int source)
{
  std::queue<int> q;
  if (graph->ContainsVertex(source))
  {
    q.push(source);
    ans_HasPathTo.insert(source);
    while (!q.empty())
    {
      int tmp = q.front();
      q.pop();
      for (auto x : graph->GetNeighbors(tmp))
      {
        if (ans_HasPathTo.find(x) == ans_HasPathTo.end())
        {
          q.push(x);
          ans_HasPathTo.insert(x);
        }
      }
    }
  }
} //里面用来计算哪些点从source开始可达

template <typename TGraph>
bool ShortestPaths<TGraph>::HasPathTo(int destination) const
{
  return ans_HasPathTo.find(destination) != ans_HasPathTo.end();
}

template <typename TGraph>
std::optional<TValue> ShortestPaths<TGraph>::TryGetDistanceTo(int destination) const
{
  if (ans_TryGetDistanceTo.find(destination) != ans_TryGetDistanceTo.end())
    return ans_TryGetDistanceTo.at(destination);
  else
    return std::nullopt;
}

template <typename TGraph>
std::optional<std::vector<int>> ShortestPaths<TGraph>::TryGetShortestPathTo(int destination) const
{
  if (ans_TryGetShortestPathTo.find(destination) != ans_TryGetShortestPathTo.end())
    return ans_TryGetShortestPathTo.at(destination);
  else
    return std::nullopt;
}
#endif
