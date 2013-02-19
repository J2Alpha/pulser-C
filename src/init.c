/*
 * init.cpp
 *
 *  Created on: 2-okt.-2012
 *      Author: J2Alpha
 */

#include "init.h"
#include "statelist.h"

uint32_t in_INIT_on_UART(void)
{
	//TODO: reset buffer
	return INIT;
}
uint32_t in_INIT_on_IONIZE(void)
{
	//ignore
	return INIT;
}
uint32_t in_INIT_on_STOP(void)
{
	//ignore
	return INIT;
}
uint32_t in_INIT_on_CHARGE(void)
{
	//ignore
	return INIT;
}
