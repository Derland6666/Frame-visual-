cmake_minimum_required(VERSION 3.25)

project(FrameVisual)

find_package(Geode REQUIRED)

add_geode_mod(
    derland6666.framevisual
    VERSION v1.0.0
    SOURCES src/main.cpp
)

# Link standard libraries if needed for specific platforms
if(WIN32)
    target_compile_definitions(derland6666.framevisual PUBLIC NOMINMAX)
endif()
