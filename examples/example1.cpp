#include "vectorway/open_street_maps.h"
#include "vectorway/library.h"
#include <bits/stdc++.h>


using namespace std;

int main() {
    double south = 50.4420;
    double west  = 30.5190;
    double north = 50.4480;
    double east  = 30.5300;


    auto matrix = roadsToMatrix(getRoadsFromOSM(south, west, north, east), 3, 3);

    vector<pair<int, int>> result;

    result = bfs(0, 0, matrix);
    cout << matrix[0][0] << "\n";

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (auto p : result) {
        cout << p.first << " " << p.second << "\n";
    }


    return 0;
}
