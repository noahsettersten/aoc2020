cmake_minimum_required(VERSION 3.10)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -O2 -Werror=implicit-function-declaration")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project("AoC 2020")

add_subdirectory(utilities)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
# add_subdirectory(day5)
# add_subdirectory(day6)
add_subdirectory(day7)
