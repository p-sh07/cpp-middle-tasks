cmake_minimum_required(VERSION 3.31)
project(module_tasks)

set(CMAKE_CXX_STANDARD 26)

# Настройка общей структуры проекта
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Добавление поддиректорий с программами
add_subdirectory(1_Memory_Resource_Management)
add_subdirectory(2_Templates)
add_subdirectory(3_Algorithms_Data_Structures)
add_subdirectory(4_Ranges_Views)
add_subdirectory(5_Vocabulary_Types)
add_subdirectory(6_Multithreading_Parallelism)