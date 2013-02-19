/*
 * wait.c
 *
 *  Created on: 8-okt.-2012
 *      Author: admin
 */

#include "wait.h"
#include "peripherialpins.h"
#include "statelist.h"
#include "LPC17xxPWM.h"
uint32_t in_WAIT_on_UART(void)
{
	//TODO: handle
	return WAIT;
}
uint32_t in_WAIT_on_IONIZE(void)
{
	PWM_Start(1);
	Set_Pin_HI(IOPORT,IONIZELED);
	return FAST;
}
uint32_t in_WAIT_on_STOP(void)
{
	//do nothing
	return WAIT;
}
uint32_t in_WAIT_on_CHARGE(void)
{
	Set_Pin_HI(IOPORT,CHARGEPIN | CHARGELED);
	return SLOW;
}
