set(OUTPUT_NAME geometryTest)
add_executable(${OUTPUT_NAME} geometryTest.cpp)

# As opposed to 'CMAKE_CURRENT_LIST_DIR'
target_include_directories(${OUTPUT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/hexapod_kinematics
        )

target_link_libraries(${OUTPUT_NAME}
        vector
        geometry
        )

# enable usb output, disable uart output (so it doesn't confuse any connected servos)
pico_enable_stdio_usb(${OUTPUT_NAME} 1)
pico_enable_stdio_uart(${OUTPUT_NAME} 0)

pico_add_extra_outputs(${OUTPUT_NAME})