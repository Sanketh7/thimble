#include "vector.h"

Vector* make_vector() {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->max_size = 0;
    v->size = 0;
    return v;
}

static void vector_resize(Vector* v, int new_max_size) {
    void** new_data = realloc(v->data, sizeof(void*)*new_max_size);
    if (new_data) {
        v->data = new_data;
        v->max_size = new_max_size;
    } else {
        // realloc error
        fprintf(stderr, "realloc() error while resizing vector to size %d\n.", new_max_size);
        exit(1);
    }
}

void vector_pushback(Vector* v, void* val) {
    if (v->size == v->max_size) {
        vector_resize(v, v->max_size*2);    
    }
    v->data[v->size++] = val;
}

void vector_popback(Vector* v) {
    if (v->size == 0) {
        fprintf(stderr, "Cannot pop element from empty vector.");
        exit(1);
    }
    v->data[--v->size] = NULL;
    if (v->size > 0 && v->size == v->max_size/4) {
        vector_resize(v, v->max_size/2);
    }
}

void vector_set(Vector* v, int i, void* val) {
    if (i < 0 || i >= v->size) {
        fprintf(stderr, "Index %d out of bounds.\n", i);
        exit(1);
    }
    v->data[i] = val;
}

void* vector_get(Vector* v, int i) {
    if (i < 0 || i >= v->size) {
        fprintf(stderr, "Index %d out of bounds.\n", i);
        exit(1);
    }
    return v->data[i];
}

void vector_free(Vector* v) {
    free(v->data);
}