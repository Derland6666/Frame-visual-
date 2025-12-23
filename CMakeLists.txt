cmake_minimum_required(VERSION 3.25)

# Sets the project name (matches your mod.json ID)
project(derland6666.framevisual)

find_package(Geode REQUIRED)

# Configures the mod build
add_geode_mod(
    derland6666.framevisual
    VERSION v1.0.0
    # Tells CMake where your code is located
    SOURCES src/main.cpp
)

# Optimization for MSVC (Windows) users
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()
