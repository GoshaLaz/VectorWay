#ifndef VECTORWAY_LIBRARY_H
#define VECTORWAY_LIBRARY_H

#include <vector>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

std::vector<std::vector<std::vector<int>>> createMatrix(int z, int y, int x, int (*matrixF)(int, int, int));
std::vector<std::vector<std::vector<int>>> rebuildMatrix(int l, int r, int y, int x, int x2, int y2,
    std::vector<std::vector<std::vector<int>>> matrix, int (*matrixF)(int, int, int, int));
std::vector<std::vector<std::vector<int>>> createLayerMatrix(int x, int y, std::vector<std::vector<std::vector<int>>> matrix, int (*matrixF)(int, int));
std::vector<std::vector<std::vector<int>>> deleteMatrix(int l, int r, int x, int y, int x2, int y2, std::vector<std::vector<std::vector<int>>> matrix);
void printMatrix(std::vector<std::vector<std::vector<int>>> matrix);
std::vector<std::pair<int, int>> dfs(int startX, int startY, const std::vector<std::vector<int>>& grid);
std::vector<std::pair<int, int>> bfs(int startX, int startY, const std::vector<std::vector<int>>& grid);
std::vector<long long> dijkstra(const Graph& g, int s);
std::pair<std::vector<long long>, std::vector<int>> dijkstra_to(const Graph& g, int s, int t);
std::vector<int> restore_path(int s, int t, const std::vector<int>& parent);


#endif // VECTORWAY_LIBRARY_H