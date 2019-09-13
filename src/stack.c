#include <stack.h>
#include <stdlib.h>
#define LIMIT MAX_STACK_SIZE-1
static int top = -1;
static void *data[MAX_STACK_SIZE];

int stack_push(void *el){
	if(top >= LIMIT)
		return -1; /* stack overflow. */
	data[++top] = el;
	return 0;
}

int stack_pop(void **el){
	if(top == -1)
		return -1; /* stack empty */
	*el = data[top--];
	return 0;
}
