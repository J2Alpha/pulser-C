#include "simplestack.h"
#include <stdio.h>

LN * Push(LN * newtop, element newel )
{
	static LN * newLN;
	newLN =calloc(sizeof(LN),1);
	newLN->content=newel;
	newLN->next =newtop;

	return newLN;
}
LN * Pop(LN * Top)
{
    static LN * newtop;
    newtop = Top->next;
    free(Top);

    return newtop;
}

/* belongs to the stack implementation
element stackinit(SIMPLESTACK* newstack, uint32_t maxlength)
{
  //element *newset;
  //newset = (element *) calloc(sizeof(element) * maxlength);//allocate memspace calloc vs malloc
  //if (newset == NULL)//if true, can't allocate enough memory
  //{
  //  return 0;
  //}
  newstack->content = new element[maxlength];//newset;//point everything in right way
  newstack->size = maxlength;//maxlength;
  newstack->top = -1;//set empty
  return 1;
}

element pop(SIMPLESTACK* stack)
{
	if (is_empty(stack)) 
	{
    return 0;
  	}
	uint32_t comnew=stack->content[(stack->top)--];
	//stack->content[(stack->top)]=0; set to zero needed?
	//(stack->top)--;
	return comnew;
		
}
element push(SIMPLESTACK* stack, element newelement)
{
	if (is_full(stack)) 
	{
		return 0;
	}
	stack->content[(++(stack->top))] = newelement;
	return 1;
}
element is_empty(SIMPLESTACK* stack)
{
	return (stack->top==-1);
}
element is_full(SIMPLESTACK* stack)
{
	return (stack->top==stack->size-1);
}
element destroy(SIMPLESTACK* deadstack)
{
	free(deadstack->content);
	deadstack->content=NULL;
	deadstack->size=0;
	deadstack->top=-1;
	return 1;
}
*/
