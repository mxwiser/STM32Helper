cmake_minimum_required(VERSION 3.22)

project(mpu6050)
add_library(mpu6050 INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)



target_include_directories(mpu6050 INTERFACE
        ./
        )
set(sources
        mpu6050.c
        )
target_sources(mpu6050 INTERFACE ${sources})

target_link_directories(mpu6050 INTERFACE
        )

target_link_libraries(mpu6050 INTERFACE
        )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


