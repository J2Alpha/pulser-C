#include "stack.h"

element stackinit(STACK* newstack, uint32_t maxlength)
{
  element *newset;
  newset = (element *) malloc(sizeof(element) * maxlength);//allocate memspace
  if (newset == NULL)//if true, can't allocate enough memory 
  {
    return 0;
  }
  newstack->content = newset;//point everything in right way
  newstack->size = maxlength;//maxlength;
  newstack->top = -1;//set empty
  return 1;
}

element pop(STACK* stack)
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
element push(STACK* stack, element newelement)
{
	if (is_full(stack)) 
	{
		return 0;
	}
	stack->content[(++(stack->top))] = newelement;
	return 1;
}
element is_empty(STACK* stack)
{
	return (stack->top==-1);
}
element is_full(STACK* stack)
{
	return (stack->top==stack->size-1);
}
element destroy(STACK* deadstack)
{
	free(deadstack->content);
	deadstack->content=NULL;
	deadstack->size=0;
	deadstack->top=-1;
	return 1;
}
