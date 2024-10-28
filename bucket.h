//
// Created by freddo on 2024-10-15.
//

#ifndef BUCKET_H
#define BUCKET_H
typedef struct {
    char **values;
    unsigned int capacity;
    unsigned int items;
} bucket;

void bucket_init(bucket* b, unsigned int capacity);

void bucket_insert(bucket *b, char *key);

void bucket_destroy(bucket *b);

bool bucket_full(bucket *b);

void bucket_grow(bucket *b, unsigned int factor);

unsigned int bucket_items(bucket *b);

#endif //BUCKET_H
