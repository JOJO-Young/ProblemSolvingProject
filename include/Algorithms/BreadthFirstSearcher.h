#ifndef BREADTH_FIRST_SEARCHER
#define BREADTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <queue>
#include <set>

template <typename TGraph>
class BreadthFirstSearcher
{
public:
  static void VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action);
  static std::optional<int> TryFindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate);
};

template <typename TGraph>
void BreadthFirstSearcher<TGraph>::VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action)
{
  std::queue<int> q;
  std::set<int> catched;
  if (graph->ContainsVertex(start))
  {
    q.push(start);
    catched.insert(start);
    while (!q.empty())
    {
      int tmp = q.front();
      q.pop();
      action(tmp);
      for (auto x : graph->GetNeighbors(tmp))
      {
        if (catched.find(x) == catched.end())
        {
          q.push(x);
          catched.insert(x);
        }
      }
    }
  }
}

template <typename TGraph>
std::optional<int> BreadthFirstSearcher<TGraph>::TryFindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate)
{
  std::queue<int> q;
  std::set<int> catched;
  if (graph->ContainsVertex(start))
  {
    q.push(start);
    catched.insert(start);
    while (!q.empty())
    {
      int tmp = q.front();
      q.pop();
      if (predicate(tmp))
        return tmp;
      for (auto x : graph->GetNeighbors(tmp))
      {
        if (catched.find(x) == catched.end())
        {
          q.push(x);
          catched.insert(x);
        }
      }
    }
    return std::nullopt;
  }
  return std::nullopt;
}
#endif