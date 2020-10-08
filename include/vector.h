#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    void** data;
    int size; // size right now
    int max_size;
} Vector;

Vector* make_vector();
void vector_pushback(Vector* v, void* val);
void vector_popback(Vector* v);
void vector_set(Vector* v, int i, void* val);
void* vector_get(Vector* v, int i);
void vector_free(Vector* v);

#endif