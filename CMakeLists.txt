cmake_minimum_required(VERSION 3.31)

include(${CMAKE_SOURCE_DIR}/gcc-arm-none-eabi.cmake)

project(stm32f4_freertos VERSION 0.0 LANGUAGES ASM C CXX)

set(FREERTOS_DIR ${CMAKE_SOURCE_DIR}/freertos)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE SOURCES_DRIVER ${CMAKE_SOURCE_DIR}/driver/*.c)
file(GLOB_RECURSE SOURCES_CC ${CMAKE_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE SOURCES_CPP ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE FREERTOS_SOURCES ${CMAKE_SOURCE_DIR}/freertos/*.c)

list(APPEND SOURCES ${SOURCES_CC})
list(APPEND SOURCES ${SOURCES_CPP})
list(APPEND SOURCES ${SOURCES_DRIVER})
list(APPEND SOURCES ${FREERTOS_SOURCES})

# foreach(ITEM IN LISTS ${SOURCES})
#     message(STATUS ${ITEM})
# endforeach()


list(FILTER SOURCES EXCLUDE REGEX "heap_1.c")
list(FILTER SOURCES EXCLUDE REGEX "heap_2.c")
list(FILTER SOURCES EXCLUDE REGEX "heap_3.c")
list(FILTER SOURCES EXCLUDE REGEX "heap_5.c")

# foreach(SRC IN LISTS SOURCES)
#     file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${SRC})
#     message(STATUS ${REL_PATH})
# endforeach()

include_directories(${CMAKE_SOURCE_DIR}/driver/inc)
include_directories(${CMAKE_SOURCE_DIR}/core/CMSIS/Include)
include_directories(${CMAKE_SOURCE_DIR}/core/CMSIS/Device)
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${FREERTOS_DIR}/include)
include_directories(${FREERTOS_DIR}/portable/GCC/ARM_CM4F)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC ${SOURCES} ${STARTUP})
target_compile_definitions(${PROJECT_NAME} PUBLIC STM32F446xx)

target_compile_options(${PROJECT_NAME} PUBLIC 
    -DSTM32F446xx
    -g
)


target_link_options(${PROJECT_NAME} PUBLIC 
    -T${LINKER}
    -Wl,--print-memory-usage
    -Wl,--gc-sections
    -Wl,-Map=output.map
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND echo "============================================================="
    COMMAND ${CMAKE_SIZE}  ${PROJECT_NAME}.elf
    COMMAND echo "============================================================="
)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
add_custom_target(flash 
    COMMAND st-flash write ${PROJECT_NAME}.bin 0x8000000
)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
add_custom_target(flash
    COMMAND ${STLINK_PATH} -P ${PROJECT_NAME}.bin 0x08000000 -Rst
)
endif()