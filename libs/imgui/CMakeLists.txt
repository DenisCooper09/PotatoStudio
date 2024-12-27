cmake_minimum_required(VERSION 3.24...3.29)
project(imgui VERSION 1.91.6)

set(SOURCES
        src/imgui.cpp
        src/imgui_demo.cpp
        src/imgui_draw.cpp
        src/imgui_impl_glfw.cpp
        src/imgui_impl_opengl3.cpp
        src/imgui_tables.cpp
        src/imgui_widgets.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

set(LIBRARIES
        glad
        glfw
)

include(../Libraries.cmake)
build_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/../.." "${LIBRARIES}")
