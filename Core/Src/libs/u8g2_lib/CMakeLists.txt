cmake_minimum_required(VERSION 3.22)

project(u8g2)
add_library(u8g2 INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)



target_include_directories(u8g2 INTERFACE
        ./
        )
set(sources
        u8g2_bitmap.c
        u8g2_box.c
        u8g2_buffer.c
        u8g2_circle.c
        u8g2_cleardisplay.c
        u8g2_com_stm32_hw_spi_hal.c
        u8g2_d_memory.c
        u8g2_d_setup.c
        u8g2_font.c
        u8g2_fonts.c
        u8g2_hvline.c
        u8g2_input_value.c
        u8g2_intersection.c
        u8g2_kerning.c
        u8g2_line.c
        u8g2_ll_hvline.c
        u8g2_message.c
        u8g2_polygon.c
        u8g2_selection_list.c
        u8g2_setup.c
        u8log_u8g2.c
        u8log_u8x8.c
        u8log.c
        u8x8_8x8.c
        u8x8_byte.c
        u8x8_cad.c
        u8x8_capture.c
        u8x8_d_ssd1306_128x64_noname.c
        u8x8_debounce.c
        u8x8_display.c
        u8x8_fonts.c
        u8x8_gpio.c
        u8x8_input_value.c
        u8x8_message.c
        u8x8_selection_list.c
        u8x8_setup.c
        u8x8_string.c
        u8x8_u8toa.c
        u8x8_u16toa.c

        )
target_sources(u8g2 INTERFACE ${sources})

target_link_directories(u8g2 INTERFACE
        )

target_link_libraries(u8g2 INTERFACE
        )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


