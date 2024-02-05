set(OUTPUT_NAME oneLegIK)
add_executable(${OUTPUT_NAME} main.cpp)

# As opposed to 'CMAKE_CURRENT_LIST_DIR'
target_include_directories(${OUTPUT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/pimoroni_drivers
        )

target_link_libraries(${OUTPUT_NAME}
        pico_stdlib
        servo2040
        analogmux
        analog
        button
        )

# enable usb output, disable uart output (so it doesn't confuse any connected servos)
pico_enable_stdio_usb(${OUTPUT_NAME} 1)
pico_enable_stdio_uart(${OUTPUT_NAME} 0)

pico_add_extra_outputs(${OUTPUT_NAME})