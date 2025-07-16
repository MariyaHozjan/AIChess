cmake_minimum_required(VERSION 3.31)
project(chess)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(chess ${SOURCE_FILES})
target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(chess PRIVATE fmt::fmt spdlog::spdlog)