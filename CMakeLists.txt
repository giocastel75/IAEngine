cmake_minimum_required(VERSION 3.14)

project(IAEngine C CXX)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(external/llama.cpp)

add_executable(IAEngine
    src/main.c
)

target_include_directories(IAEngine PRIVATE
    external/llama.cpp/include
)

target_link_libraries(IAEngine PRIVATE
    llama
)
set_target_properties(IAEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)