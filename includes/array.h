#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "csv.h"

//dynamic array of fields
typedef struct {
  struct fields *array;
  size_t capacity;
  size_t count;
} Array;


void print_csv(Array *a) {
   printf("\nPrinting out All Fields | Debug\n\n");

  for(size_t i=0; i < a->count; i++) {
    printf("-------------\n");
    printf("%s\n", a->array[i].name);
    printf("%d\n", a->array[i].age);
    printf("%f\n", a->array[i].number);
  }     
}

void init(Array *a) {
  a->count = 0;

  if(a->capacity == 0)
    a->capacity = 256;

  a->array = malloc(a->capacity * sizeof(struct fields));
}

void reserve(Array *a, size_t reserved) {
  a->capacity = reserved;
}

void add(Array *a, struct fields element) {
  
  // if size == capacity realloc by 2
  if(a->count == a->capacity) {
    a->capacity *= 2;
    a->array = realloc(a->array, a->capacity * sizeof(struct fields));
  }
  
  a->array[a->count++] = element;
}

// insert at given index
void insert(Array *a, struct fields element, size_t index) {
  assert(index < a->count);
  a->array[index] = element;
}

void delete(Array *a, size_t index) {

  assert(index <= a->count);
 
  // shift the rest to the left from index
  for(index; index < a->count-1; index++) {
    a->array[index] = a->array[index+1];      
  }
  
  // delete last element in array 
  a->count -= 1;
}


struct fields pop_back(Array *a) {  
  struct fields result = a->array[a->count];
  a->count -= 1;
  return result;
}


void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->count = a->capacity = 0;
}


#endif
