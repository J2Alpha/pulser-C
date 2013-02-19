/*
 * iointerupts.h
 *
 *  Created on: 12-okt.-2012
 *      Author: J2Alpha
 *
 *      defines the link between a pin change and an action for interrupt handling.
 *      only for externally caused non-uart actions that may cause a state change and
 *      derive from a GPIO event.
 */
#pragma once
#ifndef ACTIONS_H_
#define ACTIONS_H_

#include "global.h"
#include "peripherialpins.h"

//define a search-able struct collection to differentiate in an interupt
volatile struct IOinterupttype{
	uint32_t port;
	uint32_t pin;
	uint32_t action;
}IO_INT;

		//port		   pin			type
volatile struct IOinterupttype iolist[]={
		{IOPORT,IONIZEINTPIN,(uint32_t)2},//ionize switch
		{IOPORT,CHARGEINTPIN,(uint32_t)1},//pulse switch
		{IOPORT,STOPINTPIN,(uint32_t)3} //stop switch
};
volatile uint32_t NR_of_interupts=sizeof(iolist)/sizeof(IO_INT);


#endif /* ACTIONS_H_ */
