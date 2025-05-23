cmake_minimum_required(VERSION 3.16)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable static linking
option(SFML_STATIC_LIBRARIES "Link SFML statically" ON)


if(NOT DEFINED SFML_DIR)
    if(DEFINED ENV{GITHUB_ACTIONS})
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/install")
    elseif(DEFINED ENV{SFML_INSTALL_DIR})
        set(SFML_DIR "$ENV{SFML_INSTALL_DIR}")
    elseif(WIN32 AND EXISTS "${CMAKE_SOURCE_DIR}/SFML/install")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/install")
    else()
        message(WARNING "SFML_DIR is not set; please set it to your SFML install location.")
    endif()
endif()

# Gather source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Exclude anything in the SFML directory
list(FILTER SOURCES EXCLUDE REGEX ".*/SFML/.*")

# Find SFML using modern CMake targets
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
# Executable
add_executable(Minesweeper ${SOURCES})

# Include headers
target_include_directories(Minesweeper PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/resource
)

target_compile_definitions(Minesweeper PRIVATE SFML_STATIC)

# Link SFML statically
target_link_libraries(Minesweeper
    SFML::Graphics
    SFML::Window
    SFML::System
)

# Windows-specific: link runtime statically
if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(Minesweeper PRIVATE -static-libgcc -static-libstdc++)
endif()