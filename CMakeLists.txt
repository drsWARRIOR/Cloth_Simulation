cmake_minimum_required(VERSION 3.15)

project(Cloth_Simulation)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# === SFML Submodule Directory ===
set(SFML_DIR ${CMAKE_SOURCE_DIR}/third-party/SFML)

# Include SFML headers
include_directories(${SFML_DIR}/include)

# Include your project headers
include_directories(${CMAKE_SOURCE_DIR}/includes)

# === SFML Submodule Configuration ===
if(EXISTS "${SFML_DIR}/CMakeLists.txt")
    add_subdirectory(${SFML_DIR} EXCLUDE_FROM_ALL)
else()
    message(FATAL_ERROR "SFML submodule not initialized or missing: expected CMakeLists.txt in ${SFML_DIR}")
endif()

# === Collect Source and Header Files ===
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/includes/*.h)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Group sources for IDEs
source_group("src" FILES ${SOURCES})
source_group("includes" FILES ${HEADERS})

# === Link SFML ===
target_link_libraries(${PROJECT_NAME} PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)

# To avoid path for data folder mismatch among different developement and runtime enviroment
target_compile_definitions(${PROJECT_NAME} PRIVATE
        DATA_PATH="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data/"
)

# Link math library on Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC m)
endif()

# === macOS Specific Settings ===
if(APPLE)
    message(STATUS "Building for macOS")

    # Link Cocoa, OpenGL and other required frameworks
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKit_LIBRARY IOKit)
    find_library(CoreVideo_LIBRARY CoreVideo)

    target_link_libraries(${PROJECT_NAME} PUBLIC
            ${COCOA_LIBRARY}
            ${OpenGL_LIBRARY}
            ${IOKit_LIBRARY}
            ${CoreVideo_LIBRARY}
    )
endif()

# === Copy arial.ttf into bin/data directory ===
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/assets/arial.ttf
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/data/arial.ttf
)
