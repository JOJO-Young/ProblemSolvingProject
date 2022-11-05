#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <set>
#include <queue>
#include <vector>
#include <limits.h>
#include <optional>

template <template <typename> class TGraph, typename TValue>
class ShortestPaths
{
protected:
  std::set<int> ans_HasPathTo;                                             //用来记录哪些点可到达
  std::map<int, int> ans_TryGetDistanceTo;                                 //用来表示点int的最短路，相当于dis
  std::map<int, std::optional<std::vector<int>>> ans_TryGetShortestPathTo; //用来记录路径

public:
  ShortestPaths() = delete;
  ShortestPaths(const TGraph<TValue> *graph, int source);
  virtual ~ShortestPaths();

public:
  bool HasPathTo(int destination) const;
  std::optional<TValue> TryGetDistanceTo(int destination) const;
  std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const;
};
template <template <typename> class TGraph, typename TValue>
ShortestPaths<TGraph, TValue>::~ShortestPaths()
{
}

template <template <typename> class TGraph, typename TValue>
ShortestPaths<TGraph, TValue>::ShortestPaths(const TGraph<TValue> *graph, int source)
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
  for (auto x : graph->GetVertices())
  {
    ans_TryGetDistanceTo[x] = INT_MAX / 2;
    ans_TryGetShortestPathTo[x] = std::nullopt;
  }
}
template <template <typename> class TGraph, typename TValue>
bool ShortestPaths<TGraph, TValue>::HasPathTo(int destination) const
{
  return ans_HasPathTo.find(destination) != ans_HasPathTo.end();
}

template <template <typename> class TGraph, typename TValue>
std::optional<TValue> ShortestPaths<TGraph, TValue>::TryGetDistanceTo(int destination) const
{
  if (ans_TryGetDistanceTo.at(destination) == INT_MAX / 2)
    return std::nullopt;
  else
    return ans_TryGetDistanceTo.at(destination);
}

template <template <typename> class TGraph, typename TValue>
std::optional<std::vector<int>> ShortestPaths<TGraph, TValue>::TryGetShortestPathTo(int destination) const
{
  return ans_TryGetShortestPathTo.at(destination);
}
#endif
