# Build rules for GPS logger target.
# App specific compiler/linker settings are also defined here

SET(SOURCE_FILES
	
	./_write.c
	./driver/src/DataManager.c
	./driver/src/DriverInterface.c

	./driver/src/devices/gpio_driver.c
	./driver/src/devices/gpio_driver.h
	./driver/src/devices/test_driver.c

	./expression_parser/expression_parser.c
	./expression_parser/expression_parser.h
	./expression_parser/logic.c
	./expression_parser/logic.h
	./expression_parser/variables_def.h
	./main.c
	./mem.c
	./network.c

	./onewire/ds1820/ds1820.c
	./onewire/ds1820/ds1820.h
	./onewire/onewire.c
	./onewire/onewire.h

	./sdio/bsp_driver_sd.c
	./sdio/bsp_driver_sd.h
	./sdio/sd_diskio.c
	./sdio/sd_diskio.h
	./sdio/sdio.c
	./sdio/sdio.h
	./stm32f2xx_it.c

	./stuff/configs.c
	./stuff/configs.h
	./stuff/gpio.c
	./stuff/gpio.h
	./stuff/macros.h
	./stuff/rtc.c
	./stuff/rtc.h
	./stuff/uuid.c
	./stuff/uuid.h
	./usbd_cdc_if.c
	./usbd_conf.c
	./usbd_desc.c

)

INCLUDE_DIRECTORIES(
	.
	./driver/include
	# ${AURORA_LIBS_DIR}/USBlib/core/inc
	# ${AURORA_LIBS_DIR}/USBlib/class/cdc/inc

	${AURORA_LIBS_DIR}/stm32cube_f2/STM32F2xx_HAL_Driver/Inc
	${AURORA_LIBS_DIR}/stm32cube_f2/CMSIS/Device/ST/STM32F2xx/Include/
	${AURORA_LIBS_DIR}/stm32cube_f2/CMSIS/Include/

	${AURORA_LIBS_DIR}/Common
	${AURORA_LIBS_DIR}/fatfs
	${AURORA_LIBS_DIR}/FreeRTOS
	)


# Do not link to libc or newlib-nano - we are not using anything from that
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")

ADD_EXECUTABLE(Aurora ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(Aurora LINK_PUBLIC
	FreeRTOS
	USBLib
	STM32Cube_f2
	
	Common
	Fatfs
)

STM32_SET_TARGET_PROPERTIES(Aurora)
STM32_PRINT_SIZE_OF_TARGETS(Aurora)

# Additional handy targets
STM32_ADD_HEX_BIN_TARGETS(Aurora)
STM32_ADD_DUMP_TARGET(Aurora)
