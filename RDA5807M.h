#ifndef _RDA5807M_H_INCLUDED
#define _RDA5807M_H_INCLUDED

//#include "TypeDef.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
/*
  PROJETO: Radio FM com RDA5807P
  MCU: PIC18F4550
  Compilador: MikroC PRO PIC
  Autor: Tiago
  Blog: microcontrolandos.blogspot.com.br
  Bibliotecas utilizadas: RDA5807P, SSD1306, Conversions
*/

/* pinos */
//sbit Soft_I2C_Sda at RD0_Bit;
//sbit Soft_I2C_Scl at RD1_Bit;
//sbit Soft_I2C_Sda_Direction at TRISD0_Bit;
//sbit Soft_I2C_Scl_Direction at TRISD1_Bit;



#define RDA5807P_ADDRESS 0x20

typedef struct
{
   union
   {
      char ENABLE : 1; //Power Up Enable. 0 = Disabled; 1 = Enabled.
      char RESET : 1; //Soft reset. 1 = Reset.
      char : 2;
      char CLK_MODE : 3; //000 = 32.768kHz, 001 = 12Mhz, 101 = 24Mhz, 010 = 13Mhz, 110 = 26Mhz, 011 = 19.2Mhz, 111 = 38.4Mhz
      char SKMODE : 1; //Seek Mode.
      char SEEK : 1; //Seek. 0 = Disable stop seek; 1 = Enable.
      char SEEKUP : 1; //Seek Up. 0 = Seek down; 1 = Seek up.
      char : 2;
      char BASS : 1; //Bass Boost. 0 = Disabled; 1 = Bass boost enabled
      char MONO : 1; //Mono Select. 0 = Stereo; 1 = Force mono.
      char DMUTE : 1; //Mute Disable. 0 = Mute; 1 = Normal operation.
      char DHIZ : 1; //Audio Output High-Z Disable. 1 = Normal operation.
      unsigned REG02;
   };//REG02;
   union
   {
      char SPACE : 2; //Channel Spacing. 00 = 100 kHz, 01 = 200 kHz, 10 = 50kHz, 11 = 12.5KHz
      char BAND : 2; //Band Select. 00 = 87–108 MHz (US/Europe), 01 = 76–91 MHz (Japan), 10 = 76–108 MHz (world wide), 11 = 65 –76 MHz ( East Europe) or 50-65MHz
      char TUNE : 1; //Tune. 0 = Disable, 1 = Enable.
      char : 1;
      uint16_t CHANNEL : 10; //Channel Select. Se BAND = 0, Freq = SPACE(kHz) x CHANNEL + 87.0 MHz...
      unsigned REG03;
   };//REG03;
   union
   {
      char : 1;
      char STCIEN : 1; //Seek/Tune Complete Interrupt Enable.
      char : 2;
      char DE : 1; //De-emphasis. 0 = 75 us; 1 = 50 us
      char : 4;
      char I2S_ENABLED : 1; //I2S bus enable. If 1, enabled.
      char GPIO3 : 2;
      char GPIO2 : 2;
      char GPIO1 : 2;
      unsigned REG04;
   };//REG04;
   union
   {
      char VOLUME : 4; //DAC Gain Control Bits. Volume scale is logarithmic.
      char : 4;
      char SEEKTH : 7; //Nivel minino do sinal ( RSSI ) para encontrar uma radio.
      char INT_MODE : 1; //If 0, generate 5ms interrupt.
      unsigned REG05;
   };//REG05;
}RDA5807P;

 typedef struct
{
   unsigned long FREQUENCY;
   union
   {
      char LEVEL : 8; //RSSI ( 7 bits )
      char STC : 1; //STC. 1 = Busca/Sintonizacao terminou.
      char SF : 1;
      char STEREO : 1; //1 = Stereo, 0 = Mono.
      char FM_TRUE : 1; //1 = the current channel is a station.
      char FM_READY : 1; //FM Ready
   };
}RDA5807PInfo;

/* Funçoes */
void RDA5807P_Init( void );
void RDA5807P_Write( void  );
RDA5807PInfo RDA5807P_Read( void );
void RDA5807P_Up( void );
void RDA5807P_Down( void );
void RDA5807P_Search(  char dir );
void RDA5807P_Set_Frequency(  unsigned long freq_khz );

#endif
