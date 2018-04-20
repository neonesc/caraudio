
#include "RDA5807M.h"
//#include "RDA5807M-private.h"
//extern RDA5807P radio;
//extern RDA5807PInfo info;

/* constantes */
const int UP = 5;
const int DOWN = 6;
const int SEARCH = 7;

/* variáveis */
char flags = 0; //armazena os estados dos botoes
//static RDA5807P radio; //configuraçoes do módulo
//static RDA5807PInfo info; //informaçao da rádio selecionada
char msg[12]; //usado para armazenar a conversao de um número em string

RDA5807P radio; //configuraçoes do módulo
RDA5807PInfo info; //informaçao da rádio selecionada

void RDA5807P_Init(  )
{
   radio.REG02 = 0xD081;//radio.REG02.BASS = 1; radio.REG02.ENABLE = 1; radio.REG02.DMUTE = 0; radio.REG02.SKMODE = 1;// = 0xD081; //boss = true, enable = true, mute = false, seekmode = 1
   radio.REG03 = 0x0010;//radio.REG03.SPACE = 0x00; radio.REG03.TUNE = 1;//0x0010; //space = 100KHz, tune = true
   radio.REG04 = 0x0000;
   radio.REG05 = 0x88AF; //volume maximo
   RDA5807P_Write(  );
}

void RDA5807P_Write( )
{
//char i;

////unsigned * wData = (unsigned*)&radio;
//unsigned * wDatas = (unsigned*)&radio;
//char ints[5];
/*
   I2C1_Start();
   I2C1_Is_Idle();
   I2C1_Wr( RDA5807P_ADDRESS );
   I2C1_Is_Idle();
   for( i = 0; i < 4; i++ )
   {
      I2C1_Wr( ((char*)wData)[1] ); //High
      I2C1_Is_Idle();
      I2C1_Wr( ((char*)wData)[0] ); //Low
      I2C1_Is_Idle();
      wData++;
   }
   I2C1_Stop();
   */

  // IntToStr(Hi(radio.REG02), ints);
   //LCD_Print(ints , 0, 6, 0, 0, 0);
  // IntToStr(Lo(radio.REG02), ints);
  // LCD_Print(ints , 0, 5, 0, 0, 0);
   /*
   IntToStr(Hi(radio.REG02), ints);
   LCD_Print(&ints[2] , 0, 0, 0, 0, 0);
   IntToStr(Lo(radio.REG02), ints);
   LCD_Print(&ints[2] , 0, 1, 0, 0, 0);
   IntToStr(Hi(radio.REG03), ints);
   LCD_Print(&ints[2] , 0, 2, 0, 0, 0);
   IntToStr(Lo(radio.REG03), ints);
   LCD_Print(&ints[2] , 0, 3, 0, 0, 0);
   IntToStr(Hi(radio.REG04), ints);
   LCD_Print(&ints[2] , 50, 0, 0, 0, 0);
   IntToStr(Lo(radio.REG04), ints);
   LCD_Print(&ints[2] , 50, 1, 0, 0, 0);
   IntToStr(Hi(radio.REG05), ints);
   LCD_Print(&ints[2] , 50, 2, 0, 0, 0);
   IntToStr(Lo(radio.REG05), ints);
   LCD_Print(&ints[2] , 50, 3, 0, 0, 0);
   */
/*
   I2C1_Start();
   I2C1_Is_Idle();
   I2C1_Wr( RDA5807P_ADDRESS );
   I2C1_Is_Idle();
   I2C1_Wr( Hi(radio.REG02));
   I2C1_Is_Idle();
   I2C1_Wr( Lo(radio.REG02));
   I2C1_Is_Idle();
   I2C1_Wr( Hi(radio.REG03));
   I2C1_Is_Idle();
   I2C1_Wr( Lo(radio.REG03));
   I2C1_Is_Idle();
   I2C1_Wr( Hi(radio.REG04));
   I2C1_Is_Idle();
   I2C1_Wr( Lo(radio.REG04));
   I2C1_Is_Idle();
   I2C1_Wr( Hi(radio.REG05));
   I2C1_Is_Idle();
   I2C1_Wr( Lo(radio.REG05));
   I2C1_Is_Idle();
   
   I2C1_Stop();
*/
	I2C_TransferHandling(I2C1, RDA5807P_ADDRESS, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
	while(!(I2C1->ISR & I2C_ISR_TXIS));

	I2C_SendData(I2C1, radio.REG02&0xFF00);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_SendData(I2C1, radio.REG02&0xFF);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_SendData(I2C1, radio.REG03&0xFF00);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_SendData(I2C1, radio.REG03&0xFF);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_SendData(I2C1, radio.REG04&0xFF00);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_SendData(I2C1, radio.REG04&0xFF);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_SendData(I2C1, radio.REG05&0xFF00);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_AutoEndCmd(I2C1, ENABLE);
	while(!(I2C1->ISR & I2C_ISR_TXIS));

	I2C_SendData(I2C1, radio.REG05&0xFF);
	while(!(I2C1->ISR & I2C_ISR_TCR));

	I2C_ReloadCmd(I2C1, DISABLE);

	while(!(I2C1->ISR & I2C_ISR_STOPF));

}

void RDA5807P_Search(  char dir )
{
   radio.SEEKUP = dir&1<<0;//dir.B0;
   radio.TUNE = 0;
   radio.SEEK = 1;
   RDA5807P_Write( );
   radio.SEEK = 0;
   //Delay_ms( 20 );
}

RDA5807PInfo RDA5807P_Read( )
{
char rData[4];
char cs = 100;
RDA5807PInfo info;
/*
   I2C2_Start();
   I2C2_Wr( RDA5807P_ADDRESS | 1 );
   rData[1] = I2C2_Rd(1); //High
   rData[0] = I2C2_Rd(1); //Low
   rData[3] = I2C2_Rd(1); //High
   rData[2] = I2C2_Rd(0); //Low
   I2C2_Stop();
*/
	//I2C_TransferHandling(I2C1, RDA5807P_ADDRESS | 1, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	//while(!(I2C1->ISR & I2C_ISR_TXIS));
	//I2C_SendData(I2C1, reg);
	//while(!(I2C1->ISR & I2C_ISR_TC));
	I2C_TransferHandling(I2C1, RDA5807P_ADDRESS | 1, 4, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
	while(!(I2C1->ISR & I2C_ISR_RXNE));

	rData[1] = I2C_ReceiveData(I2C1);
	rData[0] = I2C_ReceiveData(I2C1);
	rData[3] = I2C_ReceiveData(I2C1);
	rData[2] = I2C_ReceiveData(I2C1);

	while(!(I2C1->ISR & I2C_ISR_STOPF));
	I2C1->ICR = I2C_ICR_STOPCF;

   info.STC = rData[1] & 1<<6;//rData[1].B6;
   info.SF = rData[1] & 1<<5;//rData[1].B5;
   info.STEREO = rData[1] & 1<<2;//rData[1].B2;
   info.FM_TRUE = rData[3] & 1<<0;//rData[3].B0;
   info.FM_READY = rData[2] & 1<<7;//rData[2].B7;
   info.LEVEL = rData[3] >> 1;

   rData[1] &= 0x3; //limpa os 6 bits mais significativos...ja foram lidos acima.
   radio.CHANNEL = ((unsigned*)&rData)[0];
   //R3 = radio.SPACE;
   switch( radio.SPACE )
   {
      case 1 : cs = 200; break;
      case 2 : cs = 50; break;
      case 3 : cs = 12; break;
   }
    info.FREQUENCY = cs * (unsigned long)((unsigned*)&rData)[0] + ( !radio.BAND ? 87000UL : 76000UL );
    return info;
}

void RDA5807P_Up(  )
{
   radio.CHANNEL++;
   radio.TUNE = 1;
   RDA5807P_Write(  );
   radio.TUNE = 0;
   //Delay_ms( 20 );
}

void RDA5807P_Down(  )
{
   radio.CHANNEL--;
   radio.TUNE = 1;
   RDA5807P_Write(  );
   radio.TUNE = 0;
  // Delay_ms( 20 );
}

void RDA5807P_Set_Frequency(  unsigned long freq_khz )
{
	char cs = 100;
	//R3 = radio.SPACE;
	switch( radio.SPACE )
	{
	  case 1 : cs = 200; break;
	  case 2 : cs = 50; break;
	  case 3 : cs = 25; break;
	}

	radio.CHANNEL = ( freq_khz - ( !radio.BAND ? 87000UL : 76000UL ) ) / cs;
	radio.TUNE = 1;
	RDA5807P_Write(  );
	radio.TUNE = 0;
	//Delay_ms( 20 );
}
