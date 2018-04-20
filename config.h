/*
 * config.h
 *
 *  Created on: 06.03.2017
 *      Author: Piotr
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#ifndef FALSE
#define FALSE 0
#ifndef TRUE
#define TRUE  !FALSE
#endif
#endif

#ifndef false
#define false 0
#ifndef true
#define true  !false
#endif
#endif

#define WRITE_START_ADDR   ((uint32_t)0x08005000)//The starting address is written
#define FIRMWARE_START_ADDR   (uint32_t)(WRITE_START_ADDR)


//uint8_t PTic;
uint32_t StartTic;
uint8_t SaveEE;

uint16_t ConfigLoad, ConfigWrite;//crc konfiguracji


	typedef struct
	{
		uint8_t firmwareVersion_major;//wersja bootloadera
		uint8_t firmwareVersion_minor;//wersja bootloadera
		uint32_t serial;//numer seryjny czujnika
		uint8_t year;//rok wgrania bootloadera
		uint8_t month;//miesiac wgrania bootloadera
		uint8_t day;//dzien wgrania bootloadera

	} DVersion;



	extern DVersion Version;


	void SaveConfig(void);
	uint8_t LoadConfig(void);
	void ConfLoad(void);
	void ConfWrite(void);
	void LoadDefaultConfig(void);
	void ConfigLoop(void);
	void writeEEprom(void);
	void readEEprom(void);
	void SaveConfigEEPROM(void);

	void  SetBit( uint32_t *A,  uint16_t k );
	void  ClearBit( uint32_t *A,  uint16_t k );
	uint8_t ReadBit( const uint32_t *A,  uint16_t k );

#endif /* SRC_CONFIG_H_ */
