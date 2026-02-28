#include "vectorway/open_street_maps.h"
#include "vectorway/library.h"
#include <bits/stdc++.h>

using namespace std;


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
    int cnt2 = 0;
    for (int v : path) {
        cout << "(" << v / m << "," << v % m << ") ";
        if (cnt2 % 3 == 0) {
            cout << "\n";
        }
        cnt2++;
    }
    cout << "\n";
    cout << "Distance = " << dist[t] << "\n";
    cout << "DFS result:\n";
    auto bfsResult = dfs(startX, startY, matrix);
    int cnt = 0;
    for (auto [x, y] : bfsResult) {
        cout << "(" << x << "," << y << ") ";
        if (cnt % 3 == 0) {
            cout << "\n";
        }
        cnt++;
    }
    cout << "\n";

    return 0;
}