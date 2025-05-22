cmake_minimum_required(VERSION 3.16)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: enable static linking if you've built SFML that way
option(SFML_STATIC_LIBRARIES "Link SFML statically" ON)


if(WIN32)
    set(SFML_DIR "C:/Users/ASUS/SFML-install/lib/cmake/SFML")
elseif(APPLE)
    # macOS: install SFML via Homebrew
    set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.0/lib/cmake/SFML")
elseif(UNIX)
    # Linux: install SFML via apt
    set(SFML_DIR "/usr/lib/x86_64-linux-gnu/cmake/SFML")
endif()


# Gather source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

# Include your own project headers
include_directories(include resource)

# Find SFML using modern targets
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Create executable
add_executable(Minesweeper ${SOURCES})

# Link with modern SFML targets
target_link_libraries(Minesweeper SFML::Graphics SFML::Window SFML::System)

# Optional: static libgcc/libstdc++ on Windows
if(WIN32)
    target_link_options(Minesweeper PRIVATE -static-libgcc -static-libstdc++)
endif()
