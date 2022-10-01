#include "sudoku.h"
#include <stdio.h>

void PrintBoard(char *board) {
  for (int i = 0; i < 81; i++) {
    if (i == 26) printf("\n----------------------------");
    if (i == 53) printf("\n----------------------------");
    if (i % 9 == 0 && i != 0) printf("\n");
    else if (i % 3 == 0 && i != 0) printf("|");
    printf(" %c ", board[i]);
  }
}

int ToIndex(char character) {
  return character - 49;
}

void GetPossibleNumbers(char *board, int index, int *arr) {
  // sets entire array to true so that when number is found it is set to false
  for(int i = 0; i < 9; i++)
    board[i] = 1;

  // search surrounding square, collumn, and row
  // getting distances
  int northDist = index / 9;
  int westDist = index % 9;
  int southDist = 8 - (index % 9);
  int eastDist = 8 - (index / 9); 

  // search row 
  //for (int i = row; i < row + )

}

