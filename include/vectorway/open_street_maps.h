#pragma once
#include <string>
#include <vector>
#include "vectorway/external/jsonH.hpp"

struct OSMRoad {
    std::string id;
    std::string name;
    std::string type;
    std::vector<std::pair<double, double>> coordinates;
};

std::vector<OSMRoad> getRoadsFromOSM(
    double south, double west,
    double north, double east
);

std::vector<std::vector<int>> roadsToMatrix(
    const std::vector<OSMRoad>& roads
);

std::vector<std::vector<int>> roadsToMatrix(
    const std::vector<OSMRoad>& roads,
    int gridHeight,
    int gridWidth
);