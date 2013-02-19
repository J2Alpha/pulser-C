/*
 * LPC17xxPWM.c
 *
 *  Created on: 17-okt.-2012
 *      Author: J2Alpha
 */

#include "LPC17xxPWM.h"
#include "missingtypes.h"
volatile uint32_t match_counter0, match_counter1;

/******************************************************************************
** Function name:		PWM1_IRQHandler
**
** Descriptions:		PWM1 interrupt handler
**						For now, it only deals with PWM1 match 0
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void PWM1_IRQHandler (void)
{
  uint32_t regVal;

  regVal = LPC_PWM1->IR;
  if ( regVal & MR0_INT )
  {
	match_counter1++;
  }
  LPC_PWM1->IR |= regVal;		/* clear interrupt flag on match 0 */
  return;
}

/******************************************************************************
** Function name:		PWM_Init
**
** Descriptions:		PWM initialization, setup all GPIOs to PWM0~6,
**						reset counter, all latches are enabled, interrupt
**						on PWMMR0, install PWM interrupt to the VIC table.
**
** parameters:			ChannelNum, Duty cycle
** Returned value:		true or fase, if VIC table is full, return false
**
******************************************************************************/
uint32_t PWM_Init( uint32_t ChannelNum, uint32_t cycle )
{
  if ( ChannelNum == 1 )
  {
	match_counter1 = 0;
	LPC_PINCON->PINSEL4 = 0x00000555;	/* set GPIOs for all PWM pins on PWM */

	LPC_PWM1->TCR = TCR_RESET;		/* Counter Reset */
	LPC_PWM1->PR = 0x00;			/* prescaler count frequency:Fpclk */
	LPC_PWM1->MCR = PWMMR0R;		/* interrupt on PWMMR0=>PWMMR0I, reset on match PWMMR0=>PWMMR0R, stop whole pwm on match PWMMR0=>PWMMR0S*/
	LPC_PWM1->MR0 = cycle;			/* set PWM cycle length (cycle= max count before reset) */
	LPC_PWM1->MR1 = cycle * 0;		/*M0->M1= high period for ch1 | this may wrap around a reset, so it starts high*/
	LPC_PWM1->MR2 = cycle * 0;		/*M1->M2= high period for ch2 | by for example making M1>M2*/
	LPC_PWM1->MR3 = cycle * 1/2;	/*M2->M3= high period for ch3 */ //used
	LPC_PWM1->MR4 = cycle * 1/4;		/*M4->M5= high period for ch4 */
	LPC_PWM1->MR5 = cycle * 1;		/*M5->M6= high period for ch5 */
	LPC_PWM1->MR6 = cycle * 0;

	/* all PWM latch enabled */
	LPC_PWM1->LER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;
  }
  else
  {
	return ( FALSE );		/* Unknown channel number */
  }

  //NVIC_EnableIRQ(PWM1_IRQn); /*install interrupt into vector table so it actually calls*/
  return (TRUE);
}

/******************************************************************************
** Function name:		PWM_Set
**
** Descriptions:		PWM cycle setup
**
** parameters:			Channel number, PWM cycle, and offset
** Returned value:		None
**
******************************************************************************/
void PWM_Set( uint32_t ChannelNum, uint32_t cycle, uint32_t offset )
{
  if ( ChannelNum == 1 )
  {
	  LPC_PWM1->MR0 = cycle;			/* set PWM cycle (cycle= max count before reset) */
	  LPC_PWM1->MR1 = cycle * 0;			/*M0->M1= high period for ch1 | this may wrap around a reset, so it starts high*/
	  LPC_PWM1->MR2 = cycle * 0;			/*M1->M2= high period for ch2 | by for example making M1>M2*/
	  LPC_PWM1->MR3 = cycle * 0;			/*M3->M4= high period for ch3 */
	  LPC_PWM1->MR4 = cycle * 1/2;			/*M4->M5= high period for ch4 */
	  LPC_PWM1->MR5 = cycle * 1/2;			/*M5->M6= high period for ch5 */
	  LPC_PWM1->MR6 = cycle * 1;

	/* The LER will be cleared when the Match 0 takes place, in order to
	load and execute the new value of match registers, all the PWMLERs need to
	reloaded. all PWM latch enabled */
	LPC_PWM1->LER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;
  }
  return;
}

/******************************************************************************
** Function name:		PWM_Start
**
** Descriptions:		Enable PWM by setting the PCR, PTCR registers
**
** parameters:			channel number
** Returned value:		None
**
******************************************************************************/
void PWM_Start( uint32_t channelNum )
{
  if ( channelNum == 1 )
  {
	/* All double edge, all enable */
	LPC_PWM1->PCR = 			 PWMSEL2 | PWMSEL3 | PWMSEL4 | PWMSEL5 | PWMSEL5
				 	 | PWMENA1 | PWMENA2 | PWMENA3 | PWMENA4 | PWMENA5 | PWMENA6;
	LPC_PWM1->TCR = TCR_CNT_EN | TCR_PWM_EN;	/* counter enable, PWM enable */
  }
  return;
}

/******************************************************************************
** Function name:		PWM_Stop
**
** Descriptions:		Stop all PWM channels
**
** parameters:			channel number
** Returned value:		None
**
******************************************************************************/
void PWM_Stop( uint32_t channelNum )
{
  if ( channelNum == 1 )
  {
	LPC_PWM1->PCR = 0;
	LPC_PWM1->TCR = 0x00;		/* Stop all PWMs */
  }
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

