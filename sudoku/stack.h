#ifndef STACK_H
#define STACK_H

struct StackNode {
  char *string;
  struct StackNode *next;
};

typedef struct {
  struct StackNode *head;
  int size;
} Stack;

void StackInit(Stack *stack);
void StackPush(Stack *stack, char *str);
char * StackPop(Stack *stack);
char * StackTop(Stack *stack);
int StackIsEmpty(Stack *stack);
int StackSize(Stack *stack);

#endif
