cmake_minimum_required(VERSION 3.15)
project(VectorWay)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${PROJECT_SOURCE_DIR}/include)



add_library(VectorWay STATIC
        src/library.cpp
)

target_include_directories(VectorWay PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(VectorWay PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)




add_executable(test1_target tests/test1.cpp
        examples/example1.cpp
        include/vectorway/library.h)
target_link_libraries(test1_target PRIVATE VectorWay)
target_include_directories(test1_target PRIVATE ${PROJECT_SOURCE_DIR}/include)
