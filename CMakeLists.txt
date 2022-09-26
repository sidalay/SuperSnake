cmake_minimum_required(VERSION 3.17)
project(SuperSnake)

find_package(SFML 2.5.1 COMPONENTS graphics audio network window system REQUIRED)
if (NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/engine.cpp 
    src/apple.cpp 
    src/engine_audio.cpp 
    src/engine_draw.cpp 
    src/engine_input.cpp 
    src/engine_levels.cpp 
    src/engine_text.cpp 
    src/engine_textures.cpp 
    src/engine_update.cpp 
    src/snakesection.cpp 
    src/wall.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio sfml-network)
target_include_directories(${PROJECT_NAME} PRIVATE include ${SFML_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})