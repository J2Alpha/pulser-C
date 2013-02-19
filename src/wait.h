/*
 * wait.h
 *
 *  Created on: 2-okt.-2012
 *      Author: J2Alpha
 */

#ifndef WAIT_H_
#define WAIT_H_

#include "global.h"
#include "lpc17xxUart.h"
#include "lpc17xxIO.h"

uint32_t in_WAIT_on_UART(void);
uint32_t in_WAIT_on_IONIZE(void);
uint32_t in_WAIT_on_STOP(void);
uint32_t in_WAIT_on_CHARGE(void);

#endif /* WAIT_H_ */
