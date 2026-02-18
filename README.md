
VectorWay
=========

VectorWay is a C++ library for digitizing, modeling, and analyzing road networks.
It provides tools for building graph-based transportation models, performing graph
traversal and shortest-path computations, and working with real-world map data
from OpenStreetMap via the Overpass API.

The library is implemented using C++ and the Standard Template Library (STL) and
focuses on performance, modularity, and ease of integration.

Overview
--------
Modern transportation systems require efficient routing and traffic optimization
solutions. VectorWay addresses this challenge by offering a lightweight yet powerful
set of tools for implementing routing algorithms and working with real transportation
data in a flexible programming environment.

Features
--------
- Graph-based road network representation
- Depth-First Search (DFS) and Breadth-First Search (BFS)
- Shortest path computation using Dijkstra’s algorithm
- Path restoration between graph nodes
- Integration with OpenStreetMap via the Overpass API
- Conversion of real road data into grid-based structures
- Modular and extensible architecture

Architecture
------------
- include/ – public headers and interfaces
- src/ – core algorithm implementations
- lib/ – compiled static library
- examples/ – usage examples
- tests/ – basic tests

Algorithms
----------
VectorWay implements classical routing and traversal algorithms including DFS, BFS,
and Dijkstra’s algorithm for weighted shortest-path routing.

OpenStreetMap Support
--------------------
The library retrieves real road data using the Overpass API, with HTTP requests
handled by libcurl and JSON parsing via nlohmann/json. Road data is converted into
grid or graph representations suitable for routing and analysis.

Technologies
------------
C++, STL, CMake, libcurl, OpenStreetMap / Overpass API, nlohmann/json
