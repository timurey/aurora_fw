# Build rules for GPS logger target.
# App specific compiler/linker settings are also defined here

SET(SOURCE_FILES
	
	./main.c
	./mem.c
	./network.c
	./_write.c
	./newlib.c
	./sdio.c

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

	./CycloneTCP_extras/sntpd.c
	./CycloneTCP_extras/ftpd.c
	./CycloneTCP_extras/httpd.c
	./CycloneTCP_extras/rest/clock.c
#	./CycloneTCP_extras/rest/onewire_rest.c
	./CycloneTCP_extras/rest/powermanagment.c
	./CycloneTCP_extras/rest/sensors.c
	./CycloneTCP_extras/rest/cpu.c
	# ./CycloneTCP_extras/rest/output.c
	./CycloneTCP_extras/rest/rest.c

#	./onewire/ds1820/ds1820.c
#	./onewire/ds1820/ds1820.h
#	./onewire/onewire.c
#	./onewire/onewire.h

	./bsp_driver_sd.c

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
	./CycloneTCP_extras
	./fatfs_extras
	./stuff
	./onewire

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
	CycloneTCP
	Jsmn_extras
	xprintf
	list
)

STM32_SET_TARGET_PROPERTIES(Aurora)
STM32_PRINT_SIZE_OF_TARGETS(Aurora)

# Additional handy targets
STM32_ADD_HEX_BIN_TARGETS(Aurora)
STM32_ADD_DUMP_TARGET(Aurora)
