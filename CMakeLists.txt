cmake_minimum_required(VERSION 3.28)
project(PotatoStudio)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(PS_DEBUG_BUILD)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(PS_RELEASE_BUILD)
endif ()

add_subdirectory(src bin)

target_include_directories(${PROJECT_NAME} PRIVATE include)

set(LIBRARIES
        glad
        glfw
        imgui
        implot
        implot3d
)

include(libs/Libraries.cmake)
build_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}" "${LIBRARIES}")

target_link_options(${PROJECT_NAME} PRIVATE -static)
