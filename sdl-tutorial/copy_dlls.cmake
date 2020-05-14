cmake_minimum_required (VERSION 3.2)

if (WIN32 OR CMAKE_HOST_WIN32)

    set(COPY_DLLS_TARGET "copy_dlls")

    message(STATUS "Setup windows custom target: ${COPY_DLLS_TARGET}")

    set(BINARY_OUTPUT_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")

    add_custom_target(${COPY_DLLS_TARGET}
                      COMMAND ${CMAKE_COMMAND} -E copy
                        "${THIRDPARTY_DIR}/glew/windows/bin/Release/x64/glew32.dll"
                        "${BINARY_OUTPUT_CONFIG}/glew32.dll"

                      COMMAND ${CMAKE_COMMAND} -E copy
                        "${THIRDPARTY_DIR}/SDL2/windows/x64/SDL2.dll"
                        "${BINARY_OUTPUT_CONFIG}/SDL2.dll"

                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      VERBATIM
    )

    add_dependencies(${PROJECT_NAME} ${COPY_DLLS_TARGET})

endif()
