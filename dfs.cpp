#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int start) {
        vector<bool> visited(V, false);
        stack<int> stk;
        stk.push(start);
        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();
            if (!visited[u]) {
                cout << u << " ";
                visited[u] = true;
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        stk.push(v);
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;
    Graph g(V);
    cout << "Enter the edges (in format 'u v'):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    cout << "DFS starting from vertex 0: ";
    g.dfs(0);
    return 0;
}
