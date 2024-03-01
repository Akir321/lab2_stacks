#ifndef  __STACK_LIST__
#define  __STACK_LIST__

#include <stddef.h>

struct node;
struct stack;

typedef struct node  Node;
typedef struct stack Stack;

struct node
{
    size_t bufferSize;

    void        *buffer;
    struct node *next;
};

struct stack
{
    size_t sizeOfElem;
    size_t size;

    Node *head;
};

Node *nodeCtr(size_t sizeOfBuf, void *value, Node *next);
Node *nodeDtr(Node *nod);

Stack* stackCtr(size_t elementSize);
Stack* stackDtr(Stack* stk);

int stackPush(Stack *stk, void *buffer);
int stackTop (Stack *stk, void *buffer);
int stackPop (Stack *stk, void *buffer);

#endif //__STACK_LIST__
