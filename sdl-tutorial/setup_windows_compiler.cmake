cmake_minimum_required (VERSION 3.2)

message(STATUS "Windows host generator selected.")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(HOST_GENERATOR "Visual Studio 16 2019")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /W4 /ZI /RTC1 /DDEBUG /MP")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O3 /MP")

set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /INCREMENTAL /DEBUG:FASTLINK /SAFESEH:NO")

include_directories(
    "${THIRDPARTY_DIR}/glew/windows/include"
)

link_directories(
    "${THIRDPARTY_DIR}/SDL2/windows/x64"
    "${THIRDPARTY_DIR}/glew/windows/lib/x64"
)

set(LIBRARIES
    SDL2
    glew32
    opengl32
    Shcore
)

set(APPLICATION_SOURCES ${APPLICATION_SOURCES}
    "${FRAMEWORK_DIR}/setup_windows_compiler.cmake"
    "${FRAMEWORK_DIR}/copy_dlls.cmake"
)
