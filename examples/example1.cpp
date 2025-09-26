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

    vector<vector<int>> matrix;


    for (int i = 0; i < n; i++) {
        vector<int> row;
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            row.push_back(a);
        }
        matrix.push_back(row);
    }


    vector<pair<int, int>> p = dfs(startX, startY, matrix);



    for (pair<int, int> p2 : p) {
        cout << p2.first << " " << p2.second << "   ";
    }
}