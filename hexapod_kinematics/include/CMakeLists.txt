set(DRIVER_NAME hexapodKinematics)
add_library(${DRIVER_NAME} INTERFACE)

target_sources(${DRIVER_NAME} INTERFACE
  ${PROJECT_SOURCE_DIR}/hexapodKinematics.cpp
  ${PROJECT_SOURCE_DIR}/vector.cpp
  ${PROJECT_SOURCE_DIR}/geometry.cpp
  ${PROJECT_SOURCE_DIR}/solvers/ik/IKinfo.cpp
  ${PROJECT_SOURCE_DIR}/solvers/ik/LinkageIKSolver.cpp
)

target_include_directories(${DRIVER_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${DRIVER_NAME} INTERFACE
    pico_stdlib
    )