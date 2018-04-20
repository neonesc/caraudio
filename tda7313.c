/*
 * tda7313.c
 *
 *  Created on: 20.01.2018
 *      Author: Piotr
 */
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "tda7313.h"
#include "sysTime.h"
#include "EEPROM.h"

uint8_t VOL_VAR[7] = { 20, 0, 0, 31, 31, 0, 2};
const uint8_t VOL_VARS[7] = { 64,16,16,64,64,3,5};
const uint8_t VOL_VARSW[5][2] = { {63, 0}, {0, 0}, {0, 0}, {128, 159},{192, 223}};//, {160, 191}, {224, 255}};
const uint8_t LOUDNESS[5] = { 92, 88, 80, 72, 64 };//{ 68, 88, 80, 72, 64 };
const uint8_t VOLBassTreb[16] = { 96, 97, 98, 99, 100, 101, 102, 103, 111, 110, 109, 108, 107, 106, 105, 104 };//Treble = Bass+16

uint32_t  sEETimeout ;

void TDA7313Init(void){
  //byte VOL_VARE;
	//MUTE=1;
	//TDA7313sendByte(7);
  //if(TDA7313){
    //i2c.beginTransmission(0x44); // 01000100 , 68
    for (uint8_t VOL_VARE = 0; VOL_VARE < 7; VOL_VARE++) {
      TDA7313sendByte(VOL_VARE);
    }
    MUTE=0;
    TDA7313sendByte(7);
    //i2c.write(0x45); // input 2, 11.25db gain, loud mode off
    //i2c.write(0x6F); // bass flat
    //i2c.write(0x7F); // treb flat
    //i2c.write(0x9F); // mute lf
    //i2c.write(0xBF); // mute rf
    //i2c.write(0xC0); // 0db attn RL
    //i2c.write(0xE0); // 0db attn RR
    //i2c.write(0x16); // vol atten to -40db
    //i2c.endTransmission();
 // }

}

void TDA7313sendByte(uint8_t SELE){
  //if(TDA7313){
	uint8_t data[2];// = 0;//, data1 = 0;
    int dtmax;
    if(SELE==0){
      data[0] = VOL_VARSW[SELE][0]-VOL_VAR[SELE];
    }else if(SELE==1){
      data[0] = VOLBassTreb[VOL_VAR[SELE]];
    }else if(SELE==2){
      data[0] = VOLBassTreb[VOL_VAR[SELE]]+16;
    }else if(SELE>2 && SELE<6){
      if(SELE==3 || SELE==4){
        dtmax = VOL_VAR[SELE]-31;
        if(dtmax>=0){
          data[0] = VOL_VARSW[SELE][0];
          data[1] = VOL_VARSW[SELE+1][0]+dtmax;
        }else{
          data[0] = VOL_VARSW[SELE][0]+(dtmax*-1);
          data[1] = VOL_VARSW[SELE+1][0];
        }
      }else{
        data[0] = VOL_VARSW[SELE][0]+VOL_VAR[SELE];
      }
    }else if(SELE==6){
      data[0] = LOUDNESS[VOL_VAR[6]+VOL_VAR[5]];
    }else if(SELE==7){
      data[0] = (MUTE==1) ? 0xff : VOL_VARSW[0][0]-VOL_VAR[0];//VOL_VARSW[SELE][0]-VOL_VAR[SELE];
      //if(MUTE==1){
      //  data = 0xff;
      //}else{
      //  data = VOL_VARSW[SELE][0]-VOL_VAR[SELE];
      //}
    }
    uint8_t nBytes = 1;
    if(SELE==3 || SELE==4){
    	nBytes = 2;
    }


    for(uint8_t kl = 0 ; kl < nBytes ; kl++){
    	sEETimeout = 100;
		I2C_TransferHandling(I2C2, TDA7313_Adress, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);
		while(!(I2C2->ISR & I2C_ISR_TXIS))
		{
			if((sEETimeout--) == 0){  break;};
		}
		if(sEETimeout){
			I2C_SendData(I2C2, data[kl]);
			//while(!(I2C1->ISR & I2C_ISR_TCR));

			//I2C_AutoEndCmd(I2C2, ENABLE);
			//while(!(I2C1->ISR & I2C_ISR_TXIS));

			sEETimeout = 100;

			//I2C_ReloadCmd(I2C2, DISABLE);

			while(!(I2C1->ISR & I2C_ISR_STOPF))
			{
				if((sEETimeout--) == 0){  break;};
			}
		}

		I2C2->ICR = I2C_ICR_STOPCF;
    }

}

