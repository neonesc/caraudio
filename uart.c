/*
 * uart.c
 *
 *  Created on: 04.03.2017
 *      Author: Piotr
 */
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "uart.h"
//#include "incomming_packet.h"
#include "sysTime.h"
#include "led.h"

uint32_t TXTic;
USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef USART_ClockInitstructure;
uint32_t errTic;

void UartInit(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	GPIO_InitTypeDef  GPIO_InitStructureA;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_0);

	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructureA.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructureA.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);

	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructureA.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructureA.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);
	//Configure USART1 setting: ----------------------------
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 9600;
	//USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
	//USART_InitStructure.USART_Parity = USART_Parity_Odd ;
	USART_Init(USART1, &USART_InitStructure);

	//USART_DECmd(USART1, ENABLE);
	//USART_DEPolarityConfig(USART1, USART_DEPolarity_High );//USART_DEPolarity_Low
	//USART_SetDEDeassertionTime(USART1, 0x10);

	USART_Cmd(USART1,ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

}

void USART1_IRQHandler(void)
{
	//UartOn = 1;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
   {
		//if(getElapsedSysTICs(RXreset) >= TWENTY_MS){
			//resetCMD();
		//}
		//UartOn = 1;
		//volatile char str = USART_ReceiveData(USART1);
		Rx_Buf[Rx_R++] = USART_ReceiveData(USART1);
		if( Rx_R >= BUFFER_SIZE ){
			Rx_R = 0;
		}
		//ResetTic = getSysTICs();
		//UartOn = 0;
		//LedMig(50);
   }
   if(USART_GetFlagStatus(USART1, USART_IT_PE)) {//Parity error
		//LedMig(500);
	//	USART_ClearFlag(USART1, USART_IT_PE);
		USART_Cmd(USART1,DISABLE);
		USART_Cmd(USART1,ENABLE);
	}
}

/*
**===========================================================================
**
**  Abstract: Send_Byte
**
**===========================================================================
*/
void Send_Byte (uint8_t c)
{

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

}

void UartSendOdp(uint8_t length)
{
	Send_Byte (0x55);
	for(uint8_t i = 0; i< length; i++){
		//Send_Byte (command[i]);
	}
	Send_Byte (0x56);
}

