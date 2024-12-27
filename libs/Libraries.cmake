set(BUILT_LIBRARIES "" CACHE INTERNAL "List of already built libraries")

function(build_libraries target dir LIBRARIES)
    foreach (LIBRARY IN LISTS LIBRARIES)
        message("================================================================")
        message("[INFO] Processing '${LIBRARY}' for '${target}'")

        set(LIBRARY_DIRECTORY ${dir}/libs/${LIBRARY})
        set(LIBRARY_BINARY_DIRECTORY ${CMAKE_BINARY_DIR}/libs/${LIBRARY})

        message("[INFO] Library directory: ${LIBRARY_DIRECTORY}")
        message("[INFO] Library binary directory: ${LIBRARY_BINARY_DIRECTORY}")

        if (NOT EXISTS ${LIBRARY_DIRECTORY}/CMakeLists.txt)
            message("[ERROR] CMakeLists.txt could not be found for '${LIBRARY}'. Continuing to the next library.")
            continue()
        endif ()

        if (LIBRARY IN_LIST BUILT_LIBRARIES)
            message("[INFO] '${LIBRARY}' is already built. Skipping build process...")
        else ()
            message("[INFO] Found CMakeLists.txt for '${LIBRARY}'. Building...")
            add_subdirectory(${LIBRARY_DIRECTORY} ${LIBRARY_BINARY_DIRECTORY})
        endif ()

        message("[INFO] Linking '${LIBRARY}' to '${target}'...")
        target_link_libraries(${target} PRIVATE ${LIBRARY})
        target_include_directories(${target} PRIVATE ${LIBRARY_DIRECTORY}/include)

        list(APPEND BUILT_LIBRARIES ${LIBRARY})
        set(BUILT_LIBRARIES "${BUILT_LIBRARIES}" CACHE INTERNAL "List of already built libraries")
    endforeach ()
endfunction()
