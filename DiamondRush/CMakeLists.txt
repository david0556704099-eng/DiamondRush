cmake_minimum_required(VERSION 3.16)
project(DiamondRush CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Tile.cpp
    src/Map.cpp
    src/PhysicsEngine.cpp
)
set(HEADERS
    include/Game.h
    include/Common.h
    include/Tile.h
    include/Grid.h
    include/Map.h
    include/PhysicsEngine.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets"
)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
endif()