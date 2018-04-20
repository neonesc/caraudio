/*
 * led.c
 *
 *  Created on: 21.03.2017
 *      Author: Piotr
 */

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "sysTime.h"
#include "config.h"
#include "gpio.h"
#include "led.h"

uint8_t ON_OFF;
uint32_t LedTic;

void LedLoop(void){
	if(ON_OFF == true){
		if(getSysTICs() >= LedTic){
			ON_OFF = false;
			GPIO_ResetBits(GPIOA, LED);
		}
	}
}

//Zapalenie diody na okreslony czas - time w milisekundach
void LedMig(uint16_t time){
	LedTic = getSysTICs() + (time * ONE_MS);
	ON_OFF = true;
	GPIO_SetBits(GPIOA, LED);
}
