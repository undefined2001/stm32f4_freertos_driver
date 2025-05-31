set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR Arm)

# Here Goes the Configuration which finds the compiler in Both Windows and Linux
message("#################### OS Info ###################")
message("#                   ${CMAKE_HOST_SYSTEM_NAME}                    #")
message("################################################")

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(TOOLCHAIN_PATH_PREFIX /usr/bin/arm-none-eabi)
    set(TOOLCHAIN_SUFFIX "")
    set(STLINK_PATH)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(TOOLCHAIN_PATH_PREFIX "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/arm-none-eabi")
    set(TOOLCHAIN_SUFFIX ".exe")
    set(STLINK_PATH "C:/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe")
else()
    message(ERROR "Unsupported System")
endif()
#############################################################################

# Setting the Compiler Configurations
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH_PREFIX}-gcc${TOOLCHAIN_SUFFIX})
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH_PREFIX}-gcc${TOOLCHAIN_SUFFIX})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH_PREFIX}-g++${TOOLCHAIN_SUFFIX})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PATH_PREFIX}-objcopy${TOOLCHAIN_SUFFIX})
set(CMAKE_OBJDUMP ${TOOLCHAIN_PATH_PREFIX}-objdump${TOOLCHAIN_SUFFIX})
set(CMAKE_SIZE ${TOOLCHAIN_PATH_PREFIX}-size${TOOLCHAIN_SUFFIX})

set(STARTUP ${CMAKE_SOURCE_DIR}/core/Startup/startup_stm32f446retx.c)
set(LINKER ${CMAKE_SOURCE_DIR}/STM32F446RETX_FLASH.ld)

set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-tree-loop-distribution -fno-exceptions")

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)




