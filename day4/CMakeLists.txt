cmake_minimum_required(VERSION 3.10)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -O2 -Werror=implicit-function-declaration")

add_executable(day4 day4.cxx)
