 /*
 * statelist.h
 *
 *  Created on: 17-okt.-2012
 *      Author: J2Alpha
 */

#ifndef STATELIST_H_
#define STATELIST_H_

#include "global.h"

enum states{INIT,WAIT,SLOW,FAST,MIXS,STATELIMIT};// state_now;
enum actions{UART,CHARGE,IONIZE,STOP,ACTIONLIMIT};// action_now;

#endif /* STATELIST_H_ */
