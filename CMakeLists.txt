# Always build in release as it uses -Os
SET(CMAKE_BUILD_TYPE Debug)

# Handy path variables used in this script and passed to submodules
SET(AURORA_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Lib)

# All compiler related stuff is defined in the toolchain file
SET(STM32_CHIP "STM32F205VET6")

# Using Maple's linker script that corresponds maple/stm32duino code
# SET(STM32_LINKER_SCRIPT ${AURORA_LIBS_DIR}/STM32duino/variants/generic_stm32f103c/ld/bootloader_20.ld)
LINK_DIRECTORIES(${AURORA_LIBS_DIR}/STM32duino/variants/generic_stm32f103c/ld)

# Flash offset due to bootloader
#SET(VECT_TAB_ADDR "0x08002000")
#SET(STM32_FLASH_ORIGIN "0x08002000")

# Load the toolchain file that uses vars above
SET(CMAKE_TOOLCHAIN_FILE ../stm32-cmake/cmake/gcc_stm32.cmake)



# Project definition
PROJECT(Aurora)

# Misc stuff
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_LANGUAGE(ASM)

# Project wide definitions
ADD_DEFINITIONS(
	-DSTM32F205xx
	-DSTM32F205VET6
	-DMCU_STM32F205VET6
	-DF_CPU=72000000L
	-DARDUINO=10801
	-DDEBUG_LEVEL=DEBUG_NONE
	-DSERIAL_USB
)

# Project wide include directories
INCLUDE_DIRECTORIES(
	# Common includes
	${CMAKE_CURRENT_SOURCE_DIR}/include
	
	# FREErtos includes
	${FREERTOS_INCLUDE_DIRS}
	
	# STM32cube includes
	${STM32CUBE_F2_INCLUDE_DIRS}

	# USBLib includes
	${USBLIB_INCLUDE_DIRS}

	# Common includes
	${COMMON_INCLUDE_DIRS}


	# Arduino core
#	${AURORA_LIBS_DIR}/STM32duino/cores/maple

	# Libmaple/HAL	
#	${AURORA_LIBS_DIR}/STM32duino/system/libmaple
#	${AURORA_LIBS_DIR}/STM32duino/system/libmaple/include
#	${AURORA_LIBS_DIR}/STM32duino/variants/generic_stm32f103c
)

ADD_SUBDIRECTORY(Lib)
ADD_SUBDIRECTORY(Src)

