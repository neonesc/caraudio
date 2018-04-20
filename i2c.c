/*
 * i2c.c
 *
 *  Created on: 21.01.2018
 *      Author: Piotr
 */

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "gpio.h"

GPIO_InitTypeDef gpioI2C;
I2C_InitTypeDef i2c;

void I2C1Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_1);

	GPIO_StructInit(&gpioI2C);
	gpioI2C.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; // SCL, SDA
	gpioI2C.GPIO_Mode = GPIO_Mode_AF;
	gpioI2C.GPIO_Speed = GPIO_Speed_2MHz;//GPIO_Speed_50MHz;
	gpioI2C.GPIO_OType = GPIO_OType_PP;
	gpioI2C.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &gpioI2C);

	I2C_DeInit(I2C1);
	I2C_Cmd(I2C1, DISABLE);
	i2c.I2C_AnalogFilter = I2C_AnalogFilter_Disable;
	i2c.I2C_DigitalFilter = 0x00;
	i2c.I2C_OwnAddress1 = 0x30;

	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_Ack = I2C_Ack_Enable;

	i2c.I2C_Timing = 0x2000090E;//0xB0420F13;
	i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

	I2C_Init(I2C1, &i2c);
	I2C_Cmd(I2C1, ENABLE);



	I2C_ITConfig(I2C2, I2C_AcknowledgedAddress_7bit, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the I2C2 interrupt priority */
	NVIC_InitStructure.NVIC_IRQChannel = I2C2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void I2C2Init(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);

	GPIO_StructInit(&gpioI2C);
	gpioI2C.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; // SCL, SDA
	gpioI2C.GPIO_Mode = GPIO_Mode_AF;
	gpioI2C.GPIO_Speed = GPIO_Speed_10MHz;//GPIO_Speed_2MHz;//GPIO_Speed_50MHz;
	gpioI2C.GPIO_OType = GPIO_OType_PP;
	gpioI2C.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &gpioI2C);



	I2C_StructInit(&i2c);
	i2c.I2C_Timing = 0x2000090E;//0x2000090E;//0x00212828;//0x0070D8FF;
	//i2c.I2C_Ack = I2C_Ack_Enable;
	//i2c.I2C_Mode = I2C_Mode_I2C;
	//i2c.I2C_AnalogFilter = 1;
	//i2c.I2C_ClockSpeed = 100000;
	I2C_Init(I2C2, &i2c);
	I2C_Cmd(I2C2, ENABLE);

}

void I2C1_ER_IRQHandler(void)
{
  /* Check on I2C1 AF flag and clear it */
  if (I2C_GetITStatus(I2C1, I2C_IT_RXNE))
  {
    //I2C_GenerateSTOP(I2C1,ENABLE);    // release SDA and SCL lines
    I2C_ClearITPendingBit(I2C1, I2C_IT_RXNE);
  }
}

