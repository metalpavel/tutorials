cmake_minimum_required (VERSION 3.2)

# If PROJECT_NAME doesn't exists then default tutorial will be set.

if (NOT PROJECT_NAME OR PROJECT_NAME STREQUAL "")

    set(PROJECT_NAME "sdl_tutorial") # as default tutorial

    project(${PROJECT_NAME})

    set(APPLICATION_SOURCES ${APPLICATION_SOURCES}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_tutorial_app.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl_tutorial_app.hpp"
    )
    
    # File with installation target for Emscripten toolchain.
    set(INSTALL_CMAKE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/install.cmake")

    # For this tutorial (sdl_tutorial) is same folder.
    set(FRAMEWORK_DIR ${CMAKE_CURRENT_SOURCE_DIR})

endif()

message(STATUS "Project ${PROJECT_NAME}")

get_filename_component(THIRDPARTY_DIR "${FRAMEWORK_DIR}/../thirdparty" ABSOLUTE)

# Downloading 3rdparty libraries.
include("${FRAMEWORK_DIR}/thirdparty-download.cmake")

# ================
# Setup compilers.
# ================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32 OR CMAKE_HOST_WIN32)

    include("${FRAMEWORK_DIR}/setup_windows_compiler.cmake")

elseif (EMSCRIPTEN)

    include("${FRAMEWORK_DIR}/setup_emscripten_compiler.cmake")

else()

    message(FATAL_ERROR "Unknown host compiler!")

endif()

# ==============
# Setup sources.
# ==============

include_directories(
    "${THIRDPARTY_DIR}/SDL2/include"
    "${FRAMEWORK_DIR}/src"
)

include("${FRAMEWORK_DIR}/src/framework/sources.cmake")

# APPLICATION_SOURCES setted in 'sources.cmake' file.
add_executable(${PROJECT_NAME}
    ${APPLICATION_SOURCES}
)

# LIBRARIES setted in specific '*compiler.cmake' file.
target_link_libraries (${PROJECT_NAME} ${LIBRARIES})

# ==============

# Setup target for copying dlls of SDL2 and glew32 to binary output folder. (Windows only)
if (WIN32 OR CMAKE_HOST_WIN32)
    include("${FRAMEWORK_DIR}/copy_dlls.cmake")
endif()

# Installation target for Emscripten.
if (EMSCRIPTEN AND INSTALL_CMAKE_FILE)
    include("${INSTALL_CMAKE_FILE}")
endif()
