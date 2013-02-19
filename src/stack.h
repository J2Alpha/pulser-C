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

//! \brief stack like struct
typedef struct stack{
element *content;
uint32_t size;
int32_t top;
}STACK;

//classic stack commands
//! \brief allocate stack
element stackinit( STACK* newstack, uint32_t max);
//get top element
element pop(STACK* stack);
//! \brief add element to the bottom
element push(STACK* stack, element newcom);
//! \brief check for empty
element is_empty(STACK* stack);
//! \brief check for full
element is_full(STACK* stack);
//! \brief call this to safely remove the contents, don't forget to destroy the reference afterwards
element destroy(STACK* deadstack);

#endif
