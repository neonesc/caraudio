/*
 * tda7313.h
 *
 *  Created on: 20.01.2018
 *      Author: Piotr
 */

#ifndef SRC_TDA7313_H_
#define SRC_TDA7313_H_

#define TDA7313_Adress 0x88

extern uint8_t VOL_VAR[7];
extern const uint8_t VOL_VARS[7];
extern const uint8_t VOL_VARSW[5][2];
extern const uint8_t LOUDNESS[5];
extern const uint8_t VOLBassTreb[16];
uint8_t MUTE;
uint8_t VOLBUTTONS_TYPE;

void TDA7313Init(void);
void TDA7313sendByte(uint8_t SELE);

#endif /* SRC_TDA7313_H_ */
