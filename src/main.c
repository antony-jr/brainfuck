#include <stack.h>
#include <stdio.h>

int main(){
	char *a1 = "Hello";
	char *a2 = "World";
	stack_push(a1);
	stack_push(a2);

	char *ptr = NULL;
	stack_pop(&ptr);
	printf("%s\n", ptr);
	stack_pop(&ptr);
	printf("%s\n", ptr);
	return 0;
}
