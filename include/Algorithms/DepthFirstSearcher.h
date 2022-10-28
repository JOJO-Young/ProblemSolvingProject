#ifndef DEPTH_FIRST_SEARCHER
#define DEPTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <set>

template <typename TGraph>
class DepthFirstSearcher
{
private:
  static std::optional<int> ans;
  static std::set<int> catched;

public:
  static void VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action);
  static std::optional<int> FindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate);
};

template <typename TGraph>
std::optional<int> DepthFirstSearcher<TGraph>::ans = std::nullopt;

template <typename TGraph>
std::set<int> DepthFirstSearcher<TGraph>::catched;

template <typename TGraph>
void DepthFirstSearcher<TGraph>::VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action)
{
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
  if (graph->ContainsVertex(start))
  {
    if (predicate(start))
      ans = start;
    catched.insert(start);
    for (auto x : graph->GetNeighbors(start))
      if (catched.find(start) == catched.end())
        FindFirstVertex(graph, x, predicate);
    return ans;
  }
  return std::nullopt;
}

#endif
