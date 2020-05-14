cmake_minimum_required (VERSION 3.2)

if (NOT CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX STREQUAL "")
    message(ERROR "No CMAKE_INSTALL_PREFIX?")
else()

    set(INSTALL_FILES_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/web/index.html"
        "${CMAKE_CURRENT_SOURCE_DIR}/web/module.js"
        "${CMAKE_CURRENT_SOURCE_DIR}/web/styles.css"
        "${CMAKE_CURRENT_BINARY_DIR}/sdl_tutorial.js"
        "${CMAKE_CURRENT_BINARY_DIR}/sdl_tutorial.wasm"
    )

    install(FILES ${INSTALL_FILES_LIST} DESTINATION ${CMAKE_INSTALL_PREFIX})

endif()