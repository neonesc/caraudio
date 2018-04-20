/*
 * eeprom.h
 *
 *  Created on: 04.03.2017
 *      Author: Piotr
 */

#ifndef SRC_EEPROM_H_
#define SRC_EEPROM_H_

uint32_t EEWriteTic, EEReadTic;
uint8_t i2cWrite(uint8_t addr_, uint8_t reg, uint8_t data);
uint8_t i2cRead(uint8_t addr_, uint8_t reg);
#define E_Adress 0xA0

#endif /* SRC_EEPROM_H_ */
