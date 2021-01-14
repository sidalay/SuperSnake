cmake_minimum_required(VERSION 3.17)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp src/engine.cpp headers/engine.hpp src/engine_draw.cpp src/engine_input.cpp src/snakesection.cpp headers/snakesection.hpp src/engine_update.cpp src/apple.cpp headers/apple.hpp src/wall.cpp headers/wall.hpp src/engine_textures.cpp src/engine_audio.cpp src/engine_levels.cpp src/engine_text.cpp)

include_directories(headers)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build directory
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()