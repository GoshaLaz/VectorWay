#include "library.h"
#include <bits/stdc++.h>
using namespace std;

using crtMatrix = std::vector<std::vector<std::vector<int>>>;


vector<int> value;
int indexValue = 0;
int myFunction(int z, int y, int x) {
    indexValue++;
    return value[indexValue-1];
}

int myFunction2(int z, int y, int x, int g) {
    return g*g;
}


int myFunction3(int y, int x) {

    return x+y;
}


int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    for (int i = 0; i < b * c * a; i++) {
        int number;
        cin >> number;
        value.push_back(number);
    }





    crtMatrix myMatrix = createMatrix(a, b, c, myFunction);
    printMatrix(myMatrix);

    myMatrix = rebuildMatrix(d, a-1, b, c, myMatrix, myFunction2);
    printMatrix(myMatrix);

    myMatrix = createLayerMatrix(5, 5, myMatrix, myFunction3);
    printMatrix(myMatrix);

    myMatrix = deleteMatrix(0, 0, a, b, myMatrix);
    printMatrix(myMatrix);
}
