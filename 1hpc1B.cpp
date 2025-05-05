#include <iostream>
#include <vector>
#include <stack>
#include <omp.h> // OpenMP for parallelism
using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int start_node)
{
  stack<int> s;
  s.push(start_node);
  while (!s.empty())
  {
    int curr = s.top();
    s.pop();
    if (!visited[curr])
    {
      visited[curr] = true;
      cout << curr << " ";
      // Push adjacent nodes
      for (int adj : graph[curr])
      {
        if (!visited[adj])
          s.push(adj);
      }
    }
  }
}

int main()
{
  int n, m, start;
  cout << "Enter No of Nodes, Edges, and Start Node: ";
  cin >> n >> m >> start;

  cout << "Enter Edges (u v):\n";
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u); // Undirected graph
  }

// Parallel initialization of visited array
#pragma omp parallel for
  for (int i = 0; i <= n; i++)
    visited[i] = false;

  cout << "DFS Traversal Output: ";
  dfs(start);
}

