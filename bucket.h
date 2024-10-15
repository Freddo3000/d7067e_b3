//
// Created by freddo on 2024-10-15.
//

#ifndef BUCKET_H
#define BUCKET_H
typedef struct {
    char** values;
    unsigned int capacity;
} bucket;

void bucket_init(bucket *b, unsigned int capacity);
bucket* bucket_create(unsigned int capacity);
void bucket_destroy(bucket* b, bool purge);
bool bucket_lookup(bucket* bucket, char* key, unsigned int layer);
bool bucket_insert(bucket* bucket, char* key, unsigned int layer);
bool bucket_delete(bucket* bucket, char* key, unsigned int layer);
#endif //BUCKET_H
