
/* #include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

const int MAX = 1000;
vector<int> tree[MAX];
bool visited[MAX];

void bfs(int start)
{
  queue<int> q;
  q.push(start);

  while (!q.empty())
  {
    int size = q.size();

#pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
      int curr;
#pragma omp critical
      {
        curr = q.front();
        q.pop();
      }

      if (!visited[curr])
      {
        visited[curr] = true;
        cout << curr << " ";

#pragma omp critical
        {
          for (int child : tree[curr])
          {
            if (!visited[child])
              q.push(child);
          }
        }
      }
    }
    cout << endl;
  }
}

int main()
{
  int n, edges, start;
  cout << "Enter number of nodes, edges and starting node: ";
  cin >> n >> edges >> start;

  cout << "Enter edges (parent child):\n";
  for (int i = 0; i < edges; i++)
  {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    // For strict tree, no tree[v].push_back(u);
  }

#pragma omp parallel for
  for (int i = 0; i <= n; i++)
    visited[i] = false;

  cout << "\nBFS Traversal Output:\n";
  bfs(start);

  return 0;
}*/

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

const int MAX = 1000;
vector<int> tree[MAX];
bool visited[MAX];

void bfs(int start)
{
  queue<int> q;
  q.push(start);
  visited[start] = true;

  while (!q.empty())
  {
    int curr = q.front();
    q.pop();
    cout << curr << " ";

   for (size_t i = 0; i < tree[curr].size(); ++i)
{
    int child = tree[curr][i];
    if (!visited[child])
    {
        visited[child] = true;
        q.push(child);
    }
}

  }
  cout << endl;
}

int main()
{
  int n, edges, start;
  cout << "Enter number of nodes, edges and starting node: ";
  cin >> n >> edges >> start;

  cout << "Enter edges (parent child):\n";
  for (int i = 0; i < edges; i++)
  {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    // Not adding reverse edge since it's a directed tree
  }

  // Parallel initialization of visited array
#pragma omp parallel for
  for (int i = 0; i <= n; i++)
    visited[i] = false;

  cout << "\nBFS Traversal Output:\n";
  bfs(start);

  return 0;
}

