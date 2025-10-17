cmake_minimum_required(VERSION 3.31)

# Получаем имя директории
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 26)

# Use 1 main for all tasks
file(GLOB SRC_FILES "src/*.cpp")
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)