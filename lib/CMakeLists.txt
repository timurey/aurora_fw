# Not pushing this file down to libraries in order to keep source tree as is (not populating with extra files, such as CMakeList.txt)
#
# Below each section represents a library with its own settings



###################
# NeoGPS
###################

#SET(NEOGPS_SRC
#	NeoGPS/DMS.cpp
#	NeoGPS/GPSTime.cpp
#	NeoGPS/Location.cpp
#	NeoGPS/NeoTime.cpp
#	NeoGPS/NMEAGPS.cpp
#)
#ADD_LIBRARY(NeoGPS STATIC ${NEOGPS_SRC})



###################
# FreeRTOS
###################

SET(FREERTOS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS)
SET(FREERTOS_PORT_DIR portable/GCC/ARM_CM3)

SET(FREERTOS_SRC
	${FREERTOS_SRC_DIR}/croutine.c
	${FREERTOS_SRC_DIR}/event_groups.c

	${FREERTOS_SRC_DIR}/include/FreeRTOS.h
	${FREERTOS_SRC_DIR}/include/StackMacros.h
	${FREERTOS_SRC_DIR}/include/croutine.h
	${FREERTOS_SRC_DIR}/include/deprecated_definitions.h
	${FREERTOS_SRC_DIR}/include/event_groups.h
	${FREERTOS_SRC_DIR}/include/list.h
	${FREERTOS_SRC_DIR}/include/mpu_prototypes.h
	${FREERTOS_SRC_DIR}/include/mpu_wrappers.h
	${FREERTOS_SRC_DIR}/include/portable.h
	${FREERTOS_SRC_DIR}/include/projdefs.h
	${FREERTOS_SRC_DIR}/include/queue.h
	${FREERTOS_SRC_DIR}/include/semphr.h
	${FREERTOS_SRC_DIR}/include/stdint.readme
	${FREERTOS_SRC_DIR}/include/task.h
	${FREERTOS_SRC_DIR}/include/timers.h
	${FREERTOS_SRC_DIR}/list.c

	${FREERTOS_SRC_DIR}/${FREERTOS_PORT_DIR}/port.c
	${FREERTOS_SRC_DIR}/${FREERTOS_PORT_DIR}/portmacro.h

	${FREERTOS_SRC_DIR}/queue.c

	${FREERTOS_SRC_DIR}/tasks.c
	${FREERTOS_SRC_DIR}/timers.c
)
ADD_LIBRARY(FreeRTOS STATIC ${FREERTOS_SRC})

target_include_directories(FreeRTOS PUBLIC 
	${FREERTOS_SRC_DIR}/include
	${FREERTOS_SRC_DIR}/${FREERTOS_PORT_DIR}
)



###################
# USBlib
###################

SET(USBLIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/USBlib)

SET(USBLIB_SRC
	${USBLIB_SRC_DIR}/class/cdc/inc/usbd_cdc.h
	${USBLIB_SRC_DIR}/class/cdc/src/usbd_cdc.c

	${USBLIB_SRC_DIR}/core/inc/usbd_core.h
	${USBLIB_SRC_DIR}/core/inc/usbd_ctlreq.h
	${USBLIB_SRC_DIR}/core/inc/usbd_def.h
	${USBLIB_SRC_DIR}/core/inc/usbd_ioreq.h

	${USBLIB_SRC_DIR}/core/src/usbd_core.c
	${USBLIB_SRC_DIR}/core/src/usbd_ctlreq.c
	${USBLIB_SRC_DIR}/core/src/usbd_ioreq.c
)

ADD_LIBRARY(USBLib STATIC ${USBLIB_SRC})

TARGET_INCLUDE_DIRECTORIES(USBLib PUBLIC
	${USBLIB_SRC_DIR}/core/inc/
	${USBLIB_SRC_DIR}/class/cdc/inc/
)


target_link_libraries (USBLib LINK_PUBLIC STM32Cube_f2)


###################
# STM32Cube_f2
###################

SET(STM32CUBE_F2_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stm32cube_f2)

SET(STM32CUBE_F2_SRC
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_can.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_crc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cryp.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dac.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dac_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dcmi.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_hash.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_hcd.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_i2c.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_i2s.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_irda.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_mmc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_msp_template.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_nand.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_nor.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pccard.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pcd.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pcd_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rng.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rtc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rtc_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_sd.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_smartcard.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_spi.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_sram.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_timebase_rtc_alarm_template.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_timebase_rtc_wakeup_template.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_timebase_tim_template.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_usart.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_wwdg.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_adc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_crc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_dac.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_dma.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_exti.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_fsmc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_gpio.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_i2c.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_pwr.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_rcc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_rng.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_rtc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_sdmmc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_spi.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_tim.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_usart.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_usb.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_utils.c

)

ADD_LIBRARY(STM32Cube_f2 STATIC ${STM32CUBE_F2_SRC})

TARGET_INCLUDE_DIRECTORIES(STM32Cube_f2 PUBLIC
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Inc
	${STM32CUBE_F2_SRC_DIR}/CMSIS/Device/ST/STM32F2xx/Include/
	${STM32CUBE_F2_SRC_DIR}/CMSIS/Include/
)



###################
# Common
###################

SET(COMMON_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Common)

SET(COMMON_SRC
	${COMMON_SRC_DIR}/cpu_endian.c
	${COMMON_SRC_DIR}/fs_port_fatfs.c
	# ${COMMON_SRC_DIR}/os_port_cmsis_rtos2.c
	# ${COMMON_SRC_DIR}/os_port_none.c
	# ${COMMON_SRC_DIR}/os_port_sys_bios.c
	# ${COMMON_SRC_DIR}/os_port_windows.c
	${COMMON_SRC_DIR}/str.c
	${COMMON_SRC_DIR}/date_time.c
	# ${COMMON_SRC_DIR}/os_port_chibios.c
	# ${COMMON_SRC_DIR}/os_port_embos.c
	# ${COMMON_SRC_DIR}/os_port_posix.c
	# ${COMMON_SRC_DIR}/os_port_ucos2.c
	${COMMON_SRC_DIR}/path.c
	${COMMON_SRC_DIR}/debug.c
	# ${COMMON_SRC_DIR}/os_port_cmsis_rtos.c
	${COMMON_SRC_DIR}/os_port_freertos.c
	# ${COMMON_SRC_DIR}/os_port_rtx.c
	# ${COMMON_SRC_DIR}/os_port_ucos3.c
	${COMMON_SRC_DIR}/resource_manager.c
)

ADD_LIBRARY(Common STATIC ${COMMON_SRC})

target_link_libraries (Common LINK_PUBLIC FreeRTOS)
target_link_libraries (Common LINK_PUBLIC Fatfs)

TARGET_INCLUDE_DIRECTORIES(Common PUBLIC
	${COMMON_SRC_DIR}
)


###################
# Fatfs
###################

SET(FATFS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/fatfs)

SET(FATFS_SRC
	${FATFS_SRC_DIR}/ff.c
	${FATFS_SRC_DIR}/ffsystem.c
	${FATFS_SRC_DIR}/ffunicode.c
)

ADD_LIBRARY(Fatfs STATIC ${FATFS_SRC})

TARGET_INCLUDE_DIRECTORIES(Fatfs PUBLIC
	${FATFS_SRC_DIR}
)


#TARGET_COMPILE_DEFINITIONS(STM32duino PRIVATE 
#	-DVECT_TAB_ADDR=${VECT_TAB_ADDR} 
#	-DGENERIC_BOOTLOADER 
#	-DBOARD_maple
#)