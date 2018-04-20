/*
 * config.c
 *
 *  Created on: 06.03.2017
 *      Author: Piotr
 */
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "stm32f0xx_conf.h"
#include "sysTime.h"
#include "config.h"

#include "EEPROM.h"
#include "led.h"


//#define true 	1
//#define false 	0

uint8_t bootRun;		//czy pierwszy start
uint16_t StartRun;		//ilosc uruchomien czujnika
uint32_t CLoadTic, CWriteTic;

static const DVersion defaultVersion = {
		.firmwareVersion_major = 0,
		.firmwareVersion_minor = 1,
		.serial = 0,
		.year = 0,
		.month = 0,
		.day = 0
};

DVersion Version;


//ColorDisplay CDisplay;

//Ladowanie defaultowych ustawien
void LoadDefaultConfig()
{
	//writeFlash(defaultConfig);
	//readFlash();
}


uint8_t LoadConfig()
{
	//Pierwszy start programu
	EEWriteTic = getSysTICs();
	bootRun = i2cRead(E_Adress, 0);
	uint8_t sizeConfig = i2cRead(E_Adress, 200);
	//Send_Byte (bootRun);
	StartRun = (i2cRead(E_Adress, 2) << 8) | i2cRead(E_Adress, 1);
	StartRun ++;
	Version = defaultVersion;//kopiowanie defaulowych ustawien do wersji
	if((bootRun == 2 || bootRun == 3) && sizeConfig == sizeof(DVersion)){
		readEEprom();//odczyt configuracji z pamieci EEPROM
		if(bootRun == 2){
			LedMig(50);
		}else{
			i2cWrite(E_Adress, 0, 2);
			LedMig(800);
		}
		bootRun = 2;
		//BVersion = defaultBVersion;//kopiowanie defaulowych ustawien do wersji bootloadera
		//Version = defaultVersion;//kopiowanie defaulowych ustawien do wersji
		//Config = defaultConfig;//kopiowanie defaulowych ustawien do Config
		//Config.blue = 0xff;
		//readEEprom();//odczyt configuracji z pamieci EEPROM
		//Config = defaultConfig;
	}else{
		//Send_Byte (0xff);
		//CLoadTic = getSysTICs();
		//CWriteTic = getSysTICs();
		//ConfigLoad = 1;
		//ConfigWrite = 1;
		LedMig(500);
		//Send_Byte (0xff);
		//Send_Byte (i2cWrite(E_Adress, 0, 2));
		bootRun = 2;
		//Send_Byte (0xff);
		//LedMig(500);
		//}else{
		//	LedMig(50);
		//}
		//Send_Byte (0xff);
		writeEEprom();//zapisanie konfiguracji do pamięci EEPROM
		//Send_Byte (0xff);
		//bootRun = 1;
		//Version = defaultVersion;//kopiowanie defaulowych ustawien do wersji
		//Config = defaultConfig;//kopiowanie defaulowych ustawien do Config
	}
	//Send_Byte (0xfe);
	//przygotowanie tablic
	//BVersion = defaultBVersion;//kopiowanie defaulowych ustawien do wersji bootloadera
	//Version = defaultVersion;//kopiowanie defaulowych ustawien do wersji
	//Config = defaultConfig;//kopiowanie defaulowych ustawien do Config
	//zapisanie tablic
	//LedMig(50);
	//readEEprom();//odczyt configuracji z pamieci EEPROM
	//ilosc startow +1
	//StartRun = (i2cRead(E_Adress, 2) << 8) | i2cRead(E_Adress, 1);
	//StartRun ++;
	i2cWrite(E_Adress, 0, 2);
	//uint8_t STR[2] = { StartRun, StartRun>>8};
	//i2cWriteBuffer(E_Adress, 1, 2, &STR[0]);
	i2cWrite(E_Adress, 1, StartRun);
	i2cWrite(E_Adress, 2, StartRun>>8);
	//Send_Byte (STR[0]);
	//Send_Byte (STR[1]);
	return 1;
}

void ConfLoad(void){
	//if(ConfigLoad && getElapsedSysTICs(CLoadTic) >= ONE_SEC ){
		ConfigLoad = 0;
		LedMig(50);
		readEEprom();//odczyt configuracji z pamieci EEPROM
	//}
}

void ConfWrite(void){
	//if(ConfigWrite && getElapsedSysTICs(CWriteTic) >= ONE_SEC/2 ){
		ConfigWrite = 0;
		LedMig(100);
		//Send_Byte (0xff);
		i2cWrite(E_Adress, 0, 2);
		//Send_Byte (1);
		bootRun = 2;
		//Send_Byte (0xff);
		writeEEprom();//zapisanie konfiguracji do pamięci EEPROM
		//Send_Byte (0xff);
		//uint8_t STR[2] = { StartRun, StartRun>>8};
			//i2cWriteBuffer(E_Adress, 1, 2, &STR[0]);
			i2cWrite(E_Adress, 1, StartRun);
			i2cWrite(E_Adress, 2, StartRun>>8);
			//Send_Byte (STR[0]);
			//Send_Byte (STR[1]);
			//Send_Byte (0xff);
	//}
}

//zapis defaultowych ustawien
void writeEEprom(void)
{
	uint8_t sizeST = sizeof(DVersion);
	uint8_t* addressOfStruct = (uint8_t*)(&defaultVersion);
	//Send_Byte (sizeST);
	//i2cWriteBuffer(E_Adress, 60, sizeST, addressOfStruct);
	for(uint8_t i=0 ; i<sizeST ; i++){
		//Send_Byte (addressOfStruct[i]);
		i2cWrite(E_Adress, 60+i, addressOfStruct[i]);
	}


	//i2cWrite(E_Adress, 200, sizeST);
}

//odczyt z pamieci EEPROM
//0-boot
//1-program version
//2-config
void readEEprom(void)
{
	uint8_t sizeSTB = sizeof(Version);
	uint8_t receiveBufferB[sizeSTB];
	//Send_Byte (sizeSTB);
	for(uint8_t i=0 ; i<sizeSTB ; i++){
		receiveBufferB[i] = i2cRead(E_Adress, 10+i);
		//Send_Byte (receiveBufferB[i]);
	}
	*(uint8_t*)&Version = *(uint8_t *)(receiveBufferB); //przeniesienie tablicy z bufora do BVersion

}

void SaveConfigEEPROM(void)
{
	//uint8_t sizeSTC = sizeof(DConfig);
	//uint8_t* addressOfStructC = (uint8_t*)(&Config);
	//for(uint8_t i=0 ; i<sizeSTC ; i++){
	//	i2cWrite(E_Adress, 100+i, addressOfStructC[i]);
		//Send_Byte (addressOfStructC[i]);
	//}
	//crc_Config();
	//crcConfig = MakeCrc(&addressOfStructC[0], sizeSTC);
}

void  SetBit( uint32_t *A,  uint16_t k )
{
	A[k/32] |= 1 << (k%32);
}

void  ClearBit( uint32_t *A,  uint16_t k )
{
	A[k/32] &= ~(1 << (k%32));
}

uint8_t ReadBit( const uint32_t *A,  uint16_t k )
{
	return ( (A[k/32] & (1 << (k%32) )) != 0 ) ;
}
