//
// Created by freddo on 2024-10-15.
//

#ifndef BUCKET_H
#define BUCKET_H
typedef struct {
    char** values;
    unsigned int size;
} bucket;

bucket new_bucket();
void free_bucket(bucket* b);
bool lookup(bucket bucket, char* key);
bool insert(bucket bucket, char* key);
bool delete(bucket bucket, char* key);
#endif //BUCKET_H
