# Not pushing this file down to libraries in order to keep source tree as is (not populating with extra files, such as CMakeList.txt)
#
# Below each section represents a library with its own settings




###################
# FreeRTOS
###################

SET(FREERTOS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS)
SET(FREERTOS_PORT_DIR portable/GCC/ARM_CM3)

SET(FREERTOS_SRC
	${FREERTOS_SRC_DIR}/croutine.c
	${FREERTOS_SRC_DIR}/event_groups.c
	${FREERTOS_SRC_DIR}/list.c
	${FREERTOS_SRC_DIR}/queue.c
	${FREERTOS_SRC_DIR}/tasks.c
	${FREERTOS_SRC_DIR}/timers.c
	
	${FREERTOS_SRC_DIR}/portable/MemMang/heap_4.c
	
	${FREERTOS_SRC_DIR}/${FREERTOS_PORT_DIR}/port.c
	${FREERTOS_SRC_DIR}/${FREERTOS_PORT_DIR}/portmacro.h
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
	${STM32CUBE_F2_SRC_DIR}/CMSIS/Device/ST/STM32F2xx/Source/Templates/gcc/startup_stm32f205xx.s
	${STM32CUBE_F2_SRC_DIR}/CMSIS/Device/ST/STM32F2xx/Source/Templates/system_stm32f2xx.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc_ex.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_can.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_crc.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cryp.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dac.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dac_ex.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dcmi.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_hash.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_hcd.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_i2c.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_i2s.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_irda.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_mmc.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_msp_template.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_nand.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_nor.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pccard.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pcd.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pcd_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rng.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rtc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rtc_ex.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_sd.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_smartcard.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_spi.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_sram.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_timebase_rtc_alarm_template.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_timebase_rtc_wakeup_template.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_timebase_tim_template.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_usart.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_wwdg.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_adc.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_crc.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_dac.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_dma.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_exti.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_fsmc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_gpio.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_i2c.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_pwr.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_rcc.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_rng.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_rtc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_sdmmc.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_spi.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_tim.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_usart.c
	${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_usb.c
	# ${STM32CUBE_F2_SRC_DIR}/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_utils.c


)

ADD_LIBRARY(STM32Cube_f2 STATIC ${STM32CUBE_F2_SRC})

target_link_libraries (STM32Cube_f2 LINK_PUBLIC newlib)

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
target_link_libraries (Common LINK_PUBLIC STM32Cube_f2)

TARGET_INCLUDE_DIRECTORIES(Common PUBLIC
	${COMMON_SRC_DIR}
)

###################
# CycloneTCP
###################

SET(CYCLONETCP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CycloneTCP)

SET(CYCLONETCP_SRC
#Core
	${CYCLONETCP_SRC_DIR}/core/bsd_socket.c
	${CYCLONETCP_SRC_DIR}/core/ethernet.c
	${CYCLONETCP_SRC_DIR}/core/ip.c
	${CYCLONETCP_SRC_DIR}/core/net.c
	${CYCLONETCP_SRC_DIR}/core/net_mem.c
	${CYCLONETCP_SRC_DIR}/core/nic.c
	${CYCLONETCP_SRC_DIR}/core/ping.c
	${CYCLONETCP_SRC_DIR}/core/raw_socket.c
	${CYCLONETCP_SRC_DIR}/core/socket.c
	${CYCLONETCP_SRC_DIR}/core/tcp.c
	${CYCLONETCP_SRC_DIR}/core/tcp_fsm.c
	${CYCLONETCP_SRC_DIR}/core/tcp_misc.c
	${CYCLONETCP_SRC_DIR}/core/tcp_timer.c
	${CYCLONETCP_SRC_DIR}/core/udp.c
#DHCP
	${CYCLONETCP_SRC_DIR}/dhcp/dhcp_client.c
	${CYCLONETCP_SRC_DIR}/dhcp/dhcp_common.c
	${CYCLONETCP_SRC_DIR}/dhcp/dhcp_debug.c
	${CYCLONETCP_SRC_DIR}/dhcp/dhcp_server.c
#dhcpv6
	${CYCLONETCP_SRC_DIR}/dhcpv6/dhcpv6_client.c
	${CYCLONETCP_SRC_DIR}/dhcpv6/dhcpv6_common.c
	${CYCLONETCP_SRC_DIR}/dhcpv6/dhcpv6_debug.c
	${CYCLONETCP_SRC_DIR}/dhcpv6/dhcpv6_relay.c
#dns
	${CYCLONETCP_SRC_DIR}/dns/dns_cache.c
	${CYCLONETCP_SRC_DIR}/dns/dns_client.c
	${CYCLONETCP_SRC_DIR}/dns/dns_common.c
	${CYCLONETCP_SRC_DIR}/dns/dns_debug.c
#dns_sd
	${CYCLONETCP_SRC_DIR}/dns_sd/dns_sd.c
#drivers
	# ${CYCLONETCP_SRC_DIR}/drivers/a2fxxxm3_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/am335x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/aps3_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ar8031.c
	# ${CYCLONETCP_SRC_DIR}/drivers/avr32_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/bcm43362_driver.c
	# ${CYCLONETCP_SRC_DIR}/drivers/dm9000.c
	# ${CYCLONETCP_SRC_DIR}/drivers/dm9161.c
	# ${CYCLONETCP_SRC_DIR}/drivers/dp83620.c
	# ${CYCLONETCP_SRC_DIR}/drivers/dp83822.c
	# ${CYCLONETCP_SRC_DIR}/drivers/dp83848.c
	${CYCLONETCP_SRC_DIR}/drivers/enc28j60.c
	${CYCLONETCP_SRC_DIR}/drivers/ext_int_driver.c
	${CYCLONETCP_SRC_DIR}/drivers/spi_driver.c
	# ${CYCLONETCP_SRC_DIR}/drivers/enc624j600.c
	# ${CYCLONETCP_SRC_DIR}/drivers/f28m35x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/fm4_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8031.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8041.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8051.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8061.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8081.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8091.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8721.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8851.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8873.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz8895.c
	# ${CYCLONETCP_SRC_DIR}/drivers/ksz9031.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lan8700.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lan8710.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lan8720.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lan8740.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lan8742.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lan9303.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lm3s_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lpc175x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lpc176x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lpc178x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lpc18xx_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lpc23xx_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/lpc43xx_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/m2sxxx_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/mcf5225x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/mk6x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/mk7x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/mkv5x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/mrf24wg_driver.c
	# ${CYCLONETCP_SRC_DIR}/drivers/omapl138_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/pcap_driver.c
	# ${CYCLONETCP_SRC_DIR}/drivers/pic32mx_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/pic32mz_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/rtl8211.c
	# ${CYCLONETCP_SRC_DIR}/drivers/rx63n_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/rza1_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/s7g2_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/sam3x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/sam4e_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/sam7x_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/sam9263_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/sama5d2_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/sama5d3_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/sama5d3_gigabit_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/same70_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/samv71_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/st802rt1a.c
	# ${CYCLONETCP_SRC_DIR}/drivers/stm32f107_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/stm32f2x7_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/stm32f4x7_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/stm32f4x9_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/stm32f7xx_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/stm32h7xx_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/str912_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/tm4c129_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/upd60611.c
	# ${CYCLONETCP_SRC_DIR}/drivers/wilc1000_driver.c
	# ${CYCLONETCP_SRC_DIR}/drivers/winc1500_driver.c
	# ${CYCLONETCP_SRC_DIR}/drivers/xmc4500_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/xmc4700_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/xmc4800_eth.c
	# ${CYCLONETCP_SRC_DIR}/drivers/zynq7000_eth.c
#ftp client
	# ${CYCLONETCP_SRC_DIR}/ftp/ftp_client.c
#ftp server
	${CYCLONETCP_SRC_DIR}/ftp/ftp_server.c
	${CYCLONETCP_SRC_DIR}/ftp/ftp_server_commands.c
	${CYCLONETCP_SRC_DIR}/ftp/ftp_server_events.c
	${CYCLONETCP_SRC_DIR}/ftp/ftp_server_misc.c
#http server
	${CYCLONETCP_SRC_DIR}/http/http_server.c
	${CYCLONETCP_SRC_DIR}/http/http_server_auth.c
	${CYCLONETCP_SRC_DIR}/http/http_server_misc.c
	${CYCLONETCP_SRC_DIR}/http/mime.c
	${CYCLONETCP_SRC_DIR}/http/ssi.c
#icecast
	# ${CYCLONETCP_SRC_DIR}/icecast/icecast_client.c
#ipv4
	${CYCLONETCP_SRC_DIR}/ipv4/arp.c
	${CYCLONETCP_SRC_DIR}/ipv4/auto_ip.c
	${CYCLONETCP_SRC_DIR}/ipv4/icmp.c
	${CYCLONETCP_SRC_DIR}/ipv4/igmp.c
	${CYCLONETCP_SRC_DIR}/ipv4/ipv4.c
	${CYCLONETCP_SRC_DIR}/ipv4/ipv4_frag.c
#ipv6
	# ${CYCLONETCP_SRC_DIR}/ipv6/icmpv6.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ipv6.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ipv6_frag.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ipv6_misc.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ipv6_pmtu.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ipv6_routing.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/mld.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ndp.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ndp_cache.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ndp_misc.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/ndp_router_adv.c
	# ${CYCLONETCP_SRC_DIR}/ipv6/slaac.c
#mdns
	${CYCLONETCP_SRC_DIR}/mdns/mdns_client.c
	${CYCLONETCP_SRC_DIR}/mdns/mdns_common.c
	${CYCLONETCP_SRC_DIR}/mdns/mdns_responder.c
#mibs
	# ${CYCLONETCP_SRC_DIR}/mibs/if_mib_impl.c
	# ${CYCLONETCP_SRC_DIR}/mibs/if_mib_module.c
	# ${CYCLONETCP_SRC_DIR}/mibs/ip_mib_impl.c
	# ${CYCLONETCP_SRC_DIR}/mibs/ip_mib_module.c
	# ${CYCLONETCP_SRC_DIR}/mibs/mib2_impl.c
	# ${CYCLONETCP_SRC_DIR}/mibs/mib2_module.c
	# ${CYCLONETCP_SRC_DIR}/mibs/mib_common.c
	# ${CYCLONETCP_SRC_DIR}/mibs/snmp_mib_impl.c
	# ${CYCLONETCP_SRC_DIR}/mibs/snmp_mib_module.c
	# ${CYCLONETCP_SRC_DIR}/mibs/snmp_usm_mib_impl.c
	# ${CYCLONETCP_SRC_DIR}/mibs/snmp_usm_mib_module.c
	# ${CYCLONETCP_SRC_DIR}/mibs/tcp_mib_impl.c
	# ${CYCLONETCP_SRC_DIR}/mibs/tcp_mib_module.c
	# ${CYCLONETCP_SRC_DIR}/mibs/udp_mib_impl.c
	# ${CYCLONETCP_SRC_DIR}/mibs/udp_mib_module.c
#mqtt
	# ${CYCLONETCP_SRC_DIR}/mqtt/mqtt_client.c
	# ${CYCLONETCP_SRC_DIR}/mqtt/mqtt_client_misc.c
	# ${CYCLONETCP_SRC_DIR}/mqtt/mqtt_client_packet.c
	# ${CYCLONETCP_SRC_DIR}/mqtt/mqtt_client_transport.c
#netbios
	 ${CYCLONETCP_SRC_DIR}/netbios/nbns_client.c
	 ${CYCLONETCP_SRC_DIR}/netbios/nbns_common.c
	 ${CYCLONETCP_SRC_DIR}/netbios/nbns_responder.c
#ppp
	# ${CYCLONETCP_SRC_DIR}/ppp/chap.c
	# ${CYCLONETCP_SRC_DIR}/ppp/ipcp.c
	# ${CYCLONETCP_SRC_DIR}/ppp/ipv6cp.c
	# ${CYCLONETCP_SRC_DIR}/ppp/lcp.c
	# ${CYCLONETCP_SRC_DIR}/ppp/pap.c
	# ${CYCLONETCP_SRC_DIR}/ppp/ppp.c
	# ${CYCLONETCP_SRC_DIR}/ppp/ppp_debug.c
	# ${CYCLONETCP_SRC_DIR}/ppp/ppp_fsm.c
	# ${CYCLONETCP_SRC_DIR}/ppp/ppp_hdlc.c
	# ${CYCLONETCP_SRC_DIR}/ppp/ppp_misc.c
#smtp client
	# ${CYCLONETCP_SRC_DIR}/smtp/smtp_client.c
#snmp agent
	# ${CYCLONETCP_SRC_DIR}/snmp/snmp_agent.c
	# ${CYCLONETCP_SRC_DIR}/snmp/snmp_agent_dispatch.c
	# ${CYCLONETCP_SRC_DIR}/snmp/snmp_agent_misc.c
	# ${CYCLONETCP_SRC_DIR}/snmp/snmp_agent_pdu.c
	# ${CYCLONETCP_SRC_DIR}/snmp/snmp_common.c
	# ${CYCLONETCP_SRC_DIR}/snmp/snmp_usm.c
#sntp client
	${CYCLONETCP_SRC_DIR}/sntp/sntp_client.c
#std_services
	# ${CYCLONETCP_SRC_DIR}/std_services/chargen.c
	# ${CYCLONETCP_SRC_DIR}/std_services/daytime.c
	# ${CYCLONETCP_SRC_DIR}/std_services/discard.c
	# ${CYCLONETCP_SRC_DIR}/std_services/echo.c
#tftp client and server
	# ${CYCLONETCP_SRC_DIR}/tftp/tftp_client.c
	# ${CYCLONETCP_SRC_DIR}/tftp/tftp_client_misc.c
	# ${CYCLONETCP_SRC_DIR}/tftp/tftp_server.c
	# ${CYCLONETCP_SRC_DIR}/tftp/tftp_server_misc.c
#websocket
	# ${CYCLONETCP_SRC_DIR}/web_socket/web_socket.c
	# ${CYCLONETCP_SRC_DIR}/web_socket/web_socket_auth.c
	# ${CYCLONETCP_SRC_DIR}/web_socket/web_socket_frame.c
	# ${CYCLONETCP_SRC_DIR}/web_socket/web_socket_misc.c
	# ${CYCLONETCP_SRC_DIR}/web_socket/web_socket_transport.c
)

ADD_LIBRARY(CycloneTCP STATIC ${CYCLONETCP_SRC})

target_link_libraries (CycloneTCP LINK_PUBLIC Common)
target_link_libraries (CycloneTCP LINK_PUBLIC STM32Cube_f2)

TARGET_INCLUDE_DIRECTORIES(CycloneTCP PUBLIC
	${CYCLONETCP_SRC_DIR}
)

###################
# fatfs is ap part of STM32Cube_f2
###################

SET(FATFS_SRC_DIR ${STM32CUBE_F2_SRC_DIR}/FatFs/src)

SET(FATFS_SRC
${FATFS_SRC_DIR}/diskio.c
${FATFS_SRC_DIR}/drivers/sd_diskio.c
# ${FATFS_SRC_DIR}/drivers/sdram_diskio.c
# ${FATFS_SRC_DIR}/drivers/sram_diskio.c
# ${FATFS_SRC_DIR}/drivers/usbh_diskio.c
${FATFS_SRC_DIR}/ff.c
${FATFS_SRC_DIR}/ff_gen_drv.c
# ${FATFS_SRC_DIR}/option/cc932.c
# ${FATFS_SRC_DIR}/option/cc936.c
# ${FATFS_SRC_DIR}/option/cc949.c
# ${FATFS_SRC_DIR}/option/cc950.c
${FATFS_SRC_DIR}/option/ccsbcs.c
${FATFS_SRC_DIR}/option/syscall.c
${FATFS_SRC_DIR}/option/unicode.c
)

ADD_LIBRARY(Fatfs STATIC ${FATFS_SRC})

target_link_libraries (Fatfs LINK_PUBLIC STM32Cube_f2)
target_link_libraries (Fatfs LINK_PUBLIC Common)

TARGET_INCLUDE_DIRECTORIES(Fatfs PUBLIC
	${FATFS_SRC_DIR}
	${FATFS_SRC_DIR}/drivers
)

###################
# jsmn_extras
###################

SET(JSMNEXTRAS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/jsmn-extras)

SET(JSMNEXTRAS_SRC
	${JSMNEXTRAS_SRC_DIR}/jsmn.c
	${JSMNEXTRAS_SRC_DIR}/jsmn_extras.c
)

ADD_LIBRARY(Jsmn_extras STATIC ${JSMNEXTRAS_SRC})

TARGET_COMPILE_DEFINITIONS(Jsmn_extras PUBLIC
	-DJSMN_PARENT_LINKS
)

TARGET_INCLUDE_DIRECTORIES(Jsmn_extras PUBLIC
	${JSMNEXTRAS_SRC_DIR}
)

###################
# xprintf
###################

SET(XPINTF_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xprintf)

SET(XPINTF_SRC
	${XPINTF_SRC_DIR}/xprintf.c
)

ADD_LIBRARY(xprintf STATIC ${XPINTF_SRC})

TARGET_INCLUDE_DIRECTORIES(xprintf PUBLIC
	${XPINTF_SRC_DIR}
)

###################
# list
###################

SET(LIST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/list)

SET(LIST_SRC
	${LIST_SRC_DIR}/list_iterator.c
	${LIST_SRC_DIR}/list_node.c
	${LIST_SRC_DIR}/list.c
)

ADD_LIBRARY(list STATIC ${LIST_SRC})

target_link_libraries (list LINK_PUBLIC Common)

TARGET_INCLUDE_DIRECTORIES(list PUBLIC
	${LIST_SRC_DIR}
)

###################
# newlib
###################

SET(NEWLIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/newlib)

SET(NEWLIB_SRC
	${NEWLIB_SRC_DIR}/_exit.c
	${NEWLIB_SRC_DIR}/_sbrk.c
	${NEWLIB_SRC_DIR}/_startup.c
	${NEWLIB_SRC_DIR}/_syscalls.c
	${NEWLIB_SRC_DIR}/assert.c
)

ADD_LIBRARY(newlib STATIC ${NEWLIB_SRC})

# TARGET_INCLUDE_DIRECTORIES(newli PUBLIC
# 	${LIST_SRC_DIR}
# )