cmake_minimum_required (VERSION 3.2)

set(PROJECT_NAME "texture_tutorial")

project(${PROJECT_NAME})

set(APPLICATION_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/box_mesh.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/texture_tutorial_app.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/texture_tutorial_app.hpp"
)

# Setting a directory with compiler options and framework.
get_filename_component(FRAMEWORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../sdl-tutorial" ABSOLUTE)

# File with installation target for Emscripten toolchain.
set(INSTALL_CMAKE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/install.cmake")

include("${FRAMEWORK_DIR}/CMakeLists.txt")

if (WIN32 OR CMAKE_HOST_WIN32)

    set(BINARY_OUTPUT_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")

    # Copying resources to target folder.
    add_custom_target(copy_data
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "${CMAKE_CURRENT_SOURCE_DIR}/data/retrocastle.png"
                        "${BINARY_OUTPUT_CONFIG}/retrocastle.png"

                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        VERBATIM
    )

    add_dependencies(${PROJECT_NAME} copy_data)

endif()
