#include "library.h"
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cassert>

static constexpr long long INF = std::numeric_limits<long long>::max()/4;


using crtMatrix = std::vector<std::vector<std::vector<int>>>;



crtMatrix createMatrix(int z, int y, int x, int (*matrixF)(int, int, int)) {
    crtMatrix mainMatrix;


    for (int l = 0; l < z; l++) {
        std::vector<std::vector<int>> tempMatrix;
        for (int i = 0; i < y; i++) {
            std::vector<int> tempVector;
            for (int j = 0; j < x; j++) {
                tempVector.push_back(matrixF(l, i, j));
            }
            tempMatrix.push_back(tempVector);
        }
        mainMatrix.push_back(tempMatrix);
    }

    return mainMatrix;
}




crtMatrix rebuildMatrix(int l, int r, int y, int x, int x2, int y2, crtMatrix matrix, int (*matrixF)(int, int, int, int)) {
    for (int h = l; h <= r; h++) {
        for (int i = y2; i < y; i++) {
            for (int j = x2; j < x; j++) {
                matrix[l][i][j] = matrixF(l, i, j, matrix[l][i][j]);
            }
        }
    }

    return matrix;
}


crtMatrix createLayerMatrix(int x, int y, crtMatrix matrix, int (*matrixF)(int, int)) {
    std::vector<std::vector<int>> layerMatrix;

    for (int i = 0; i < y; i++) {
        std::vector<int> tempMatrix;
        for (int j = 0; j < x; j++) {
            tempMatrix.push_back(matrixF(i, j));
        }
        layerMatrix.push_back(tempMatrix);
    }

    matrix.push_back(layerMatrix);
    return matrix;
}



crtMatrix deleteMatrix(int l, int r, int x, int y, int x2, int y2, crtMatrix matrix) {
    for (int h = l; h <= r; h++) {
        for (int i = y2; i < y; i++) {
            matrix[h][i].erase(matrix[h][i].begin() + x2, matrix[h][i].begin() + x + 1);
        }
    }



    return matrix;
}




void printMatrix(crtMatrix matrix) {
    for (int l = 0; l < matrix.size(); l++) {
        for (int i = 0; i < matrix[l].size(); i++) {
            for (int j = 0; j < matrix[l][i].size(); j++) {
                std::cout << matrix[l][i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "\n";
}

std::vector<long long> dijkstra(const Graph& g, int s) {
    const int n = (int)g.size();
    assert(0 <= s && s < n);

    std::vector<long long> dist(n, INF);
    std::vector<char> used(n, 0);
    dist[s] = 0;

    using Node = std::pair<long long,int>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (used[v]) {
            continue;
        }

        used[v] = 1;
        if (d != dist[v]) {
            continue; 
        }

        for (auto [to, w] : g[v]) {
            long long nd = d + (long long)w;
            if (nd < dist[to]) {
                dist[to] = nd;
                pq.push({nd, to});
            }
        }
    }
    return dist;
}

std::pair<std::vector<long long>, std::vector<int>>
dijkstra_to(const Graph& g, int s, int t) {
    const int n = (int)g.size();
    assert(0 <= s && s < n && 0 <= t && t < n);

    std::vector<long long> dist(n, INF);
    std::vector<int> parent(n, -1);
    std::vector<char> used(n, 0);
    dist[s] = 0;

    using Node = std::pair<long long,int>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (used[v]) {
            continue;
        }

        used[v] = 1;
        if (v == t) {
            break;
        }
        
        for (auto [to, w] : g[v]) {
            long long nd = d + (long long)w;
            if (nd < dist[to]) {
                dist[to] = nd;
                parent[to] = v;
                pq.push({nd, to});
            }
        }
    }
    return {dist, parent};
}

std::vector<int> restore_path(int s, int t, const std::vector<int>& parent) {
    std::vector<int> path;
    if (t < 0 || t >= (int)parent.size()) return path;
    for (int v = t; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    if (path.back() != s) {
        return {};
    }
    std::reverse(path.begin(), path.end());
    return path;
}

