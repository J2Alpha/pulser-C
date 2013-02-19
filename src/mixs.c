/*
 * mixs.c
 *
 *  Created on: 8-okt.-2012
 *      Author: admin
 */

#include "mixs.h"
#include "peripherialpins.h"
#include "statelist.h"
#include "LPC17xxIO.h"
#include "LPC17xxPWM.h"

uint32_t in_MIXS_on_UART(void)
{
	//TODO: handle
	return MIXS;
}
uint32_t in_MIXS_on_IONIZE(void)
{
	Set_Pin_LO(IOPORT,IONIZELED);
	PWM_Stop(1);
	return SLOW;
}
uint32_t in_MIXS_on_STOP(void)
{
	Set_Pin_LO(IOPORT,CHARGEPIN | CHARGELED);
	PWM_Stop(1);
	Set_Pin_LO(IOPORT,IONIZELED);
	return WAIT;
}
uint32_t in_MIXS_on_CHARGE(void)
{
	Set_Pin_LO(IOPORT,CHARGEPIN | CHARGELED);
	return FAST;
}
