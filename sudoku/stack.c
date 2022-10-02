#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

void StackInit(Stack *stack) {
  stack->size = 0;
  stack->head = NULL;
}

void StackPush(Stack *stack, char *str) {
  stack->size++;
  struct StackNode *node = malloc(sizeof(struct StackNode));
  char *string = malloc(sizeof(char *) * 82);
  strcpy(string, str);
  node->string = string;
  node->next = stack->head;
  stack->head = node;
}

char * StackPop(Stack *stack) {
  if (stack->size != 0) {
    stack->size--;
    char * str = stack->head->string;
    struct StackNode *nextNode = stack->head->next;
    //free(stack->hea1);
    stack->head = nextNode;
    return str;
  }
  return "";
}

char * StackTop(Stack *stack) {
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
