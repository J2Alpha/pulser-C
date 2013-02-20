/*
 * lpc17xxIO.c
 *
 *  Created on: 10 okt. 2012
 *      Author: J2Alpha
 */
#include "lpc17xxIO.h"
#include "iointerupts.h"
#include "peripherialpins.h"

void Initialise_Port(uint32_t Port, uint32_t mask, uint32_t direction)
{
	switch(Port)
	{
		case 0:
			LPC_GPIO0->FIOMASK= mask;
			LPC_GPIO0->FIODIR = direction;
			LPC_GPIO0->FIOCLR = 0xFFFFFFFF;
			break;
		case 1:
			LPC_GPIO1->FIOMASK= mask;
			LPC_GPIO1->FIODIR = direction;
			LPC_GPIO1->FIOCLR = 0xFFFFFFFF;
			break;
		case 2:
			LPC_GPIO2->FIOMASK= mask;
			LPC_GPIO2->FIODIR = direction;
			LPC_GPIO2->FIOCLR = 0xFFFFFFFF;
			break;
		case 3:
			LPC_GPIO3->FIOMASK= mask;
			LPC_GPIO3->FIODIR = direction;
			LPC_GPIO3->FIOCLR = 0xFFFFFFFF;
			break;
		default:
			break;
	}
}
void Set_Pin_HI(uint32_t Port, uint32_t data)
{
	switch(Port)
		{
			case 0:
				LPC_GPIO0->FIOSET = data;

				break;
			case 1:
				LPC_GPIO1->FIOSET = data;
				break;
			case 2:
				LPC_GPIO2->FIOSET = data;
				break;
			case 3:
				LPC_GPIO3->FIOSET = data;
				break;
			default:
				break;
		}
}
void Set_Pin_LO(uint32_t Port, uint32_t data)
{
	switch(Port)
			{
				case 0:
					LPC_GPIO0->FIOCLR = data;
					break;
				case 1:
					LPC_GPIO1->FIOCLR = data;
					break;
				case 2:
					LPC_GPIO2->FIOCLR = data;
					break;
				case 3:
					LPC_GPIO3->FIOCLR = data;
					break;
				default:
					break;
			}
}
void Get_Input_From_Port(uint32_t Port, uint32_t *data,uint32_t mask)
{
	switch(Port)
		{
			case 0:
				*data = (mask>0) ? (LPC_GPIO0->FIOPIN&LPC_GPIO0->FIOMASK) : (LPC_GPIO0->FIOPIN);
				break;
			case 1:
				*data = (mask>0) ? (LPC_GPIO1->FIOPIN&LPC_GPIO1->FIOMASK) : (LPC_GPIO1->FIOPIN);
				break;
			case 2:
				*data = (mask>0) ? (LPC_GPIO2->FIOPIN&LPC_GPIO2->FIOMASK) : (LPC_GPIO2->FIOPIN);
				break;
			case 3:
				*data = (mask>0) ? (LPC_GPIO3->FIOPIN&LPC_GPIO3->FIOMASK) : (LPC_GPIO3->FIOPIN);
				break;
			default:
				break;
		}
}
void Set_pin_interupts(uint32_t Port,uint32_t edge, uint32_t data)
{
	switch(Port)
			{
				case 0:
					switch(edge)
					{
						case 0:
							LPC_GPIOINT->IO0IntEnR = data;
							break;
						case 1:
							LPC_GPIOINT->IO0IntEnF = data;
							break;
						case 2:
							LPC_GPIOINT->IO0IntEnR = data;
							LPC_GPIOINT->IO0IntEnF = data;
							break;
						default:
							break;
					}
					break;
				case 2:
					switch(edge)
					{
						case 0:
							LPC_GPIOINT->IO2IntEnR = data;
							break;
						case 1:
							LPC_GPIOINT->IO2IntEnF = data;
							break;
						case 2:
							LPC_GPIOINT->IO2IntEnR = data;
							LPC_GPIOINT->IO2IntEnF = data;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
}
extern void EINT3_IRQHandler(void)
{
	uint32_t interuption=0xFFFFFFFF;
	//interrupt on port 0 or 2
	if(LPC_GPIOINT->IntStatus&0b1)
	{
		//TODO urgent: rising or falling edge detection might be safer to do in the future
		IO_Interupt_Push(0,1,LPC_GPIOINT->IO0IntStatR);
		IO_Interupt_Push(0,0,LPC_GPIOINT->IO0IntStatF) ;
	}
	if(LPC_GPIOINT->IntStatus&0b1<<1)
	{
		//rising or falling
		IO_Interupt_Push(2,1,LPC_GPIOINT->IO2IntStatR);
		IO_Interupt_Push(2,0,LPC_GPIOINT->IO2IntStatF) ;
	}
	LPC_GPIOINT->IO0IntClr=interuption;
}
void IO_Interupt_Push(uint32_t Port, uint32_t Edge, uint32_t Pins)
{
	uint32_t i=0;
	for(i=0;i<NR_of_interupts;i++)
	{
		if(Port==iolist[i].port)
		{
			if(Pins==iolist[i].pin)
			{//TODO: edge detection
				//currentaction=iolist[i].action;
				topofstack=Push(topofstack,iolist[i].action);
			}
		}
	}
}
