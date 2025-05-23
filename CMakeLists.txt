cmake_minimum_required(VERSION 3.16)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable static linking
option(SFML_STATIC_LIBRARIES "Link SFML statically" ON)
add_definitions(-DSFML_STATIC)

if(NOT DEFINED SFML_DIR)
    if(DEFINED ENV{GITHUB_ACTIONS})
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/build")
    elseif(WIN32 AND EXISTS "C:/Users/ASUS/SFML-install/lib/cmake/SFML")
        set(SFML_DIR "C:/Users/ASUS/SFML-install/lib/cmake/SFML")
    endif()
endif()

# Gather source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

# Include headers
include_directories(include resource)

# Find SFML using modern CMake targets
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Executable
add_executable(Minesweeper ${SOURCES})

# Link SFML statically
target_link_libraries(Minesweeper
    SFML::Graphics
    SFML::Window
    SFML::System
)

# Windows-specific: link runtime statically
if(WIN32)
    target_link_options(Minesweeper PRIVATE -static-libgcc -static-libstdc++)
endif()
