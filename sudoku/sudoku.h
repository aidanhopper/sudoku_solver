#ifndef SUDOKU_H
#define SUDOKU_H

#include "stack.h"
#include "hashmap.h"

typedef struct {
  int values[82];
  int size;
} EntropyArr;

void PrintBoard(char *board);
void GetPossibleNumbers(char *board, int index, int *arr);
int ToIndex(char character);
void GenRandMove(char *board, int **possibleNumbers, Stack *stack);
void PrintPossibleNumbers(int *arr);
void GenerateMove(char *board, int **possibleNumbers, Stack *stack);
int Rand(int range);
void PrintAllPossibleNumbers(int **possibleNumbers);
int Done(char *board);

#endif
