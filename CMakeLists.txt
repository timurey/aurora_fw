# Always build in release as it uses -Os
SET(CMAKE_BUILD_TYPE DEBUG)

# Handy path variables used in this script and passed to submodules
SET(AURORA_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Lib)

# All compiler related stuff is defined in the toolchain file

IF(NOT STM32_CHIP)
     SET(STM32_CHIP "STM32F205VET6")
     MESSAGE(STATUS "No STM32_CHIP specified, using default: " ${STM32_CHIP})
ENDIF()

IF(NOT TOOLCHAIN_PREFIX)
     SET(TOOLCHAIN_PREFIX "/opt/local/arm-toolchain")
     MESSAGE(STATUS "No TOOLCHAIN_PREFIX specified, using default: " ${TOOLCHAIN_PREFIX})
ENDIF()

# IF(NOT STM32_LINKER_SCRIPT)
#      SET(STM32_LINKER_SCRIPT "../ldscripts/stm32_flash.ld")
#      MESSAGE(STATUS "No STM32_LINKER_SCRIPT specified, using default: " ${STM32_LINKER_SCRIPT})
# ENDIF()

# Using Maple's linker script that corresponds maple/stm32duino code
# SET(STM32_LINKER_SCRIPT ${AURORA_LIBS_DIR}/STM32duino/variants/generic_stm32f103c/ld/bootloader_20.ld)
# LINK_DIRECTORIES(${AURORA_LIBS_DIR}/STM32duino/variants/generic_stm32f103c/ld)

# Flash offset due to bootloader
#SET(VECT_TAB_ADDR "0x08002000")
#SET(STM32_FLASH_ORIGIN "0x08002000")
SET(STM32_MIN_STACK_SIZE 4096)
SET(STM32_MIN_HEAP_SIZE 1024)
# Load the toolchain file that uses vars above
SET(CMAKE_TOOLCHAIN_FILE ../stm32-cmake/cmake/gcc_stm32.cmake)



# Project definition
PROJECT(Aurora)

# Misc stuff
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_LANGUAGE(ASM)

# Project wide definitions
ADD_DEFINITIONS(
	
	-DDEBUG
	-D_WANT_IO_C99_FORMATS
	-DUSE_FULL_ASSERT
	-DHSE_VALUE=25000000
	-DSTM32F205xx
	-DUSE_USB_FS
	-DMCU=${STM32_CHIP}
)

# Project wide include directories
INCLUDE_DIRECTORIES(
	
	# FreeRTOS includes
	${FREERTOS_INCLUDE_DIRS}

	# USBLib includes
	${USBLIB_INCLUDE_DIRS}

	# STM32cube includes
	${STM32CUBE_F2_INCLUDE_DIRS}

	# ORYX Common
	${COMMON_INCLUDE_DIRS}

	# ORYX CycloneTCP
	${CYCLONETCP_INCLUDE_DIRS}

	# FatFs
	${FATFS_INCLUDE_DIRS}

	# Jsmn-extras
	${JSMNEXTRAS_INCLUDE_DIRS}

	# xprintf
	${XPRINTF_INCLUDE_DIRS}

	# Linked list
	${LIST_INCLUDE_DIRS}

	# Common includes
	./include
	${AURORA_INCLUDE_DIRS}

	# Common includes
	${COMMON_INCLUDE_DIRS}

)

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(src)