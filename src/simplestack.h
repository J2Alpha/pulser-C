#ifndef STACK_H
#define STACK_H


#include <stdlib.h>
#include "global.h"
/*!
	\brief pre-allocated stack

	intended to provide the ability to queue commands via an interrupt in a simple way
	implements all classical stack commands
	not dynamically typed only accepts elements of one type defined at compile time
*/
typedef int32_t element ;

/* causes hardfaults when assigning values?
//! \brief stack like struct
typedef struct{
	uint32_t size;
	int32_t top;
	element* content;

}SIMPLESTACK;
*/
//ok then, be a hardfaulting bitch, heres a linked list variant
typedef struct LN
{
	element content;
	struct LN *next;
}LN;

LN * Push(LN * newtop, element newel );
LN * Pop(LN * Top);

/* belong to the hardfaulting stack implementation
//classic stack commands
//! \brief allocate stack
element stackinit(SIMPLESTACK* newstack, uint32_t max);
//get top element
element pop(SIMPLESTACK* stack);
//! \brief add element to the bottom
element push(SIMPLESTACK* stack, element newcom);
//! \brief check for empty
element is_empty(SIMPLESTACK* stack);
//! \brief check for full
element is_full(SIMPLESTACK* stack);
//! \brief call this to safely remove the contents, don't forget to destroy the reference afterwards
element destroy(SIMPLESTACK* deadstack);
*/
#endif
