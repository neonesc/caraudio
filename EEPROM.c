/*
 * eeprom.c
 *
 *  Created on: 04.03.2017
 *      Author: Piotr
 */

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "config.h"
#include "gpio.h"
#include "sysTime.h"
#include "EEPROM.h"

uint32_t  sEETimeout ;

uint8_t i2cRead(uint8_t addr, uint8_t reg)
{

	while(getElapsedSysTICs(EEWriteTic) < TEN_MS ){

	}

	uint8_t tmp1 = 0xFF;

	I2C_TransferHandling(I2C1, E_Adress, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	while(!(I2C1->ISR & I2C_ISR_TXIS));

	I2C_SendData(I2C1, reg);
	while(!(I2C1->ISR & I2C_ISR_TC));

	I2C_TransferHandling(I2C1, E_Adress, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
	while(!(I2C1->ISR & I2C_ISR_RXNE));

	tmp1 = I2C_ReceiveData(I2C1);

	while(!(I2C1->ISR & I2C_ISR_STOPF));
	I2C1->ICR = I2C_ICR_STOPCF;

	EEReadTic = getSysTICs();
	return(tmp1);
}

uint8_t i2cWrite(uint8_t addr_, uint8_t reg, uint8_t data)
{

	while(getElapsedSysTICs(EEReadTic) <= TEN_MS /*+ FIVE_MS*/ ){

	}

	//uint8_t wra = 1;

	I2C_TransferHandling(I2C1, E_Adress, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
	while(!(I2C1->ISR & I2C_ISR_TXIS));

	I2C_SendData(I2C1, reg);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_AutoEndCmd(I2C1, ENABLE);
	while(!(I2C1->ISR & I2C_ISR_TXIS));

	I2C_SendData(I2C1, data);

	I2C_ReloadCmd(I2C1, DISABLE);

	//sEETimeout = 100;
	while(!(I2C1->ISR & I2C_ISR_STOPF));
	//{
	//	if((sEETimeout--) == 0){  break;};
	//}
	I2C1->ICR = I2C_ICR_STOPCF;
	EEWriteTic = getSysTICs();
	EEReadTic = getSysTICs();

	return 1;
}
