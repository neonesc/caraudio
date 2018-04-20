/**
  ******************************************************************************
  * @file    SysTick/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "gpio.h"
#include "Encoder.h"
#include "tda7313.h"
#include "sysTime.h"
#include "eeprom.h"
#include "config.h"
#include "led.h"
#include "i2c.h"
#include "EEPROM.h"
#include "uart.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
//void TimingDelay_Decrement(void);
//void Delay(__IO uint32_t);
void IWDGConfig(void);
//void Remap_Table(void);
//void Delay(__IO uint32_t);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
