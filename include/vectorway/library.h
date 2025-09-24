#ifndef VECTORWAY_LIBRARY_H
#define VECTORWAY_LIBRARY_H

#include <vector>

std::vector<std::vector<std::vector<int>>> createMatrix(int x, int y, int z, int (*matrixF)(int, int, int));
std::vector<std::vector<std::vector<int>>> rebuildMatrix(int l, int r, int y, int x, int x2, int y2,
    std::vector<std::vector<std::vector<int>>> matrix, int (*matrixF)(int, int, int, int));
std::vector<std::vector<std::vector<int>>> createLayerMatrix(int x, int y, std::vector<std::vector<std::vector<int>>> matrix, int (*matrixF)(int, int));
std::vector<std::vector<std::vector<int>>> deleteMatrix(int l, int r, int x, int y, int x2, int y2, std::vector<std::vector<std::vector<int>>> matrix);
void printMatrix(std::vector<std::vector<std::vector<int>>> matrix);



#endif // VECTORWAY_LIBRARY_H