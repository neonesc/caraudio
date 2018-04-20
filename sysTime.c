/*
 * systic.c
 *
 *  Created on: 02.03.2017
 *      Author: Piotr
 */
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
//#include "stm32f0xx_conf.h"
#include "sysTime.h"
#include "config.h"
#include "gpio.h"
#include "led.h"

static volatile uint32_t sysTICs;
static volatile uint32_t lastSysTIC;
static volatile uint32_t Milliseconds = 0;


void SysticInit(void)
{
	if ( SysTick_Config( SystemCoreClock / 1000 ))
	{
		while (1); //W przypadku b³êdu program zawiesi siê w pêtli nieskoñczonej
	}
}

void TIM_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 500;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 400;//600;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &timerInitStructure);

    NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	nvicStructure.NVIC_IRQChannelPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
	TIM_Cmd (TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3 , DISABLE);
}
/*
void STicTimer(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 48000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 99;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);

	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	nvicStructure.NVIC_IRQChannelPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
}

void WSTicTimer(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 250;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 5;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM14, &timerInitStructure);

	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM14_IRQn;
	nvicStructure.NVIC_IRQChannelPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);
}
*/
void TIM3_IRQHandler()
{

	if ( TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET )
    {
		TIM_Cmd(TIM3 , DISABLE);
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		TIM_SetCounter(TIM3,  0);//timer reset counter
		//LedMig(5);

    }
}
/*
void TIM14_IRQHandler()
{

	if ( TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET )
    {
		TIM_ClearITPendingBit(TIM14, TIM_IT_Update);


    }
}
*/
void TimingDelay_Decrement(void)
{

	Milliseconds++;
}

uint32_t getElapsedSysTICs(uint32_t startTime)
{
	return getSysTICs() - startTime;
}

uint32_t getSysTICs(void)
{
  	uint32_t now = Milliseconds;

  	sysTICs += (uint32_t) (Milliseconds - lastSysTIC);
  	lastSysTIC = now;
  	return sysTICs;
}
