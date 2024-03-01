#ifndef  __STACK_ARRAY__
#define  __STACK_ARRAY__

#include <stddef.h>

struct stack
{
    size_t sizeOfElem;
    size_t capacity;
    size_t size;

    void *data;
    void *curPlace;
};

typedef struct stack Stack;

Stack *stackCtr(size_t size, size_t elementSize);
Stack *stackDtr(Stack *stk);

int stackPush(Stack *stk, void *buffer);
int stackTop (Stack *stk, void *buffer);
int stackPop (Stack *stk, void *buffer);

#endif //__STACK_ARRAY__
