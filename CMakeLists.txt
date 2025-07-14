cmake_minimum_required(VERSION 3.31)
project(chess)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(chess ${SOURCE_FILES}
        include/board.h
        src/Board.cpp
        include/piece.h
        src/Piece.cpp
        include/Pawn.h
        src/Pawn.cpp
        include/Knight.h
        src/Knight.cpp
        include/Rook.h
        src/Rook.cpp
        src/Bishop.cpp
        include/Bishop.h
        src/Queen.cpp
        include/Queen.h
        src/King.cpp
        include/King.h
        include/Position.h
)
target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(chess PRIVATE fmt::fmt spdlog::spdlog)