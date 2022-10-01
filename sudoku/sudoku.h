#ifndef SUDOKU_H
#define SUDOKU_H

void PrintBoard(char *board);
void GetPossibleNumbers(char *board, int index, int *arr);
int ToIndex(char character);

#endif
