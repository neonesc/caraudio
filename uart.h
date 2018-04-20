/*
 * uart.h
 *
 *  Created on: 04.03.2017
 *      Author: Piotr
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_

#define BUFFER_SIZE	200
//volatile uint8_t Tx_Buf[BUFFER_SIZE];
volatile uint8_t Rx_Buf[BUFFER_SIZE];

//#define RS485_TX	 GPIOA->BSRR = GPIO_Pin_12
//#define RS485_RX	 GPIOA->BRR = GPIO_Pin_12

//volatile uint8_t Tx_R,Tx_P;
volatile uint8_t Rx_R,Rx_P;
uint32_t RXreset;
uint32_t ResetTic;
//uint8_t UartOn;

void UartInit(void);
//void UartSend(void);
void UartSendOdp(uint8_t length);
void Send_Byte (uint8_t c);
//void UartTXClear(void);

#endif /* SRC_UART_H_ */
