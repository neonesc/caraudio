/*
 * Encoder.h
 *
 *  Created on: 21.01.2018
 *      Author: Piotr
 */

#ifndef SRC_ENCODER_H_
#define SRC_ENCODER_H_

uint8_t Rotate, Start;
int Rotate_Add;
int MODE;
uint32_t TimeStart;
uint32_t TimePOW, TimeMODE_KEY;

void EncoderInit(void);
void EncoderLoop(void);

#endif /* SRC_ENCODER_H_ */
