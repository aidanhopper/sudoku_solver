#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "hashmap.h"
#include "sudoku.h"
#include <sys/random.h>

void PrintBoard(char *board) {
  for (int i = 0; i < 81; i++) {
    if (i == 27) printf("\n-----------------------------");
    if (i == 54) printf("\n-----------------------------");
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
  for (int i = col; i < 73 + col; i = i + 9)
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

void ClearEntropyArr(EntropyArr *arr) {
  arr->size = 0;
  arr->values[arr->size] = -1;
}

void AppendEntropyArr(EntropyArr *arr, int value) {
  arr->values[arr->size++] = value;
}

int GetEntropy(int *possibleNumbers) {
  int entropy = 0;
  for (int i = 0; i < 9; i++)
    if (possibleNumbers[i] == 1)
      entropy++;
  return entropy;
}

EntropyArr *FindLowestEntropy(int **possibleNumbers) {
  // need to return array of lowest entropy indexes that arent 0
  // if there arent any then return null

  EntropyArr *LEI = malloc(sizeof(EntropyArr *) * 82);
  ClearEntropyArr(LEI);

  int LEV = 9;
  for (int i = 0; i < 81; i++) {
    int entropy = GetEntropy(possibleNumbers[i]);
    if (entropy < LEV && entropy != 0) {
      LEV = entropy;
      ClearEntropyArr(LEI);
    }
    if (entropy == LEV)
      AppendEntropyArr(LEI, i);
  }

  return LEI;

}

void PrintAllPossibleNumbers(int **possibleNumbers) {
  for (int i = 0; i < 81; i++)
    if (possibleNumbers[i][0] != -1) {
      printf("%d ", i);
      PrintPossibleNumbers(possibleNumbers[i]);
    }
}

int Rand(int range) {
  unsigned int tmp;
  getrandom(&tmp, sizeof(unsigned int), GRND_NONBLOCK) == -1 ? perror("getrandom") : "";
  return (int) (tmp % range);
}

char GenerateNumber(int *possibleNumbers) {
  char nums[9];
  int nIndex = 0;
  for (int i = 0; i < 9; i++)
    if (possibleNumbers[i] == 1)
      nums[nIndex++] = i + 49;     

  if (nIndex == 0)
    return -1;
  
  return nums[Rand(nIndex)];
}

int Done(char *board) {
  for (int i = 0; i < 81; i++)
    if (board[i] == ' ')
      return 0;
  return 1;  
}

int GenerateLEI(char *board, int **possibleNumbers, HashMap *map) {
  EntropyArr *LEI = FindLowestEntropy(possibleNumbers);
  if (LEI->size == 0)
    return -1;

  int val = LEI->values[Rand(LEI->size)];
  for (int i = 0; i < LEI->size; i++) {
    // check if LEI + generate nums are blacklisted

    // get index 
    int index = LEI->values[i];

    // get possible numbers
    int *pNums = possibleNumbers[index];

    // return first one that is not blacklisted
    

  }

  free(LEI);
  return val;
}

void SetBoard(char *board, char *newboard) {
  for (int i = 0; i < 81; i++)
    board[i] = newboard[i];
  free(newboard);
}

void GenerateMove(char *board, int **possibleNumbers, Stack *stack, HashMap *map, int num) {
  // generates possible numbers for every position on the board
  for (int i = 0; i < 81; i++)
   GetPossibleNumbers(board, i, possibleNumbers[i]);


  // finds the lowest entropy index
  int LEI = GenerateLEI(board, possibleNumbers, map);

  // check if theres a contracdiction
  // if so pop off the stack and go back a step
  if (LEI == -1) {
    char *newboard = StackPop(stack);
    // list to map since there was a contracdiction
    HashMapPut(map, board, 1);
    return;
  }


  StackPush(stack, board);
  char newNum = GenerateNumber(possibleNumbers[LEI]);
  board[LEI] = newNum;

  // check if listed on map 
}
