#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../include/stack_list.h"

Node *nodeCtr(size_t sizeOfBuf, void *value, Node *next)
{
    assert(next);

    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (!newNode) return NULL;

    newNode->buffer = calloc(sizeOfBuf, sizeof(char));
    if (!newNode->buffer) { free(newNode); return NULL; }

    memmove(newNode->buffer, value, sizeOfBuf);
    newNode->bufferSize = sizeOfBuf;
    newNode->next       = next;

    return newNode;
}

Node *nodeDtr(Node *nod)
{
    assert(nod);
    assert(nod->buffer);

    nod->bufferSize = -1;
    nod->next       = NULL;

    free(nod->buffer);
    free(nod);

    return NULL;
}

Stack* stackCtr(size_t elementSize)
{
    Stack *stk = (Stack *) calloc (1, sizeof(Stack));
    if (!stk) return NULL;

    stk->head       = NULL;
    stk->size       = 0;
    stk->sizeOfElem = elementSize;

    return stk;
}

Stack* stackDtr(Stack* stk)
{
    assert(stk);

    Node *cur = stk->head, *next = NULL;
    while (cur != NULL)
    {
        next = cur->next;
        nodeDtr(cur);
        cur = next;
    }

    stk->head       = NULL;
    stk->size       = -1;
    stk->sizeOfElem = -1;

    return NULL;
}

int stackPush(Stack *stk, void *buffer)
{
    assert(stk);
    assert(buffer);

    Node *newNode = nodeCtr(stk->sizeOfElem, buffer, stk->head);
    if (!newNode) return EXIT_FAILURE;

    stk->size++;
    stk->head = newNode;

    return EXIT_SUCCESS;
}

int stackTop (Stack *stk, void *buffer)
{
    assert(stk);
    assert(buffer);

    if (stk->size == 0) return EXIT_FAILURE;
    memmove(stk->head->buffer, buffer, stk->sizeOfElem);

    return EXIT_SUCCESS;
}

#define RET_ON_ERR(expression)    \
    {                             \
        int error = expression;   \
        if (error) return error;  \
    }   

int stackPop (Stack *stk, void *buffer)
{
    assert(stk);
    assert(buffer);

    RET_ON_ERR(stackTop(stk, buffer));

    Node *top = stk->head;
    stk->head = top->next;
    nodeDtr(top);

    return EXIT_SUCCESS;
}

#undef RET_ON_ERR
