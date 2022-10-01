#ifndef SUDOKU_H
#define SUDOKU_H

#include "stack.h"

void PrintBoard(char *board);
void GetPossibleNumbers(char *board, int index, int *arr);
int ToIndex(char character);
void PrintPossibleNumbers(int *arr);
void GenerateMove(char *board, int **possibleNumbers, Stack *stack);
int FindLowestEntropy(int **possibleNumbers);
int Rand(int range);
char GenerateNumber(int *possibleNumbers);

#endif
