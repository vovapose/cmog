cmake_minimum_required(VERSION 3.10)
project(game)

# 1. Ручное указание путей (замените на свои, если отличаются)
set(RAYLIB_INCLUDE_DIR "/usr/local/include")
set(RAYLIB_LIBRARY "/usr/local/lib/libraylib.so")

# 2. Проверяем, существуют ли файлы
if(NOT EXISTS "${RAYLIB_INCLUDE_DIR}/raylib.h")
    message(FATAL_ERROR "Raylib headers not found in ${RAYLIB_INCLUDE_DIR}")
endif()

if(NOT EXISTS "${RAYLIB_LIBRARY}")
    message(FATAL_ERROR "Raylib library not found at ${RAYLIB_LIBRARY}")
endif()

message(STATUS "Raylib include dir: ${RAYLIB_INCLUDE_DIR}")
message(STATUS "Raylib library: ${RAYLIB_LIBRARY}")

# 3. Создаем исполняемый файл и линкуем Raylib
add_executable(game src/main.c src/arrayOperations.c include/arrayOperations.h)
target_include_directories(game PRIVATE ${RAYLIB_INCLUDE_DIR})
target_link_libraries(game PRIVATE ${RAYLIB_LIBRARY} pthread dl GL X11)
