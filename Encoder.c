/*
 * Encoder.c
 *
 *  Created on: 21.01.2018
 *      Author: Piotr
 */

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "gpio.h"
#include "config.h"
#include "Encoder.h"
#include "sysTime.h"
#include "tda7313.h"
#include "led.h"

EXTI_InitTypeDef   EXTI_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;
uint16_t Timer3;
uint32_t TimeMode;

void EncoderInit(void){
	/* Configure EXTI2 & EXTI3 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI0_1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_DisableIRQ(EXTI2_3_IRQn);

	/* Configure EXTI4 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line4 | EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI4_15 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_DisableIRQ(EXTI4_15_IRQn);

	NVIC_EnableIRQ(EXTI2_3_IRQn);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	TimeMode = getSysTICs();

}

void EXTI2_3_IRQHandler(void){
	Timer3 = TIM_GetCounter(TIM3);
	if(EXTI_GetFlagStatus(ENCOD1)){
		if(!Timer3){
			TIM_Cmd (TIM3, ENABLE);
		}else{
			TIM_Cmd(TIM3 , DISABLE);
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			TIM_SetCounter(TIM3,  0);//timer reset counter
			LedMig(5);
			TimeMode = getSysTICs();
			Rotate = 0;//left
			Rotate_Add -=1;
		}
	    EXTI_ClearFlag(ENCOD1);
	}
	if(EXTI_GetFlagStatus(ENCOD2)){
		if(!Timer3){
			TIM_Cmd (TIM3, ENABLE);
		}else{
			TIM_Cmd(TIM3 , DISABLE);
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			TIM_SetCounter(TIM3,  0);//timer reset counter
			LedMig(5);
			TimeMode = getSysTICs();
			Rotate = 1;//right
			Rotate_Add +=1;

		}
		EXTI_ClearFlag(ENCOD2);
	}
}

void EXTI4_15_IRQHandler(void){
	if(EXTI_GetFlagStatus(MODE_KEY)){
		if(!GPIO_ReadInputDataBit(GPIOA, MODE_KEY) && POWER_ON && getElapsedSysTICs(TimeMODE_KEY) >= QUARTER_SEC)
		{
			TimeMODE_KEY = getSysTICs();
			LedMig(5);
			MODE++;
			if(MODE>7){
				MODE = 0;
			}
			TimeMode = getSysTICs();
		}
	    EXTI_ClearFlag(MODE_KEY);
	}
	if(EXTI_GetFlagStatus(POW_KEY)){
		if(!GPIO_ReadInputDataBit(GPIOA, POW_KEY) && getElapsedSysTICs(TimePOW) >= ONE_SEC)
		{
			//LedMig(5);
			TimePOW = getSysTICs();
			if(!POWER_ON){
				GPIO_SetBits(GPIOB, POW_STER);
				if(Radio_ON){
					GPIO_SetBits(GPIOB, RADIO_ON);
				}
				POWER_ON = 1;
				NVIC_EnableIRQ(EXTI2_3_IRQn);
				//NVIC_EnableIRQ(EXTI4_15_IRQn);
				LedMig(500);
				//TimeStart = getSysTICs();
				//Start = 0;
				TDA7313Init();
			}else{
				POWER_ON = 0;
				//NVIC_DisableIRQ(EXTI4_15_IRQn);
				NVIC_DisableIRQ(EXTI2_3_IRQn);
				LedMig(5);
				MUTE=1;
				TDA7313sendByte(7);
				//GPIO_ResetBits(GPIOB, POW_STER);
				GPIO_ResetBits(GPIOB, RADIO_ON);
			}
		}

		EXTI_ClearFlag(POW_KEY);
	}
}

void EncoderLoop(void){
	if(POWER_ON){
		if(MODE && Rotate_Add == 0 && getElapsedSysTICs(TimeMode) >= ONE_SEC*3 ){
			MODE = 0;
		}
		if(Rotate_Add!=0){
			VOL_VAR[MODE] += Rotate_Add;
			if(VOL_VAR[MODE] < 1){
				VOL_VAR[MODE] = 1;
			}
			if(VOL_VAR[MODE] > VOL_VARS[MODE]){
				VOL_VAR[MODE] = VOL_VARS[MODE];
			}
			Rotate_Add = 0;
			TDA7313sendByte(MODE);
		}
	}
}
