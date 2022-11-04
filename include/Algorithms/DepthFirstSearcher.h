#ifndef DEPTH_FIRST_SEARCHER
#define DEPTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <set>
#include <stack>

template <typename TGraph>
class DepthFirstSearcher
{
public:
  static void VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action);
  static std::optional<int> TryFindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate);
};

template <typename TGraph>
void DepthFirstSearcher<TGraph>::VisitAllVertices(const TGraph *graph, int start, std::function<void(int)> action)
{
  std::stack<int> s;
  std::set<int> catched;
  if (graph->ContainsVertex(start))
  {
    s.push(start);
    while (!s.empty())
    {
      int tmp = s.top();
      if (catched.find(tmp) == catched.end())
      {
        action(tmp);
        catched.insert(tmp);
      }
      bool find = false;
      for (auto x : graph->GetNeighbors(tmp))
      {
        if (catched.find(x) == catched.end())
        {
          s.push(x);
          find = true;
          break;
        }
      }
      if (!find)
        s.pop();
    }
  }
}

template <typename TGraph>
std::optional<int> DepthFirstSearcher<TGraph>::TryFindFirstVertex(const TGraph *graph, int start, std::function<bool(int)> predicate)
{
  std::stack<int> s;
  std::set<int> catched;
  if (graph->ContainsVertex(start))
  {
    s.push(start);
    while (!s.empty())
    {
      int tmp = s.top();
      if (catched.find(tmp) == catched.end())
      {
        if(predicate(tmp))
          return tmp;
        catched.insert(tmp);
      }
      bool find = false;
      for (auto x : graph->GetNeighbors(tmp))
      {
        if (catched.find(x) == catched.end())
        {
          s.push(x);
          find = true;
          break;
        }
      }
      if (!find)
        s.pop();
    }
    return std::nullopt;
  }
  return std::nullopt;
}

#endif
