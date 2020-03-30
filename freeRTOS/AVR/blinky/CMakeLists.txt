cmake_minimum_required(VERSION 3.5.1)

project(FreeRTOS C)

set(FREERTOS_ROOT /home/jacob/projects/github/FreeRTOS-Kernel)
set(CMAKE_SYSYEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_C_COMPILER avr-gcc)

add_compile_options(-mmcu=atmega32 -O1 -g)
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=atmega32 -g")

add_executable(blinky main.c ${FREERTOS_ROOT}/tasks.c ${FREERTOS_ROOT}/list.c ${FREERTOS_ROOT}/portable/GCC/ATMega323/port.c)
target_include_directories(blinky PRIVATE /usr/lib/avr/include ${FREERTOS_ROOT}/include ../blinky ${FREERTOS_ROOT}/portable/GCC/ATMega323)
