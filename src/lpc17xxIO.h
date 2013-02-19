/*
 * lpc17xxIO.h
 *
 *  Created on: 2-okt.-2012
 *      Author: J2Alpha
 */
#pragma once
#ifndef LPC17xxIO_H_
#define LPC17xxIO_H_

#include "global.h"
#include "stack.h"

extern volatile STACK* pileP;
extern volatile int32_t currentaction;
/*Initializer
 * port 	 :is portnumber (0-4),
 * mask 	 :enables writing and reading of all registers for witch pinMASK = 0 and blocks when pinMASK = 1 (0x0000=read and write all)
 * direction :sets direction of pins, subject to mask
 */
void Initialise_Port(uint32_t Port, uint32_t mask, uint32_t direction);
/*sets output state of output pins _HI or_LO
 * port: is port number (0-4),
 * data: is output on/off (0=off, 1=on)
 * if masked correctly in the initializer this is always safe
 */
void Set_Pin_HI(uint32_t Port, uint32_t data);
void Set_Pin_LO(uint32_t Port, uint32_t data);
/*
 * get returns IO state of port
 * port: is port number (0-4),
 * data: is pointer to receiver of state (0=low, 1=high)
 * mask: 0->get state of all pins irregardless of input or output, anything but 0 ->mask output pins with 0's
 */
void Get_Input_From_Port(uint32_t Port, uint32_t *data,uint32_t mask);
/*set up pin interrupts
 * port: is port number (0-4),
 * edge: 0 for rising edge, 1 for falling edge, 2 for any change.
 * data: relevant pins
 */
void Set_pin_interupts(uint32_t Port,uint32_t edge, uint32_t data);
/*handle an IO pin interrupt
 * the interrupts are passed to extint3 when they happen and then handled here
 */
extern void EINT3_IRQHandler(void);
/*Pass an interrupt onto the stack
 * the IO interrupts are passed here by EINT3_IRQHandler and pushed onto the stack
 */
void IO_Interupt_Push(uint32_t Port, uint32_t edge, uint32_t pins);
#endif
