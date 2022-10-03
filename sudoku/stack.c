#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

void StackInit(Stack *stack) {
  stack->size = 0;
  stack->createdNodes = 0;
  stack->head = NULL;
}

void StackPush(Stack *stack, struct StackNode *node) {
  node->next = stack->head;
  stack->size++;
  stack->head = node;
}

struct StackNode *CreateStackNode(Stack *stack, char *str) {
  struct StackNode *node = malloc(sizeof(struct StackNode));
  node->usedNums = malloc(sizeof(*node->usedNums) * 81);
  for (int i = 0; i < 81; i++)
    node->usedNums[i] = malloc(sizeof(*node->usedNums[i]) *9);
  stack->createdNodes++;
  node->id = stack->createdNodes;
  char *string = malloc(sizeof(char *) * 82);
  strcpy(string, str);
  node->string = string;
  for (int i = 0; i < 81; i++)
    for (int j = 0; j < 9; j++)
      node->usedNums[i][j] = 0;
  return node;
}

void StackAddNum(Stack *stack, int index, int num) {
  stack->head->usedNums[index][num] = 1;
}

struct StackNode *StackPop(Stack *stack) {
  if (stack->size != 0) {
    stack->size--;
    struct StackNode *node = stack->head;
    struct StackNode *nextNode = stack->head->next;
    stack->head = nextNode;
    return node;
  }
  return NULL;
}

struct StackNode *StackTop(Stack *stack) {
  return stack->head; 
}

char *StackTopStr(Stack *stack) {
  if (stack->size != 0)
    return stack->head->string;
  return "";
}

int StackIsEmpty(Stack *stack) {
  if (stack->size != 0)
    return 0;
  return 1;
}

int StackSize(Stack *stack) {
  return stack->size;
}
