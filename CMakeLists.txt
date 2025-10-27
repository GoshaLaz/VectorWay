cmake_minimum_required(VERSION 3.15)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
            "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file"
    )
endif()

project(VectorWay)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(CURL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)



add_library(VectorWay STATIC
        src/library.cpp
        src/google_maps.cpp
        src/open_street_maps.cpp
        include/vectorway/open_street_maps.h
)


include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(VectorWay PUBLIC CURL::libcurl)


target_include_directories(VectorWay PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(VectorWay PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_executable(test1_target
        tests/test1.cpp
        examples/example1.cpp
        include/vectorway/library.h
        examples/example2.cpp
        include/vectorway/external/jsonH.hpp
        include/vectorway/google_maps.h
        include/vectorway/open_street_maps.h
)


target_link_libraries(test1_target PRIVATE
        VectorWay
        CURL::libcurl
        nlohmann_json::nlohmann_json
)

target_include_directories(test1_target PRIVATE ${PROJECT_SOURCE_DIR}/include)
