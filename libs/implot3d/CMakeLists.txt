cmake_minimum_required(VERSION 3.24...3.29)
project(implot3d)

set(SOURCES
        src/implot3d.cpp
        src/implot3d_demo.cpp
        src/implot3d_items.cpp
        src/implot3d_meshes.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

set(LIBRARIES
        imgui
        implot
)

include(../Libraries.cmake)
build_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/../.." "${LIBRARIES}")
