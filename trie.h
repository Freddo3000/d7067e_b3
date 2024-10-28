//
// Created by freddo on 2024-10-10.
//
#pragma once
#ifndef TRIE_H
#define TRIE_H
#define ALLOWED_CHARS 128
#include <stdio.h>
#include "bucket.h"

typedef struct trie_node_elem trie_node_elem;
typedef struct trie_node trie_node;

typedef enum node_type {
    UNDEF,
    TRIE,
    BUCKET
} node_type;

typedef union trie_node_elem_value {
    bucket  bucket;
    trie_node* trie;
} trie_node_elem_value;

typedef struct trie_node_elem {
    node_type type;
    trie_node_elem_value value;
} trie_node_elem;

typedef struct trie_node {
    trie_node_elem children[ALLOWED_CHARS];
} trie_node;

typedef struct trie {
    const unsigned int bucket_init;
    const unsigned int bucket_max;
    const unsigned int bucket_growth_factor;
    trie_node *root;
} trie;

trie* trie_create(unsigned int bucket_max, unsigned int bucket_init, unsigned int bucket_growth_factor);
void trie_insert(trie* trie, char* key);
#endif //TRIE_H
