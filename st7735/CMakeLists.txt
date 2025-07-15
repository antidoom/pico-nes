add_library(st7735 INTERFACE)

target_sources(st7735 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/st7735.c)

target_link_libraries(st7735 INTERFACE hardware_spi hardware_gpio)

target_include_directories(st7735 INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)