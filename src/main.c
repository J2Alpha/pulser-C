/*
===============================================================================
 Name        : main.c
 Author      : J.F.R. BOEVA
 Version     : 2.1
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other include files here
#include "global.h"
#include "statemap.h"
#include "stack.h"

#include "LPC17xxUART.h"
#include "LPC17xxPWM.h"
#include "LPC17xxIO.h"
// TODO: finish definitions and declarations here
//pwm values
#define CYCLELENGTH 100
#define STACKLENGTH 10
//ports
//port0
#include "peripherialpins.h"

#define PULSESWITCH 0x00000001
#define CHARGESWITCH 0x00000002

volatile int32_t currentaction;//the poor man's stack, this shouldn't even be volatile
volatile uint32_t currentstate;//careful with the volatiles tough, runtime asplosions may follow
volatile STACK* pileP;//caveat implementor
//what the heck is going on with my simple stack
//it doesn't work due to compiler quirks?
//but don't remove unless you wanna rewrite half of this
//causing hard faults, bullshit
//probably that redlib thing is involved in this
//don't use references to stack until I solve this
//for now the completely unsafe and completely unscaleble currentaction thing is used directly


void initializer(void);
int32_t getnextaction(STACK *stackP);

int main(void)
{
	while(1)
	{
		currentstate = INIT;//autism mode
		initializer();
		currentstate = WAIT;//active waiting mode
		uint8_t message[1]={'a'};
		while(currentstate != INIT)
		{
			//UART_Send( 0, message, 1 );
			int32_t action=currentaction;//getnextaction(pileP); /* get the next action from the stack*/
			if (((action>=0)&&(action<ACTIONLIMIT))&&((currentstate>=0)&&(currentstate<STATELIMIT)))
			{
				//look busy
				currentstate=state_map [currentstate][action] ();
				currentaction=-1;//remove when stack is fixed
			}
			else /* a catch all, do nothing or handle faulty call, just make sure it catches all */
			{
				if(action==ACTIONLIMIT)//do nothing action called on purpose
				{
					//do nothing, deliberately
				}
				if(action==-1)//stack was empty if we still used it
				{
					//never do nothing at all
				}
				if((action<-1)||(action>ACTIONLIMIT))//action not known, can happen but shouldn't happen
				{
					//TODO:output action fault onto uart for debugging
					//ignore and do nothing, it should be recoverable
				}
				if((currentstate<0)||(currentstate>STATELIMIT))//unknown state, something is seriously fubared
				{
					//TODO: try to put faulty state on uart before reset
					currentstate=INIT;//assume non-recoverable, reset controller TODO: possibly need to reset it harder
				}
			}
		}
	}
	return 0;
}

void initializer()
{
	//SystemClockUpdate();
	stackinit(pileP, STACKLENGTH);//TODO fix stack for cortex m3 or find one that works
	init_UART( 0,BAUDRATE );
	uint8_t sendstring[7]={'U','A','R','T',' ','O','K'};
	UART_Send( 0, sendstring, 1 );
	PWM_Init( 1 , CYCLELENGTH );
	Initialise_Port(IOPORT, IOPORTMASK, IOPORTDIRECTION);
	Set_pin_interupts(IOPORT, INTERUPTEDGES_0, INTPINS_0);//rewire, discover first
	NVIC_EnableIRQ(EINT3_IRQn);//enable external interupt 3 for gpio interupts
	currentaction=-1;
	//TODO: init UART etc.
	return;
}
int32_t getnextaction(STACK *stackP)
{
	if(is_empty(stackP))
	{
		return ACTIONLIMIT;
	}
	return (int32_t)pop(stackP);
}
