/*
 * lpc17xxUart.h
 *
 *  Created on: 1-okt.-2012
 *      Author: LPC: ripped wholesale from the lpc17xx code examples package and then significantly adjusted
 */

#ifndef LPC17XXUART_H_
#define LPC17XXUART_H_

//interfacing function

#include "global.h"
#include "simplestack.h"

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define BUFSIZE		0x40

extern volatile LN* topofstack;

//functions

uint32_t init_UART( uint32_t portNum, uint32_t Baudrate );/*turn on port 0 or 1 and set the baudrate*/
extern void UART0_IRQHandler( void );
extern void UART1_IRQHandler( void );
void UART_Send( uint32_t portNum, uint8_t *BufferPtr, uint32_t Length );

//internal functions
void clear_buffer();

#endif /* LPC17XXUART_H_ */
