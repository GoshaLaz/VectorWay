#include "vectorway/library.h"
#include <bits/stdc++.h>
using namespace std;

using crtMatrix = std::vector<std::vector<std::vector<int>>>;


int n, m;

int myFunction(int x, int y, int z) {
    return 1;
}


int main() {
    cin >> n >> m;
    int startX, startY;
    cin >> startX >> startY;


    crtMatrix matrix = createMatrix(1, m, n, myFunction);

    printMatrix(matrix);

    vector<pair<int, int>> p = dfs(startX, startY, matrix[0]);



    for (pair<int, int> p2 : p) {
        cout << p2.first << " " << p2.second << "   ";
    }

    cout << "\n";

    p = bfs(startX, startY, matrix[0]);

    for (pair<int, int> p2 : p) {
        cout << p2.first << " " << p2.second << "   ";
    }
}