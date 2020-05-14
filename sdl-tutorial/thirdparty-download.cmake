cmake_minimum_required(VERSION 3.2)

# This method was discovered on stackoverflow, I don't remember where exactly. :3
macro(download_lib LIB_NAME CONFIG_FILE)
    if (NOT EXISTS "${THIRDPARTY_DIR}/${LIB_NAME}")

        message(STATUS "Downloading ${LIB_NAME}.")

        configure_file("${CONFIG_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_download/CMakeLists.txt")

        execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                        RESULT_VARIABLE result
                        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_download"
        )

        if (result)
            message(FATAL_ERROR "CMake step for ${LIB_NAME} failed: ${result}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} --build .
                        RESULT_VARIABLE result
                        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_download"
        )

        if (result)
            message(FATAL_ERROR "Build step for ${LIB_NAME} failed: ${result}")
        endif()
    endif()
endmacro()

# Cloning GLM and LodePNG.
download_lib("glm" "${FRAMEWORK_DIR}/glm-config.cmake")
download_lib("lodepng" "${FRAMEWORK_DIR}/lodepng-config.cmake")

include_directories("${THIRDPARTY_DIR}/glm")

if (WIN32 OR CMAKE_HOST_WIN32)
    include_directories("${THIRDPARTY_DIR}/lodepng")

    set (APPLICATION_SOURCES ${APPLICATION_SOURCES}
        "${THIRDPARTY_DIR}/lodepng/lodepng.cpp"
        "${THIRDPARTY_DIR}/lodepng/lodepng.h"
    )
endif()