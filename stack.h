#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>
#include "pizza.h"

#if !defined(__bool_true_false_are_defined) && !defined(__cplusplus)
typedef int bool;
#define true 1
#define false 0
#define __bool_true_false_are_defined
#endif
#define StackItem t_piece*

typedef struct e_piece t_piece;

typedef struct StackNode {
    StackItem item;				/** The data of this node. **/
    struct StackNode *next;		/** The next node (the one below the top). **/
} StackNode;

typedef struct {
    size_t count; 	/** The number of items in the stack. **/
    StackNode *top;	/** The top item of the stack. **/
} Stack;

Stack *stackCreate();
void stackDestroy(Stack *stack);
void stackClean(Stack *stack);
bool stackIsEmpty(Stack *stack);
size_t stackSize(Stack *stack);
StackItem stackTop(Stack *stack);
bool stackPush(Stack *stack, StackItem item);
StackItem stackPop(Stack *stack);

#endif