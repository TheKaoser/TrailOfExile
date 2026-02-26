cmake_minimum_required(VERSION 3.16)
project(TrailOfExile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    Main.cpp
    Character.cpp
    GameManager.cpp
    State.cpp
    Weapon.cpp
    Logger.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
