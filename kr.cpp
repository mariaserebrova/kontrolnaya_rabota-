#include <iostream>
#include <queue>


using namespace std;

const int V = 6;

int path_from_a_to_b(int new_graph[V][V], int a, int b, int weight[])
{
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    queue <int> queues;
    queues.push(a);
    visited[a] = 1;
    weight[a] = -1;
    int s;
    while (!queues.empty())
    {
        int x = queues.front();
        queues.pop();
        for (s = 0; s < V; s++)
        {
            if (visited[s] == 0 && new_graph[x][s] > 0)
            {
                queues.push(s);
                weight[s] = x;
                visited[s] = 1;
            }
        }
    }
    return (visited[b] == 1);
}

void vertices_from_a(int new_graph[V][V], int a, bool visited[])
{
    visited[a] = 1;
    for (int i = 0; i < V; i++)
        if (new_graph[a][i] && !visited[i])
            vertices_from_a(new_graph, i, visited);
}

void minimum_cut(int Graph[V][V], int a, int b)
{
    int i, j;
    int new_graph[V][V];
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            new_graph[i][j] = Graph[i][j];

    int path[V];
    while (path_from_a_to_b(new_graph, a, b, path))
    {
        int flow = INT_MAX;
        for (j = b; j != a; j = path[j])
        {
            i = path[j];
            flow = min(flow, new_graph[i][j]);
        }

        for (j = b; j != a; j = path[j])
        {
            i = path[j];
            new_graph[i][j] = new_graph[j][i] - flow;
            new_graph[j][i] = new_graph[i][j] + flow;
        }
    }

    bool visited[V];
    for (int k = 0; k < V; k++)
        visited[k] = 0;

    vertices_from_a(new_graph, a, visited);

    for (int k = 0; k < V; k++)
        for (int l = 0; l < V; l++)
            if (visited[k] && visited[l] == 0 && Graph[k][l] != 0)
                cout << k << " -> " << l << endl;
}

int main()
{
    int Graph[V][V] = { {0, 1, 1, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0},
                        {1, 0, 0, 1, 1, 0},
                        {1, 0, 1, 0, 1, 1},
                        {0, 0, 1, 1, 0, 1},
                        {1, 0, 0, 1, 1, 0} };

    cout << "edges contained in the minimum cut of a graph " << endl;

    minimum_cut(Graph, 0, 5); 

    return 0;
}

