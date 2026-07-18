cmake_minimum_required(VERSION 3.5)
project(patience)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glm EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glad EXCLUDE_FROM_ALL)
add_subdirectory(vendor/json EXCLUDE_FROM_ALL)

add_executable(patience WIN32)

target_sources(patience
  PRIVATE
    src/main.cpp
    src/renderer/renderer.cpp
    src/renderer/texture.cpp
    src/game/game_object.cpp
    src/game/game.cpp
    src/game/components/animation_component.cpp
    src/game/components/graphic_component.cpp
    src/game/components/physics_component.cpp
    src/game/components/player_component.cpp
)

target_link_libraries(patience 
  PRIVATE 
    SDL3::SDL3
    glad
    glm::glm-header-only
    nlohmann_json::nlohmann_json
)
target_include_directories(patience PRIVATE vendor/stb_image/)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets"
)
add_dependencies(${PROJECT_NAME} copy_assets)
