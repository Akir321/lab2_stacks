#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stack_array.h"

static int stackRealloc(Stack *stk);

const int ReallocRate = 2;

#define LOG(...) //printf(__VA_ARGS__)


Stack *stackCtr(size_t size, size_t elementSize)
{
    Stack *stk = (Stack *)calloc(1, sizeof(Stack));
    if (!stk)                    return NULL;

    stk->data  = (void *)calloc(size, elementSize);
    if (!stk->data) { free(stk); return NULL; }

    stk->curPlace   = stk->data;
    stk->sizeOfElem = elementSize;
    stk->capacity   = size;
    stk->size       = 0;

    return stk;
}

Stack *stackDtr(Stack *stk)
{
    assert(stk);
    assert(stk->data);

    stk->capacity   =  0;
    stk->size       = -1;
    stk->sizeOfElem = -1;

    free(stk->data);
    free(stk);

    return NULL;
}

#define RET_ON_ERR(expression)    \
    {                             \
        int error = expression;   \
        if (error) return error;  \
    }   


int stackRealloc(Stack *stk)
{
    assert(stk);
    assert(stk->data);

    if      (stk->size >= stk->capacity) stk->capacity *= ReallocRate;

    else if (stk->size <= stk->capacity * ReallocRate * ReallocRate)  
                                         stk->capacity /= ReallocRate;

    else                                 return EXIT_SUCCESS;
    
    stk->data = (void *)realloc(stk->data, stk->capacity * stk->sizeOfElem);
    if (!stk->data) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}        

int stackPush(Stack *stk, void *buffer)
{
    assert(stk);
    assert(stk->data);
    assert(buffer);

    RET_ON_ERR(stackRealloc(stk));

    memmove(stk->curPlace, buffer, stk->sizeOfElem);
    stk->curPlace += stk->sizeOfElem;
    stk->size++;

    return EXIT_SUCCESS;
}

int stackTop (Stack *stk, void *buffer)
{
    assert(stk);
    assert(stk->data);
    assert(buffer);

    if (stk->size == 0) return EXIT_FAILURE;
    memmove(buffer, stk->curPlace, stk->sizeOfElem);

    return EXIT_SUCCESS;
}

int stackPop(Stack *stk, void *buffer)
{
    assert(stk);

    RET_ON_ERR(stackTop(stk, buffer));
    stk->curPlace -= stk->sizeOfElem;
    stk->size--;

    return EXIT_SUCCESS;
}

#undef RET_ON_ERR
#undef LOG
