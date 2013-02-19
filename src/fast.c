/*
 * fast.c
 *
 *  Created on: 8-okt.-2012
 *      Author: admin
 */

#include "fast.h"
#include "peripherialpins.h"
#include "statelist.h"
#include "LPC17xxPWM.h"
#include "LPC17xxIO.h"

uint32_t in_FAST_on_UART(void)
{
	//TODO: reset buffer
	return 1;
}
uint32_t in_FAST_on_IONIZE(void)
{
	PWM_Stop(1);
	Set_Pin_LO(IOPORT,IONIZELED);
	return WAIT;
}
uint32_t in_FAST_on_STOP(void)
{
	PWM_Stop(1);
	Set_Pin_LO(IOPORT,IONIZELED);
	return WAIT;
}
uint32_t in_FAST_on_CHARGE(void)
{
	Set_Pin_HI(IOPORT, CHARGEPIN | CHARGELED);
	return MIXS;
}
