cmake_minimum_required(VERSION 3.24...3.29)
project(implot)

set(SOURCES
        src/implot.cpp
        src/implot_demo.cpp
        src/implot_items.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

set(LIBRARIES
        imgui
)

include(../Libraries.cmake)
build_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/../.." "${LIBRARIES}")
