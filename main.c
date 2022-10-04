#include "sudoku/sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku/stack.h"
#include "sudoku/hashmap.h"

int main() {

  char board[] = {
    ' ', ' ', ' ', /**/ '9', ' ', ' ', /**/ '3', '1', '5',
    ' ', '3', '1', /**/ ' ', '2', ' ', /**/ ' ', '8', ' ',
    ' ', ' ', ' ', /**/ ' ', '3', ' ', /**/ '4', ' ', ' ',
    /***************************************************/
    ' ', ' ', '3', /**/ '8', ' ', ' ', /**/ ' ', ' ', ' ',
    ' ', '6', ' ', /**/ ' ', ' ', ' ', /**/ ' ', '4', ' ',
    ' ', ' ', ' ', /**/ ' ', ' ', '6', /**/ '1', ' ', ' ',
    /***************************************************/
    ' ', ' ', '8', /**/ ' ', '6', ' ', /**/ ' ', ' ', ' ',
    ' ', '7', ' ', /**/ ' ', '8', ' ', /**/ '5', '2', ' ',
    '6', '1', '5', /**/ ' ', ' ', '9', /**/ ' ', ' ', ' ',
    '\0'
  }; 

  int **possibleNumbers = malloc(sizeof(*possibleNumbers) * 81);
  for (int i = 0; i < 81; i++)
    possibleNumbers[i] = malloc(sizeof(*possibleNumbers[i]) * 9);

  Stack stack;
  StackInit(&stack);
  StackPush(&stack, CreateStackNode(&stack, board));

  PrintBoard(board);
  printf("\n##################################\n\n");
  
  while(!Done(board))
    GenRandMove(board, possibleNumbers, &stack);
  
  PrintBoard(board);

  return 0; 
}
