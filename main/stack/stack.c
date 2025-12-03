


#include "stack.h"

#define STACK_EMPTY INT_MIN

typedef struct node{
    unsigned long value;
    struct node *next;
} node;

typedef node* stack;


int push(stack *s, unsigned long value){
    node *newtop = malloc(sizeof(node));
    if (newtop == NULL) return 0;
    newtop->value = value;
    newtop->next = *s;
    *s = newtop;
    return 1;
}

int pop(stack *s){
    if (*s==NULL)return STACK_EMPTY;
    int res = (*s)->value;
    node *tmp = *s;
    *s = (*s)->next;
    free(tmp);
    return res;
}


stack create_stack(){
    stack s = NULL;
    return s;
}


