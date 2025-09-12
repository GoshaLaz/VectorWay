#include "library.h"
#include <bits/stdc++.h>
using namespace std;

using crtMatrix = std::vector<std::vector<std::vector<int>>>;


int myFunction(int x, int y, int z) {
     return x + y + z;
}

int myFunction2(int x, int y, int z, int g) {

    return g * g;
}

int myFunction3(int x, int y) {

    return 5;
}


int main() {
    int a, b, c;
    cin >> a >> b >> c;

    crtMatrix myMatrix = createMatrix(a, b, c, myFunction);
    printMatrix(myMatrix);

    myMatrix = rebuildMatrix(0, 0, b, c, 0, 0, myMatrix, myFunction2);
    printMatrix(myMatrix);

    myMatrix = createLayerMatrix(b, c, myMatrix, myFunction3);
    printMatrix(myMatrix);

    myMatrix = deleteMatrix(0, 0, b-1, c-1, 0, 0, myMatrix);
    printMatrix(myMatrix);
}
