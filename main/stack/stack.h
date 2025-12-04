#ifndef STACK_MY
#define STACK_MY

#include <limits.h>
#include <stdlib.h>

#define STACK_EMPTY INT_MIN

// typedef struct myStack stack;
typedef struct node node;
typedef node* stack;

stack create_stack();
int push(stack *s, unsigned long value);
unsigned long pop(stack *s);


#endif