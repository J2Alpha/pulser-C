/*
 * peripherialpins.h
 *
 *  Created on: 17-okt.-2012
 *      Author: J2Alpha
 * contains hardware locations for the various interfaces
 * TODO: set pins right
 */
#ifndef PERIPHERIALPINS_H_
#define PERIPHERIALPINS_H_

/********************************
 *pins, ports and constants etc.*
 ********************************/

//pins
#define IOPORT 			0x0
#define CHARGEPIN  		0b1<<4
#define CHARGELED  		0b1<<24
#define CHARGEINTPIN	0b1<<27
#define	IONIZEPIN  		0b0
#define IONIZELED  		0b1<<25
#define IONIZEINTPIN	0b1<<28
#define STOPINTPIN		0b1<<31
//set up port 0
//readable/writable pins 0=R/Wable 1=NOT R/Wable
#define IOPORTMASK 0x0//don't use for now

//directions of pins 0=in 1=out
#define IOPORTDIRECTION (CHARGELED|CHARGEPIN|IONIZEPIN|IONIZELED)

/********************************
 *interrupt definitions etc.     *
 ********************************/

//interrupt initializer
#define INTERUPTEDGES_0	2 //0=falling 1=rising 2=any
#define INTPINS_0		IONIZEINTPIN|CHARGEINTPIN

//UART
#define BAUDRATE 57600
#define FRAME 0xC
//don't forget to adapt ioinerupts.h after any changes

#endif /* PERIPHERIALPINS_H_ */
