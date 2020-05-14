cmake_minimum_required(VERSION 3.2)

project(glm_download NONE)

include(ExternalProject)

ExternalProject_Add(glm
    GIT_REPOSITORY    https://github.com/g-truc/glm.git
    GIT_TAG           master
    SOURCE_DIR        "${THIRDPARTY_DIR}/glm"
    BINARY_DIR        ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)
