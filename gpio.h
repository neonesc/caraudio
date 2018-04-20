/*
 * gpio.h
 *
 *  Created on: 04.03.2017
 *      Author: Piotr
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "config.h"
#include "led.h"
#include "sysTime.h"

#define LED			GPIO_Pin_12
#define ANALOG		GPIO_Pin_0
#define IGN			GPIO_Pin_1
#define MODE_KEY	GPIO_Pin_4
#define ENCOD2		GPIO_Pin_3
#define ENCOD1		GPIO_Pin_2
#define RADIO_ON	GPIO_Pin_13
#define POW_STER	GPIO_Pin_14
#define MODE0		GPIO_Pin_0
#define MODE1		GPIO_Pin_1
//#define POW_KEY		GPIO_Pin_1
#define POW_KEY	GPIO_Pin_7
#define BT_RESET	GPIO_Pin_12

uint8_t POWER_ON;
uint8_t Radio_ON;
uint8_t IGNITION;
__IO uint16_t Temperature;

__IO uint16_t RegularConvData_Tab[2];
#define ADC1_DR_Address    0x40012440
void gpioInit(void);
uint16_t getADC(void);
void Check_IGN(void);
//uint32_t TimePOW;

#endif /* SRC_GPIO_H_ */
