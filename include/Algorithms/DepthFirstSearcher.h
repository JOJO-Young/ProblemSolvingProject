#ifndef DEPTH_FIRST_SEARCHER
#define DEPTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <set>

template <typename TGraph>
class DepthFirstSearcher
{
private:
  std::optional<int> ans = std::nullopt;

public:
  static void VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action);
  static std::optional<int> FindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate);
};

template <typename TGraph>
void DepthFirstSearcher<TGraph>::VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action)
{
  std::set<int> catched;
  if (graph->ContainsVertex(start))
  {
    catched.insert(start);
    action(start);
    for (auto x : graph->GetNeighbors(start))
      if (catched.find(start) == catched.end())
        VisitAllVertices(graph, x, action);
  }
}

template <typename TGraph>
std::optional<int> DepthFirstSearcher<TGraph>::FindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate)
{
  std::set<int> catched;
  if (graph->ContainsVertex(start))
  {
    if (predicate(start))
      ans = start;
    catched.insert(start);
    for (auto x : graph->GetNeighbors(start))
      if (catched.find(start) == catched.end())
        FindFirstVertex(graph, x, action);
    return ans;
  }
  return std::nullopt;
}

#endif
