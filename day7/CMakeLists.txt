cmake_minimum_required(VERSION 3.10)

add_executable(day7 day7.cxx)

target_link_libraries(day7 PUBLIC utilities)

target_include_directories(day7 PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/utilities"
                          )
