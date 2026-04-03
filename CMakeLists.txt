cmake_minimum_required(VERSION 3.20)
project(AstralPlane VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(AstralPlane
  src/app/main.cpp
  src/commands/command_dispatch.cpp
  src/body/stats_model.cpp
  src/content/content_loader.cpp
  src/game/harsh_verbs.cpp
  src/game/portal_rift.cpp
  src/game/assimilation.cpp
  src/game/building_storage_heat.cpp
  src/game/ecology_loop.cpp
  src/ui/ui_smoke.cpp
  src/world/start_plane.cpp
  src/world/terrain_model.cpp
  src/save/save_system.cpp
)

set_target_properties(AstralPlane PROPERTIES
  OUTPUT_NAME "AstralPlane"
  SUFFIX ".exe"
)

target_include_directories(AstralPlane PRIVATE src)
