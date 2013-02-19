/*
 * lpc17xxUart.c
 *
 *  Created on: 9 okt. 2012
 *      Author: J2Alpha
 */

#include "lpc17xxUart.h"
extern volatile int32_t currentaction;
//variables
volatile uint8_t UART0TxEmpty=1, UART1TxEmpty=1;//=1
volatile uint8_t UART0Buffer[BUFSIZE], UART1Buffer[BUFSIZE];

/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART port, setup pin select,
**						clock, parity, stop bits, FIFO, etc.
**
** parameters:			portNum(0 or 1) and UART baudrate
** Returned value:		true or false, return false only if the
**						interrupt handler can't be installed to the
**						VIC table
**
*****************************************************************************/
uint32_t init_UART( uint32_t PortNum, uint32_t baudrate )
{
	uint32_t Fdiv;
	uint32_t pclkdiv, pclk;

	if ( PortNum == 0 )
	{
		LPC_PINCON->PINSEL0 &= ~0x000000F0;
		LPC_PINCON->PINSEL0 |= 0x00000050;  /* RxD0 is P0.3 and TxD0 is P0.2 */
		/* By default, the PCLKSELx value is zero, thus, the PCLK for
		all the peripherals is 1/4 of the SystemFrequency. */
		/* Bit 6~7 is for UART0 */
		/*here be dragons*/
		pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
		switch ( pclkdiv )
		{
		case 0x00:
		default:
			pclk = SystemCoreClock/4;
			break;
		case 0x01:
			pclk = SystemCoreClock;
			break;
		case 0x02:
			pclk = SystemCoreClock/2;
			break;
		case 0x03:
			pclk = SystemCoreClock/8;
			break;
		}

		LPC_UART0->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
		Fdiv = ( pclk / 16 ) / baudrate ;	/*baud rate */
		LPC_UART0->DLM = Fdiv / 256;
		LPC_UART0->DLL = Fdiv % 256;
		LPC_UART0->LCR = 0x03;		/* DLAB = 0 */
		LPC_UART0->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

		NVIC_EnableIRQ(UART0_IRQn);

		LPC_UART0->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART0 interrupt */
		return (1);
	}
	else if ( PortNum == 1 )
	{
		LPC_PINCON->PINSEL4 &= ~0x0000000F;
		LPC_PINCON->PINSEL4 |= 0x0000000A;	/* Enable RxD1 P2.1, TxD1 P2.0 */

		/* By default, the PCLKSELx value is zero, thus, the PCLK for
		all the peripherals is 1/4 of the SystemFrequency. */
		/* Bit 8,9 are for UART1 */
		pclkdiv = (LPC_SC->PCLKSEL0 >> 8) & 0x03;
		switch ( pclkdiv )
		{
		case 0x00:
		default:
			pclk = SystemCoreClock/4;
			break;
		case 0x01:
			pclk = SystemCoreClock;
			break;
		case 0x02:
			pclk = SystemCoreClock/2;
			break;
		case 0x03:
			pclk = SystemCoreClock/8;
			break;
		}

		LPC_UART1->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
		Fdiv = ( pclk / 16 ) / baudrate ;	/*baud rate */
		LPC_UART1->DLM = Fdiv / 256;
		LPC_UART1->DLL = Fdiv % 256;
		LPC_UART1->LCR = 0x03;		/* DLAB = 0 */
		LPC_UART1->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

		NVIC_EnableIRQ(UART1_IRQn);

		LPC_UART1->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART1 interrupt */
		return (1);
	}
	return(0);
}

/*****************************************************************************
** Function name:		UARTSend
**
** Descriptions:		Send a block of data to the UART 0 port based
**						on the data length
**
** parameters:			portNum, buffer pointer, and data length
** Returned value:		None
**
*****************************************************************************/
void UART_Send( uint32_t portNum, uint8_t *BufferPtr, uint32_t Length )
{
  if ( portNum == 0 )
  {
    while ( Length != 0 )
    {
	  /* THRE status, contain valid data */
	  while ( !(UART0TxEmpty & 0x01) );
	  LPC_UART0->THR = *BufferPtr;
	  UART0TxEmpty = 0;	/*do not empty in the THR until it shifts out */
	  BufferPtr++;
	  Length--;
	}
  }
  else
  {
	/*
	while ( Length != 0 )
    {
	  /* THRE status, contain valid data *//*
	  while ( !(UART1TxEmpty & 0x01) );//UART1TxEmpty
	  LPC_UART1->THR = *BufferPtr;
	  UART1TxEmpty = 0;	/* not empty in the THR until it shifts out UART1TxEmpty*//*
	  BufferPtr++;
	  Length--;
    }
    */
  }
  return;
}

/*****************************************************************************
** Function name:		UART0_IRQHandler
**
** Descriptions:		UART0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void UART0_IRQHandler (void)
{
  uint8_t IIRValue, LSRValue;
  uint8_t Dummy = Dummy;
  uint8_t UART0StatusDummy = 0;

  IIRValue = LPC_UART0->IIR;

  IIRValue >>= 1;					/* skip pending bit in IIR */
  IIRValue &= 0x07;					/* check bit 1~3, interrupt identification */
  if ( IIRValue == IIR_RLS )		/* Receive Line Status type interupt*/
  {
	LSRValue = LPC_UART0->LSR; 		//get the actual status to clear it
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) ) /* There are errors or a break interrupt */
	{
	  UART0StatusDummy = LSRValue; // read and forget variable for now
	  Dummy = LPC_UART0->RBR;		  // then Dummy read on RX to clear interrupt, then go back out */
	  return;
	}
	if ( LSRValue & LSR_RDR )		/* Receive Data Ready */
	{
	  /* If no error on RLS, normal ready, push onto stack.
	   * unless full then just bail, comment that part out if a reset by memory overflow is a feature to get out of an interrupt lock
	   * Note: read RBR will clear the interrupt */
	  if ( is_full(pileP) )
	  {
		  Dummy = LPC_UART0->RBR;
		  return;
	  }
	  push(pileP,  LPC_UART0->RBR);
	}
  }
  else if ( IIRValue == IIR_RDA )	/* Receive Data Available, just to handle any eventuality like an earlier buffer overflow*/
  {
	  if ( is_full(pileP) )
	  {
		 Dummy = LPC_UART0->RBR;
	  	 return;
	  }
	  push(pileP,  LPC_UART0->RBR);
  }
  else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
  {
	  UART0StatusDummy |= 0x100;		/* Bit 9 as the CTI error */
  }
  else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
  {
	/* THRE interrupt */
	LSRValue = LPC_UART0->LSR;		/* Check status in the LSR to see if valid data in U0THR or not */
	if ( LSRValue & LSR_THRE )
	{
	  UART0TxEmpty = 1;
	}
	else
	{
	  UART0TxEmpty = 0;
	}
  }
currentaction=0;
}
void encode(device,message)
{
	//will be a lot safer with functional a stack, no monkeypatching of overflows
}
void decode(recievebuffer)
{
	//needs a stack, same argument
}
