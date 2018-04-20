/*
 * gpio.c
 *
 *  Created on: 04.03.2017
 *      Author: Piotr
 */
#include "gpio.h"
GPIO_InitTypeDef        GPIO_InitStructureA;
GPIO_InitTypeDef        GPIO_InitStructureB;
GPIO_InitTypeDef        GPIO_InitStructureD;
GPIO_InitTypeDef        GPIO_InitStructureADC;
//__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
ADC_InitTypeDef     ADC_InitStructure;
//DMA_InitTypeDef   DMA_InitStructure;

GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef   EXTI_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;
//I2C_InitTypeDef I2C_InitStructure;
//GPIO_InitTypeDef gpioI2C;
//I2C_InitTypeDef i2c;

/* CPAL local transfer structures */
//CPAL_TransferTypeDef  sRxStructure, sTxStructure;

void gpioInit(void)
{
	  GPIO_DeInit(GPIOA);
	  GPIO_DeInit(GPIOB);
	  /* GPIOC Periph clock enable */
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	  GPIO_InitStructureA.GPIO_Pin = IGN | MODE_KEY | ENCOD2 | ENCOD1 | POW_KEY;
	  GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructureA.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructureA.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOA, &GPIO_InitStructureA);

	  GPIO_InitStructureA.GPIO_Pin = LED;
	  GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructureA.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructureA.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOA, &GPIO_InitStructureA);

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	  GPIO_InitStructureB.GPIO_Pin = RADIO_ON | POW_STER;
	  GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructureB.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructureB.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOB, &GPIO_InitStructureB);

	  GPIO_InitStructureB.GPIO_Pin = BT_RESET;
	  GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructureB.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructureB.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOB, &GPIO_InitStructureB);

	  //GPIO_SetBits(GPIOB, RADIO_ON);
	  GPIO_SetBits(GPIOB, POW_STER);

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	  GPIO_InitStructureB.GPIO_Pin = MODE0 | MODE1;
	  GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructureB.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructureB.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOD, & GPIO_InitStructureD);

	  //i2c_1 - Slave
	  /*
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_1);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_1);
	  GPIO_StructInit(&gpioI2C);
	  gpioI2C.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // SCL, SDA
	  gpioI2C.GPIO_Mode = GPIO_Mode_AF;
	  gpioI2C.GPIO_Speed = GPIO_Speed_2MHz;//GPIO_Speed_50MHz;
	  gpioI2C.GPIO_OType = GPIO_OType_PP;
	  gpioI2C.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOB, &gpioI2C);
	  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
	  I2C_InitStructure.I2C_DigitalFilter = 0x00;
	  I2C_InitStructure.I2C_OwnAddress1 = 0x40;
	  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	  I2C_InitStructure.I2C_Timing =0xB0420F13; //100KHz
	  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

	  I2C_Init(I2C2, &I2C_InitStructure);
	  I2C_Cmd(I2C2, ENABLE);


	  //i2c_2 - Master
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);
	  GPIO_StructInit(&gpioI2C);
	  gpioI2C.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // SCL, SDA
	  gpioI2C.GPIO_Mode = GPIO_Mode_AF;
	  gpioI2C.GPIO_Speed = GPIO_Speed_2MHz;//GPIO_Speed_50MHz;
	  gpioI2C.GPIO_OType = GPIO_OType_PP;
	  gpioI2C.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(GPIOB, &gpioI2C);
	  I2C_StructInit(&i2c);
	  i2c.I2C_Timing = 0x2000090E;
	  I2C_Init(I2C2, &i2c);
	  I2C_Cmd(I2C2, ENABLE);
	  */

	  //adc
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  GPIO_InitStructureADC.GPIO_Pin = ANALOG;
	  GPIO_InitStructureADC.GPIO_Mode = GPIO_Mode_AN;
	  GPIO_InitStructureADC.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	  GPIO_Init(GPIOA, &GPIO_InitStructureADC);
	  ADC_DeInit(ADC1);
	  ADC_StructInit(&ADC_InitStructure);
	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	  ADC_Init(ADC1, &ADC_InitStructure);

	  ADC_ChannelConfig(ADC1, ADC_Channel_0 , ADC_SampleTime_239_5Cycles);

	  ADC_GetCalibrationFactor(ADC1);
	  ADC_Cmd(ADC1, ENABLE);
	  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));

	  ADC_StartOfConversion(ADC1);

	  NVIC_EnableIRQ(EXTI0_1_IRQn);

}

void Check_IGN(void){
	if(GPIO_ReadInputDataBit(GPIOA, IGN)){
		IGNITION = 1;
	}else{
		IGNITION = 0;
	}
}

uint16_t getADC(){

	uint32_t tmp = 0;


	//for (uint8_t i = 0; i < 4; i++)
	//{
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

		tmp += ADC_GetConversionValue(ADC1);
	//}
	//tmp /= 4;
	//tmp *= 516129;
	//tmp /= 10000;
	//tmp *= 13055;
	//tmp /= 10;
	return tmp; //tmp * ((3.3*16)/1023) * 1000mV
	//return ADC_GetConversionValue(ADC1);


	  return tmp;
}

