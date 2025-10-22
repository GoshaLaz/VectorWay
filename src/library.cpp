#include "vectorway/library.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "vectorway/external/jsonH.hpp"
#include "curl/curl.h"
using crtMatrix = std::vector<std::vector<std::vector<int>>>;
using matrix2D = std::vector<std::vector<int>>;




crtMatrix createMatrix(int z, int y, int x, int (*matrixF)(int, int, int)) {
    crtMatrix mainMatrix;

    for (int l = 0; l < z; l++) {
        matrix2D tempMatrix;
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
     matrix2D layerMatrix;

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



std::vector<std::pair<int, int>> dfs(int startX, int startY, const matrix2D& grid) {
    int n = int(grid.size());
    int m = int(grid[0].size());

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    std::stack<std::pair<int, int>> st;

    std::vector<std::pair<int, int>> result;


    if (grid[startX][startY] == 1) {
        st.emplace(startX, startY);
    }


    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!st.empty()) {
        auto [x, y] = st.top();
        st.pop();

        if (visited[x][y]) {
            continue;
        }


        visited[x][y] = true;
        result.emplace_back(x, y);


        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (grid[nx][ny] == 1 && !visited[nx][ny]) {
                    st.emplace(nx, ny);
                }
            }
        }
    }


    return result;
}



std::vector<std::pair<int, int>> bfs(int startX, int startY, const matrix2D& grid) {
    int n = int(grid.size());
    int m = int(grid[0].size());

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    std::queue<std::pair<int, int>> q;

    std::vector<std::pair<int, int>> result;


    if (grid[startX][startY] == 1) {
        q.emplace(startX, startY);
    }


    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (visited[x][y]) {
            continue;
        }


        visited[x][y] = true;
        result.emplace_back(x, y);


        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (grid[nx][ny] == 1 && !visited[nx][ny]) {
                    q.emplace(nx, ny);
                }
            }
        }
    }


    return result;
}