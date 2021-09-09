//
// Created by jcasiano on 27/7/2021.
//

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Graph {
private:
    int n, m;
    vector<vector<int>> adjList;//matriz de adyacencia
    set<pair<int, int>> edges; //guarda

    void _dfs(int v, vector<bool> &vis) {
        vis[v] = true;
        for (int u : adjList[v]) {
            if (!vis[u]) {
                _dfs(u, vis);
            }
        }
    }

public:
    Graph(int n): n(n), adjList(n) {}

    void addEdge(int u, int v) {
        if (!edges.count({u, v})) {
            adjList[v].push_back(u);
            adjList[u].push_back(v);
            edges.insert({u, v});
            edges.insert({v, u});
        }
    }

    void dfs(int v) {
        vector<bool> vis(n, false);
        _dfs(v, vis);
    }

    void bfs(int src) {
        vector<int> dist(n, -1);
        queue<int> q;

        q.push(src);
        dist[src] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adjList[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            cout << dist[i] << ' ';
        }
        cout << endl;
    }

    bool connected(int v, int u) {
        vector<bool> vis(n, false);
        _dfs(v, vis);
        return vis[u];
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 5);
    g.addEdge(3, 4);

    g.bfs(0);


    return 0;
}
