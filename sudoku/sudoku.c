#include "sudoku.h"
#include <stdio.h>

void PrintBoard(char *board) {
  for (int i = 0; i < 81; i++) {
    if (i == 26) printf("\n-----------------------------");
    if (i == 53) printf("\n-----------------------------");
    if (i % 9 == 0 && i != 0) printf("\n");
    else if (i % 3 == 0 && i != 0) printf("|");
    printf(" %c ", board[i]);
  }
  printf("\n");
}

int ToIndex(char character) {
  return character - 49;
}

void PrintPossibleNumbers(int *arr) {
  printf("[");
  for (int i = 0; i < 9; i++) {
    if (arr[i] == 1) printf(" %d:T", i+1);
    else if(arr[i] == 0) printf(" %d:F", i+1);  
    else printf(" %d:F", arr[i]);  
  }
  printf(" ]\n");
}

void GetPossibleNumbers(char *board, int index, int *arr) {
  if (board[index] != ' ') {
    for (int i = 0; i < 9; i++)
      arr[i] = -1;
    return;
  }

  // sets entire array to true so that when number is found it is set to false
  for (int i = 0; i < 9; i++)
    arr[i] = 1;

  int row = index / 9;
  int col = index % 9;

  // search row 
  for (int i = row * 9; i < (row * 9) + 9; i++)
    if (board[i] != ' ')
      arr[ToIndex(board[i])] = 0;

  // search col
  for (int i = col; i < 72 + col; i = i + 9)
    if (board[i] != ' ')
      arr[ToIndex(board[i])] = 0;

  // search square
  int squareRow = row / 3;
  int squareCol = col / 3;
  for (int i = 0; i < 9; i++) {
    int squareIndex = (squareRow * 27) + (i / 3 * 9) + (squareCol * 3) + (i % 3);
    if (squareIndex != index)
      if(board[squareIndex] != ' ')
	arr[ToIndex(board[squareIndex])] = 0;
  }
}

int FindLowestEntropy(int **possibleNumbers) {
  int lowestEntropyIndex = -1;
  int lowestEntropyVal = 9;
  for (int row = 0; row < 81; row++) {
    int localEntropyVal = 9;
    for (int col = 0; col < 9; col++ ) {
      if (possibleNumbers[row][0] == -1)
	break; 
      if (possibleNumbers[row][col] == 0)
	localEntropyVal--;
    }
    if (possibleNumbers[row][0] != -1) 
      if (lowestEntropyVal > localEntropyVal) {
	lowestEntropyVal = localEntropyVal;
	lowestEntropyIndex = row;
	if (lowestEntropyVal == 1)
	  return lowestEntropyIndex;
      }
  }
  return lowestEntropyIndex;
}

void PrintAllPossibleNumbers(int **possibleNumbers) {
  for (int i = 0; i < 81; i++)
    if (possibleNumbers[i][0] != -1) {
      printf("%d ", i);
      PrintPossibleNumbers(possibleNumbers[i]);
    }
}

void GenerateMove(char *board, int **possibleNumbers) {
  // generates possible numbers for every position on the board
  for (int i = 0; i < 81; i++)
    GetPossibleNumbers(board, i, possibleNumbers[i]);

  // PrintAllPossibleNumbers(possibleNumbers);

  // finds the lowest entropy index
  int LEI = FindLowestEntropy(possibleNumbers);
  int *LEINumbers = possibleNumbers[LEI];

  printf("%d ", LEI);
  PrintPossibleNumbers(LEINumbers);
  
}
