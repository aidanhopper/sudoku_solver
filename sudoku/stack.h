#ifndef STACK_H
#define STACK_H

struct StackNode {
  char *string;
  int **usedNums;
  int id;
  struct StackNode *next;
};

typedef struct {
  struct StackNode *head;
  int size;
  int createdNodes;
} Stack;

void StackInit(Stack *stack);
char *StackTopStr(Stack *stack);
struct StackNode *CreateStackNode(Stack *stack, char *str);
struct StackNode *StackPop(Stack *stack);
void StackPush(Stack *stack, struct StackNode *node);
struct StackNode *StackTop(Stack *stack);
void StackAddNum(Stack *stack, int index, int num);
int StackIsEmpty(Stack *stack);
int StackSize(Stack *stack);

#endif
