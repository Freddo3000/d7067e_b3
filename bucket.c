//
// Created by freddo on 2024-10-15.
//

#include "bucket.h"

#include <assert.h>
#include <stdlib.h>

void bucket_init(bucket* b, unsigned int capacity) {
    b->capacity = capacity;
    b->items = 0;
    b->values = malloc(sizeof(char*) * capacity);
}

unsigned int bucket_items(bucket* b) {
    return b->items;
}

void bucket_destroy(bucket* b) {
    free(b->values);
}

void bucket_insert(bucket* b, char* key) {
    assert(b->items < b->capacity);
    b->values[b->items] = key;
    b->items++;
}

bool bucket_full(bucket* b) {
    return (b->items >= b->capacity);
}

void bucket_grow(bucket* b, unsigned int factor) {
    unsigned int new_cap = b->capacity << factor;
    b->values = realloc(b->values, new_cap * sizeof(char*));
    b->capacity = new_cap;
}