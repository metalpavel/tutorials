cmake_minimum_required (VERSION 3.2)

set(APPLICATION_SOURCES ${APPLICATION_SOURCES}
    "${FRAMEWORK_DIR}/src/framework/sources.cmake"
    "${FRAMEWORK_DIR}/src/framework/application_main.cpp"
    "${FRAMEWORK_DIR}/src/framework/application_main.hpp"
    "${FRAMEWORK_DIR}/src/framework/iapplication.hpp"
    "${FRAMEWORK_DIR}/src/framework/opengl.hpp"
    "${FRAMEWORK_DIR}/src/framework/main.cpp"
    "${FRAMEWORK_DIR}/src/framework/sdl_window.cpp"
    "${FRAMEWORK_DIR}/src/framework/sdl_window.hpp"
    "${FRAMEWORK_DIR}/src/framework/shader.cpp"
    "${FRAMEWORK_DIR}/src/framework/shader.hpp"
)
