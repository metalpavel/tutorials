cmake_minimum_required(VERSION 3.2)

project(lodepng_download NONE)

include(ExternalProject)

ExternalProject_Add(lodepng
    GIT_REPOSITORY    https://github.com/lvandeve/lodepng.git
    GIT_TAG           master
    SOURCE_DIR        "${THIRDPARTY_DIR}/lodepng"
    BINARY_DIR        ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)
