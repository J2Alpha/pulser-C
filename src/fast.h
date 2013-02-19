/*
 * fast.h
 *
 *  Created on: 2-okt.-2012
 *      Author: J2Alpha
 */

#ifndef FAST_H_
#define FAST_H_

#include "global.h"
//#include "lpc17xxUart.h"

uint32_t in_FAST_on_UART(void);
uint32_t in_FAST_on_IONIZE(void);
uint32_t in_FAST_on_STOP(void);
uint32_t in_FAST_on_CHARGE(void);

#endif /* FAST_H_ */
