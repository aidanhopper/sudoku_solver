#ifndef SUDOKU_H
#define SUDOKU_H

void PrintBoard(char *board);
void GetPossibleNumbers(char *board, int index, int *arr);
int ToIndex(char character);
void PrintPossibleNumbers(int *arr);
void GenerateMove(char *board, int **possibleNumbers);
int FindLowestEntropy(int **possibleNumbers);

#endif
