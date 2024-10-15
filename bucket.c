//
// Created by freddo on 2024-10-15.
//

#include "bucket.h"

#include <stdlib.h>
#include <string.h>

void bucket_init(bucket* b, unsigned int capacity) {
    b->capacity = capacity;
    b->values = malloc(sizeof(char*) * capacity);
    for (int i = 0; i < capacity; i++)
        b->values[i] = nullptr;
}
bucket* bucket_create(unsigned int capacity) {
    bucket* b = malloc(sizeof(bucket));
    b->capacity = capacity;
    b->values = malloc(sizeof(char*) * capacity);
    for (int i = 0; i < capacity; i++)
        b->values[i] = nullptr;

    return b;
}

void bucket_destroy(bucket* b, bool purge) {
    if (purge)
        for (int i = 0; i < b->capacity; i++)
            free(b->values[i]);
    free(b->values);
    free(b);
}

bool bucket_lookup(bucket* b, char* key, unsigned int layer) {
    for (int i = 0; i < b->capacity; i++) {
        if (b->values[i] == nullptr)
            return false;
        if (strcmp(b->values[i], key) == 0) {
            return true;
        }
    }
    return false;
}

bool bucket_insert(bucket* b, char* key, unsigned int layer) {
    for (int i = 0; i < b->capacity; i++)
        if (b->values[i] == nullptr) {
            b->values[i] = key;
            return true;
        }
    return false;
}

bool bucket_delete(bucket* b, char* key, unsigned int layer) {
    int i = 0;
    bool found = false;
    for (; i < b->capacity; i++) {
        if (b->values[i] == nullptr)
            return false;
        if (strcmp(b->values[i], key) == 0) {
            free(b->values[i]);
            b->values[i] = nullptr;
            found = true;
        }
    }
    for (++i; i < b->capacity; i++) {
        b->values[i-1] = b->values[i];
    }
    if (found)
        b->values[b->capacity-1] = nullptr;
    return found;

}