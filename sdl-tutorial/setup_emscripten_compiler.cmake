cmake_minimum_required (VERSION 3.2)

message(STATUS "Emscripten host generator selected.")

set(HOST_GENERATOR "Unix Makefiles")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Min memory is 64MB.
# --bind needed to bind a cpp functions for call from js.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s TOTAL_MEMORY=67108864 --bind -O3")

link_directories("${THIRDPARTY_DIR}/SDL2/emscripten")

set(LIBRARIES -lSDL2)
