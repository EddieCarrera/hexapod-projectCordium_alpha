set(DRIVER_NAME hexapodKinematics)
add_library(${DRIVER_NAME} INTERFACE)

target_sources(${DRIVER_NAME} INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/hexapodKinematics.cpp
  ${CMAKE_CURRENT_LIST_DIR}/vector.cpp
  ${CMAKE_CURRENT_LIST_DIR}/geometry.cpp
)

target_include_directories(${DRIVER_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${DRIVER_NAME} INTERFACE
    pico_stdlib
    )