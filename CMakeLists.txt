cmake_minimum_required(VERSION 3.16)
project(TrailOfExile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    Main.cpp
    Character.cpp
    ConfigLoader.cpp
    GameManager.cpp
    State.cpp
    Weapon.cpp
    Logger.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy the config file next to the built executable so it's found at runtime.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/GameConfig.cfg
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/GameConfig.cfg
)
