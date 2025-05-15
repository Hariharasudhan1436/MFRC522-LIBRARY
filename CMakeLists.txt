cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(mfrc522_project)

pico_sdk_init()

add_executable(mfrc522
    main.cpp
    mfrc522.cpp
)

target_link_libraries(mfrc522 pico_stdlib hardware_spi)
pico_add_extra_outputs(mfrc522)
