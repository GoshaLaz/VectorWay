#include "library.h"
#include <iostream>
#include <vector>


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