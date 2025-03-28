# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
FILE(GLOB sources src/*.cpp src/*.c)
add_executable(test_project ${sources})

pico_set_program_name(test_project "test_project")
pico_set_program_version(test_project "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(test_project 1)
pico_enable_stdio_usb(test_project 0)

# Add the standard library to the build
target_link_libraries(test_project
        pico_stdlib
        hardware_uart
        hardware_pwm
    )

# Add the standard include files to the build
target_include_directories(test_project PRIVATE inc)

pico_add_extra_outputs(test_project)

