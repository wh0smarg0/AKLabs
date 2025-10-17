cmake_minimum_required(VERSION 3.10)
project(SimpleCalculator)

set(CMAKE_CXX_STANDARD 17)

# Статична бібліотека з calculator.cpp
add_library(calc STATIC src/calculator.cpp)

# Виконуваний файл
add_executable(app src/main.cpp)

# Додаємо заголовки
target_include_directories(calc PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Лінкуємо бібліотеку до виконуваного файлу
target_link_libraries(app PRIVATE calc)
