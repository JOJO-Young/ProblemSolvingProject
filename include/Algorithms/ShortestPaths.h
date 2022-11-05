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
  std::map<int, TValue> ans_TryGetDistanceTo;                              //用来表示点int的最短路，相当于dis
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
  ans_HasPathTo.clear();
  ans_TryGetDistanceTo.clear();
  ans_TryGetShortestPathTo.clear();
}

template <template <typename> class TGraph, typename TValue>
ShortestPaths<TGraph, TValue>::ShortestPaths(const TGraph<TValue> *graph, int source)
{
}
template <template <typename> class TGraph, typename TValue>
bool ShortestPaths<TGraph, TValue>::HasPathTo(int destination) const
{
  return ans_HasPathTo.find(destination) != ans_HasPathTo.end();
}

template <template <typename> class TGraph, typename TValue>
std::optional<TValue> ShortestPaths<TGraph, TValue>::TryGetDistanceTo(int destination) const
{
  if (ans_TryGetDistanceTo.find(destination) != ans_TryGetDistanceTo.end())
    return ans_TryGetDistanceTo.at(destination);
  else
    return std::nullopt;
}

template <template <typename> class TGraph, typename TValue>
std::optional<std::vector<int>> ShortestPaths<TGraph, TValue>::TryGetShortestPathTo(int destination) const
{
  if (ans_TryGetShortestPathTo.find(destination) != ans_TryGetShortestPathTo.end())
    return ans_TryGetShortestPathTo.at(destination);
  else
    return std::nullopt;
}
#endif
