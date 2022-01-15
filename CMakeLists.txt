cmake_minimum_required(VERSION 3.0.0)
project(zzz_techmino VERSION 0.1.0)

add_library(${PROJECT_NAME} SHARED zzz_techmino.cpp)
target_link_directories(${PROJECT_NAME} PUBLIC lib)
target_link_libraries(${PROJECT_NAME} lua51)
target_include_directories(${PROJECT_NAME} PUBLIC include)
