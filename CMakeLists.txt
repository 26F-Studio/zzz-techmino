cmake_minimum_required(VERSION 3.0.0)
project(zzz VERSION 0.1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
add_library(${PROJECT_NAME} SHARED
    zzz_techmino.cpp
    zzz/ai_zzz.cpp
    zzz/integer_utils.cpp
    zzz/random.cpp
    zzz/rule_srs.cpp
    zzz/rule_toj.cpp
    zzz/search_tspin.cpp
    zzz/tetris_core.cpp
)
target_link_directories(${PROJECT_NAME} PUBLIC lib)
target_link_libraries(${PROJECT_NAME} lua51)
target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PUBLIC zzz
)

project(zzz_test VERSION 0.1.0)
add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} lua51 zzz)
