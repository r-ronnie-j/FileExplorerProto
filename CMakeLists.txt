cmake_minimum_required(VERSION 3.22)
project(Home)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_executable(Home main.cpp init.h const.h close.h Components.h Eventhandler.h generator.h)
target_link_libraries(${PROJECT_NAME}  -I./glad SDL2 dl SDL2_image SDL2_ttf)
