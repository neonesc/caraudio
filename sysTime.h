/*
 * systic.h
 *
 *  Created on: 02.03.2017
 *      Author: Piotr
 */

#ifndef SRC_SYSTIME_H_
#define SRC_SYSTIME_H_
#include "stm32f0xx.h"
//#include "stm32f0xx_conf.h"

#define sysTICSperSEC   1000 //(FREQUENCY/1/12)

uint8_t PTic, T2Tic, WSTic;

// some helpful times for pause()
//#define ONE_US          (uint32_t)((  1e-6 * sysTICSperSEC))
//#define ONE_PR          (uint32_t)((  20e-6 * sysTICSperSEC))
#define ONE_MS          (uint32_t)((  1e-3 * sysTICSperSEC))
#define TWO_MS          (uint32_t)((  2e-3 * sysTICSperSEC))
#define FIVE_MS         (uint32_t)((  5e-3 * sysTICSperSEC))
#define TEN_MS          (uint32_t)(( 10e-3 * sysTICSperSEC))
#define TWENTY_MS       (uint32_t)(( 20e-3 * sysTICSperSEC))
#define THIRTY_MS       (uint32_t)(( 30e-3 * sysTICSperSEC))
#define FIFTY_MS        (uint32_t)(( 50e-3 * sysTICSperSEC))
#define HUNDRED_MS      (uint32_t)((100e-3 * sysTICSperSEC))
#define ONE_FIFTY_MS    (uint32_t)((150e-3 * sysTICSperSEC))
#define QUARTER_SEC     (uint32_t)((250e-3 * sysTICSperSEC))
#define HALF_SEC        (uint32_t)((500e-3 * sysTICSperSEC))
#define ONE_SEC         (uint32_t)(( 1.0   * sysTICSperSEC))
#define TWO_SEC         (uint32_t)(( 2.0   * sysTICSperSEC))
#define FIVE_SEC        (uint32_t)(( 5.0   * sysTICSperSEC))
#define TEN_SEC         (uint32_t)((10.0   * sysTICSperSEC))

uint8_t TX_time ,RX_time;

uint16_t PrescalerValue;
void TIM_Config(void);
void SysticInit(void);
void STicTimer(void);
//void WSTicTimer(void);
void TimingDelay_Decrement(void);
uint32_t getSysTICs(void);
uint32_t getElapsedSysTICs(uint32_t startTime);

#endif /* SRC_SYSTIME_H_ */
