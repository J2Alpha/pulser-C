/*
 * init.h
 *
 *  Created on: 2-okt.-2012
 *      Author: J2Alpha
 */

//startup only
//doesn't need the action handlers (except uart to clear the buffer), ignores all inputs.
//the system shouldn't be in this mode again after it passed once

#ifndef INIT_H_
#define INIT_H_

#include "global.h"

uint32_t in_INIT_on_UART(void);
uint32_t in_INIT_on_IONIZE(void);
uint32_t in_INIT_on_STOP(void);
uint32_t in_INIT_on_CHARGE(void);

#endif /* INIT_H_ */
