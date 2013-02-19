/*
 * uartprotocol.h
 *
 *  Created on: 27-okt.-2012
 *      Author: J2Alpha
 */

#ifndef UARTPROTOCOL_H_
#define UARTPROTOCOL_H_

//normal protocol size definition
/*******************************************************************************
 * |          KEY           | 		FRAME1		|FRAME2|...	|     CONTROL    | *
 * |REQUESTKIND|NR_OF_FRAMES|DEVICE|ACTION|VALUE|...   |	|NR_OF_FRAMES<<16| *
 * |   0b16    |    0b16    | 0b16 | 0b16 | 0b32|...        |      0b32      | *
 *******************************************************************************/

#define KEY_SIZE = 32
#define REQUEST_KIND = 16
#define NR_OF_FRAMES = 16
#define FRAME_SIZE = 32
#define DEVICE = 16
#define ACTION = 16
#define VALUE = 32
#define CONTROLSIZE = 32
#define CONTROLL_OFFSET = 16
#define SMALLEST_FRAME = 4 //32bit (Dwords)
#define LARGEST_FRAME = SMALLEST_FRAME+(SMALLEST_FRAME-2)*14//assumed max size (in Dwords)

//request kinds
#define NO_ANS   0x8A //no answer
#define ANS      0x8C //answer only
#define ECHO     0xA8 //echo only
#define ECHO_ANS 0xC8 //echo then answer

//peripherials and actions
#define OSCILATOR    0x01
	#define STOP		 0x01
	#define START        0x02
#define CHARGER      0x02
	#define STOP		 0x01
	#define START        0x02
#define STOP_ALL     0x03
/**********************************************************
 * test info frame definition
 * |key| state | charged| pwm |
 * |0b8|  0b8  |   0b8  | 0b8 |
 ***********************************************************/

#endif /* UARTPROTOCOL_H_ */
