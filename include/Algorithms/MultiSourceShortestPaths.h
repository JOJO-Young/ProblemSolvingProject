#ifndef MULTI_SOURCE_SHORTEST_PATHS
#define MULTI_SOURCE_SHORTEST_PATHS

#include <set>
#include <map>
#include <vector>
#include <optional>
#include <Exceptions/NegativeCycleException.h>

template <typename TGraph>
class MultiSourceShortestPaths
{
#define TValue typename TGraph::value_type //定义一个宏
protected:
  std::map<std::pair<int, int>, TValue> ans_TryGetDistanceOf;               //用来表示点int的最短路，相当于dis
  std::map<std::pair<int, int>, std::vector<int>> ans_TryGetShortestPathOf; //用来记录路径
public:
  MultiSourceShortestPaths() = delete;
  explicit MultiSourceShortestPaths(const TGraph *graph);
  virtual ~MultiSourceShortestPaths();

public:
  bool HasPathOf(int source, int destination) const;
  std::optional<TValue> TryGetDistanceOf(int source, int destination) const;
  std::optional<std::vector<int>> TryGetShortestPathOf(int source, int destination) const;

public:
  TValue epsilon();
  TValue epsilon_real(std::true_type);
  TValue epsilon_real(std::false_type);
};

template <typename TGraph>
MultiSourceShortestPaths<TGraph>::MultiSourceShortestPaths(const TGraph *graph)
{
}

template <typename TGraph>
MultiSourceShortestPaths<TGraph>::~MultiSourceShortestPaths()
{
}

template <typename TGraph>
bool MultiSourceShortestPaths<TGraph>::HasPathOf(int source, int destination) const
{
  if (ans_TryGetDistanceOf.find(std::make_pair(source, destination)) == ans_TryGetDistanceOf.end())
    return false;
  return true;
}

template <typename TGraph>
std::optional<TValue> MultiSourceShortestPaths<TGraph>::TryGetDistanceOf(int source, int destination) const
{
  if (ans_TryGetDistanceOf.find(std::make_pair(source, destination)) == ans_TryGetDistanceOf.end())
    return std::nullopt;
  return ans_TryGetDistanceOf.at(std::make_pair(source, destination));
}

template <typename TGraph>
std::optional<std::vector<int>> MultiSourceShortestPaths<TGraph>::TryGetShortestPathOf(int source, int destination) const
{
  if (ans_TryGetShortestPathOf.find(std::make_pair(source, destination)) == ans_TryGetShortestPathOf.end())
    return std::nullopt;
  return ans_TryGetShortestPathOf.at(std::make_pair(source, destination));
}

template <typename TGraph>
TValue MultiSourceShortestPaths<TGraph>::epsilon()
{
  return epsilon_real(std::is_floating_point<TValue>());
}

template <typename TGraph>
TValue MultiSourceShortestPaths<TGraph>::epsilon_real(std::true_type)
{
  return 1e-6;
}

template <typename TGraph>
TValue MultiSourceShortestPaths<TGraph>::epsilon_real(std::false_type)
{
  return TValue();
}
#endif
