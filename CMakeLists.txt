cmake_minimum_required(VERSION 3.15)

project(VectorWay VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Dependencies
# -----------------------------

find_package(CURL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# -----------------------------
# Library
# -----------------------------

add_library(VectorWay STATIC
        src/library.cpp
        src/google_maps.cpp
        src/open_street_maps.cpp
)

target_include_directories(VectorWay
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(VectorWay
        PUBLIC
        CURL::libcurl
        nlohmann_json::nlohmann_json
        SFML::Graphics
        SFML::Window
        SFML::System
)

# -----------------------------
# Examples
# -----------------------------

add_executable(example1 examples/example1.cpp)
target_link_libraries(example1 PRIVATE VectorWay)

# -----------------------------
# Install
# -----------------------------

install(TARGETS VectorWay
        EXPORT VectorWayTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include/
        DESTINATION include
)

# -----------------------------
# Export package
# -----------------------------

install(EXPORT VectorWayTargets
        FILE VectorWayTargets.cmake
        NAMESPACE VectorWay::
        DESTINATION lib/cmake/VectorWay
)