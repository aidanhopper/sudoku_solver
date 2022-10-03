#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "hashmap.h"
#include "sudoku.h"
#include <string.h>
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

char ToChar(int num) {
  return num + 49;
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

int GenerateLEI(char *board, int **possibleNumbers) {
  EntropyArr *LEI = FindLowestEntropy(possibleNumbers);
  if (LEI->size == 0)
    return -1;

  int val = LEI->values[Rand(LEI->size)];
  free(LEI);
  return val;
}

void SetBoard(char *board, char *newboard) {
  for (int i = 0; i < 81; i++)
    board[i] = newboard[i];
}

int Different(char *str1, char *str2) {
  for (int i = 0; i < 81; i++)
    if (str1[i] != str2[i])
      return 1;
  return 0;
}

// Need to add a way to track used values at an index on stack
void GenerateMove(char *board, int **possibleNumbers, Stack *stack) {
  // generates possible numbers for every position on the board
  for (int i = 0; i < 81; i++)
   GetPossibleNumbers(board, i, possibleNumbers[i]);

  EntropyArr *LEI = FindLowestEntropy(possibleNumbers);

  // check if head of stack is the same or new state
  // char *topstr = StackTopStr(stack);
  struct StackNode *node = StackTop(stack);
  int different = Different(board, node->string);

  // Iterate through possible indexes
  for (int i = 0; i < LEI->size; i++) {
    // get index
    int index = LEI->values[i];
    int arr[9];
    GetPossibleNumbers(board, index, arr);

    // Iterate through every character for each index
    for (int j = 0; j < 9; j++) {
      if (arr[j] == 1) {
	// get character
	char character = ToChar(j);

	board[index] = character;
	if (!StackIsEmpty(stack)) {
	  printf("id:%d:index:%d:[ ", node->id, index);
	  for (int k = 0; k < 9; k++)
	    if (node->usedNums[index][k] == 1)printf("%d:%d ", k+1, node->usedNums[index][k]);
	  printf("] char:%c\n", character);
	}

	if (different) {
	  board[index] = character;
	  struct StackNode *newnode = CreateStackNode(stack, board);
	  newnode->usedNums[index][j] = 1;
	  printf("node id: %d\n", newnode->id);
	  StackPush(stack, newnode);
	  return;
	}

	if (!different && node->usedNums[index][j] == 0) {
	  board[index] = character;
	  //struct StackNode *newnode = CreateStackNode(stack, board);
	  node->usedNums[index][j] = 1;
	  //StackPush(stack, newnode);
	  return;
	}

      }
    }
  }

  // go back
  // pop node off stack and delete it because it has a contradiction
  struct StackNode *delnode = StackPop(stack);
  //for (int i = 0; i < 81; i++)
    //  free(delnode->usedNums[i]);
  //free(delnode->usedNums);
  //free(delnode->string);
  //free(delnode);

  // set board
  struct StackNode *nnode = StackTop(stack);
  SetBoard(board, nnode->string);
  
}

void GenRandMove(char *board, int **possibleNumbers, Stack *stack) {
  for (int i = 0; i < 81; i++)
   GetPossibleNumbers(board, i, possibleNumbers[i]);

  int LEI = GenerateLEI(board, possibleNumbers);
  if (LEI == -1) {
    SetBoard(board, StackTop(stack)->string);
    return;
  }

  char character = GenerateNumber(possibleNumbers[LEI]);
  board[LEI] = character;
}
