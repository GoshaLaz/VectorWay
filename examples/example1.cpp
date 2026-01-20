#include "vectorway/open_street_maps.h"
#include "vectorway/library.h"
#include <bits/stdc++.h>

using namespace std;


using Graph = std::vector<std::vector<std::pair<int, int>>>;
Graph matrixToGraph(const vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    auto id = [&](int x, int y) {
        return x * m + y;
    };

    Graph g(n * m);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) continue;

            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    if (grid[ni][nj] == 1) {
                        g[id(i, j)].push_back({id(ni, nj), 1});
                    }
                }
            }
        }
    }
    return g;
}


int main() {
    double south = 50.45000;
    double west  = 30.52390;
    double north = 50.45070;
    double east  = 30.52470;


    int startX, startY;
    cin >> startX >> startY;

    auto matrix = roadsToMatrix(getRoadsFromOSM(south, west, north, east),10, 10);
    cout << "Matrix:\n";
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    int n = matrix.size();
    int m = matrix[0].size();
    Graph g = matrixToGraph(matrix);
    auto id = [&](int x, int y) {
        return x * m + y;
    };
    int s = id(startX, startY);
    int t = id(4, 9);

    auto [dist, parent] = dijkstra_to(g, s, t);
    auto path = restore_path(s, t, parent);
    for (int v : path) {
        cout << "(" << v / m << "," << v % m << ") ";
    }
    cout << "\n";
    cout << "Distance = " << dist[t] << "\n";
    cout << "BFS result:\n";
    auto bfsResult = bfs(startX, startY, matrix);
    int cnt = 0;
    for (auto [x, y] : bfsResult) {
        cout << "(" << x << "," << y << ") ";
        if (cnt % 2 > 0) {
            cout << "\n";
        }
        cnt++;
    }
    cout << "\n";

    return 0;
}
