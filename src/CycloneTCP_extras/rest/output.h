/*
 * output.h
 *
 *  Created on: 03 нояб. 2015 г.
 *      Author: timurtaipov
 */

#ifndef MY_CYCLONE_REST_OUTPUT_H_
#define MY_CYCLONE_REST_OUTPUT_H_

#define MAX_NUM_OUTPUTS (16)

#define OUTPUT_SERIAL_LENGTH 8

//B12, B13, B14, B15, D8, D9, D10, D11
//D12, D13, D14, D15, D5, D6, D7,  B5 -- LED

//analog or digital OUTPUTs
#define OUTPUT_PIN_0 GPIO_PIN_12
#define OUTPUT_PORT_0 GPIOB

#define OUTPUT_PIN_1 GPIO_PIN_13
#define OUTPUT_PORT_1 GPIOB

#define OUTPUT_PIN_2 GPIO_PIN_14
#define OUTPUT_PORT_2 GPIOB

#define OUTPUT_PIN_3 GPIO_PIN_15
#define OUTPUT_PORT_3 GPIOB

#define OUTPUT_PIN_4 GPIO_PIN_8
#define OUTPUT_PORT_4 GPIOD

#define OUTPUT_PIN_5 GPIO_PIN_9
#define OUTPUT_PORT_5 GPIOD

#define OUTPUT_PIN_6 GPIO_PIN_10
#define OUTPUT_PORT_6 GPIOD

#define OUTPUT_PIN_7 GPIO_PIN_11
#define OUTPUT_PORT_7 GPIOD

#define OUTPUT_PIN_8 GPIO_PIN_12
#define OUTPUT_PORT_8 GPIOD

#define OUTPUT_PIN_9 GPIO_PIN_13
#define OUTPUT_PORT_9 GPIOD

#define OUTPUT_PIN_10 GPIO_PIN_14
#define OUTPUT_PORT_10 GPIOD

#define OUTPUT_PIN_11 GPIO_PIN_15
#define OUTPUT_PORT_11 GPIOD

#define OUTPUT_PIN_12 GPIO_PIN_5
#define OUTPUT_PORT_12 GPIOD

#define OUTPUT_PIN_13 GPIO_PIN_6
#define OUTPUT_PORT_13 GPIOD

#define OUTPUT_PIN_14 GPIO_PIN_7
#define OUTPUT_PORT_14 GPIOD

#define OUTPUT_PIN_15 GPIO_PIN_4
#define OUTPUT_PORT_15 GPIOB

#define TOTAL_OUTPUTS 16



#endif /* MY_CYCLONE_REST_OUTPUT_H_ */
