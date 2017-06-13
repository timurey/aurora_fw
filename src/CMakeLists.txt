# Build rules for GPS logger target.
# App specific compiler/linker settings are also defined here

SET(SOURCE_FILES
	
	./adc.c
	./blink.c
	./ff_demo.c
	./freertos.c
	./rtc.c
	./stm32f2xx_it.c
	./usb_device.c
	./bsp_driver_sd.c
	./sdio.c
	./system_stm32f2xx.c
	./usbd_cdc_if.c
	./dma.c
	./gpio.c
	./stm32f2xx_hal_msp.c
	./tim.c
	./usbd_conf.c
	./fatfs.c
	./main.c
	./stm32f2xx_hal_timebase_TIM.c usart.c
	./usbd_desc.c
	./_write.c

)

INCLUDE_DIRECTORIES(
	.
	./driver/include
	# ./CycloneTCP_extras
	# ./fatfs_extras
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
	cmsis
	Common
	Fatfs
	# CycloneTCP
	# Jsmn_extras
	xprintf
	# list
)

STM32_SET_TARGET_PROPERTIES(Aurora)
STM32_PRINT_SIZE_OF_TARGETS(Aurora)

# Additional handy targets
STM32_ADD_HEX_BIN_TARGETS(Aurora)
STM32_ADD_DUMP_TARGET(Aurora)
