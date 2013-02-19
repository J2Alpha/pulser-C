/*
 * states.h
 *
 *  Created on: 2-okt.-2012
 *      Author: J2Alpha
 */
#pragma once
#ifndef STATES_H_
#define STATES_H_

//states included
#include "statelist.h"
#include "init.h"
#include "wait.h"
#include "slow.h"
#include "fast.h"
#include "mixs.h"

//state table
	/*    b UART command |    charge cap   | pdm transformer |  STOP button*/
uint32_t (*const state_map [STATELIMIT][ACTIONLIMIT]) (void)=
{
    { in_INIT_on_UART,in_INIT_on_CHARGE,in_INIT_on_IONIZE,in_INIT_on_STOP }, /*INIT*/
    { in_WAIT_on_UART,in_WAIT_on_CHARGE,in_WAIT_on_IONIZE,in_WAIT_on_STOP }, /*WAIT*/
    { in_SLOW_on_UART,in_SLOW_on_CHARGE,in_SLOW_on_IONIZE,in_SLOW_on_STOP }, /*SLOW*/
    { in_FAST_on_UART,in_FAST_on_CHARGE,in_FAST_on_IONIZE,in_FAST_on_STOP }, /*FAST*/
    { in_MIXS_on_UART,in_MIXS_on_CHARGE,in_MIXS_on_IONIZE,in_MIXS_on_STOP }  /*MIXS*/
};
//

#endif /* STATES_H_ */
