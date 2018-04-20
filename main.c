#include "main.h"

int main(void)
{

	//Remap_Table();
	//__enable_irq();
	//IWDG_ReloadCounter();
	//SystemInit();
	//SystemCoreClockUpdate();
	SysticInit();
	gpioInit();
	EncoderInit();
	IWDGConfig();
	TIM_Config();
	uint32_t TimeTic = getSysTICs();
	I2C2Init();
	UartInit();
	//EEpromInit();
	//STicTimer();

	//LoadConfig();//zaladowanie ustawien zapisanych w EEprom


	//TIM_Cmd (TIM3, ENABLE);//timer ON
	//TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//TIM_Cmd (TIM14, ENABLE);//timer ON
	//TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
	//TIM_Cmd (TIM14, DISABLE);

	LedMig(50);
	TDA7313Init();
	POWER_ON = 1;
	GPIO_SetBits(GPIOB, BT_RESET);

	while (1)
	{

		if(POWER_ON){
			if(getElapsedSysTICs(TimeTic) >= ONE_SEC ){
				TimeTic = getSysTICs();

				/*
				uint16_t t1 = getADC();
				uint16_t t2 = getADC();
				Send_Byte (t1>>8);
				Send_Byte (t1&0xff);
				Send_Byte (t2>>8);
				Send_Byte (t2&0xff);
				*/
				//Send_Byte (Temperature>>8);
				//Send_Byte (Temperature&0xff);
				LedMig(50);
				Check_IGN();
			}
			EncoderLoop();
		}
		LedLoop();
		IWDG_ReloadCounter();
	}

}

void IWDGConfig(void){
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2500);
	IWDG_ReloadCounter();
	IWDG_Enable();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
