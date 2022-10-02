#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void HashMapInit(HashMap *map) {
  // allocating memory for hashmap
  map->buckets = malloc(sizeof(struct HashMapNode*) * HASHMAP_INIT_SIZE);
  for (int i = 0; i < HASHMAP_INIT_SIZE; i++)
    map->buckets[i] = malloc(sizeof(struct HashMapNode));

  // initializing each bucket
  for (int i = 0; i < HASHMAP_INIT_SIZE; i++) {
    map->buckets[i]->key = "";
    map->buckets[i]->value = 0;
    map->buckets[i]->next = NULL;
  }
}

int Hash(char *str) {
  long int sum = 0;
  for (int i = 0; i < 81; i++)
    sum += str[i];
  sum*=sum;
  return sum % HASHMAP_INIT_SIZE; 
}

int CompareKeys(char *key1, char *key2) {
  for (int i = 0; i < 81; i++)
    if (key1[i] != key2[i])
      return 0;
  return 1;
}


void HashMapPut(HashMap *map, char *k, int value) {
  char *key = malloc(sizeof(char*) * 82);
  strcpy(key, k);
  int index = Hash(k);
  if (map->buckets[index]->key[0] == '\0') {
    map->buckets[index]->key = key;
    map->buckets[index]->value = value;
    map->buckets[index]->next = NULL;
    return;
  }

  if (CompareKeys(key, map->buckets[index]->key)) {
    map->buckets[index]->value = value;
    return;
  }


  // find last node in bucket
  struct HashMapNode *tmp = map->buckets[index];
  while(tmp->next != NULL) {
    tmp = tmp->next;
    if (CompareKeys(tmp->key, key)) {
      map->buckets[index]->value = value;
      return;
    }
  }

  // allocate memory for next node
  struct HashMapNode *next = malloc(sizeof(struct HashMapNode*));
  tmp->next = next;
  
  // set key value pair of new node
  tmp->next->key = key;
  tmp->next->value = value;
  tmp->next->next = NULL;
}

int HashMapGet(HashMap *map, char *key) {
  int index = Hash(key);
  // if bucket has no nodes then insert node and return false
  if (map->buckets[index]->key[0] == '\0') {
    HashMapPut(map, key, 0);
    return 0;
  }
  // if bucket has nodes then search for it and return value of match
  struct HashMapNode *tmp = map->buckets[index];
  if (CompareKeys(tmp->key, key))
    return map->buckets[index]->value;
  while(tmp->next != NULL) {
    tmp = tmp->next;
    if (CompareKeys(tmp->key, key)) {
      return tmp->value;
    }
  }

  // if not match then insert key and return false
  HashMapPut(map, key, 0);
  return 0;

}
