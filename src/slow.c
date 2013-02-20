/*
 * slow.c
 *
 *  Created on: 8-okt.-2012
 *      Author: admin
 */

#include "slow.h"
#include "peripherialpins.h"
#include "statelist.h"
#include "LPC17xxIO.h"
#include "LPC17xxUART.h"
#include "LPC17xxPWM.h"

uint32_t in_SLOW_on_UART(void)
{
	//TODO: reset buffer
	return SLOW;
}
uint32_t in_SLOW_on_IONIZE(void)
{
	PWM_Start(1);
	Set_Pin_HI(IOPORT, IONIZEPIN | IONIZELED);
	return MIXS;
}
uint32_t in_SLOW_on_STOP(void)
{
	Set_Pin_LO(IOPORT,(CHARGEPIN)|(CHARGELED));
	return WAIT;
}
uint32_t in_SLOW_on_CHARGE(void)
{
	Set_Pin_LO(IOPORT,(CHARGEPIN)|(CHARGELED));
	return WAIT;
}
