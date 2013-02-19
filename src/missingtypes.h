/*
 * missingtypes.h
 *  ripped wholesale from NXP
 *  Created on: 18-okt.-2012
 *      Author: J2Alpha
 */

#ifndef MISSINGTYPES_H_
#define MISSINGTYPES_H_

#include <stdint.h>

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif


typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#endif /* MISSINGTYPES_H_ */
