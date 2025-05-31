set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR Arm)


if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")

    message("#################### OS Info ###################")
    message("#                   Linux                      #")
    message("################################################")


    set(TOOLCHAIN_PATH_PREFIX /usr/bin/arm-none-eabi)
    set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH_PREFIX}-gcc)
    set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH_PREFIX}-g++)
    set(CMAKE_OBJCOPY ${TOOLCHAIN_PATH_PREFIX}-objcopy)
    set(CMAKE_OBJDUMP ${TOOLCHAIN_PATH_PREFIX}-objdump)
    set(CMAKE_SIZE ${TOOLCHAIN_PATH_PREFIX}-size)

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    message("This is a Windows System")
else()
    message(ERROR "Unsupported System")
endif()




set(STARTUP ${CMAKE_SOURCE_DIR}/core/Startup/startup_stm32f446retx.c)
set(LINKER ${CMAKE_SOURCE_DIR}/STM32F446RETX_FLASH.ld)

set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-tree-loop-distribution -fno-exceptions")

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)