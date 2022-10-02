#ifndef HASHMAP_H
#define HASHMAP_H

#include <string.h>
#define HASHMAP_INIT_SIZE 1024

struct HashMapNode{
  char *key; 
  int value;
  struct HashMapNode *next;
};

typedef struct {
  struct HashMapNode **buckets;
} HashMap;

void HashMapInit(HashMap *map);
int Hash(char *str);
void HashMapPut(HashMap *map, char *key, int value);
int HashMapGet(HashMap *map, char *key);

#endif
