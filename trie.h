//
// Created by freddo on 2024-10-10.
//
#pragma once
#ifndef TRIE_H
#define TRIE_H
#define ALLOWED_CHARS 128
#include <stdio.h>

typedef struct trie_node_elem trie_node_elem;
typedef struct trie_node trie_node;

typedef enum node_type {
    UNDEF,
    TRIE,
    BUCKET
} node_type;

typedef union trie_node_elem_value {
    char**  bucket;
    trie_node* trie;
} trie_node_elem_value;

typedef struct trie_node_elem {
    node_type type;
    trie_node_elem_value value;
} trie_node_elem;

typedef struct trie_node {
    trie_node_elem children[ALLOWED_CHARS];
    unsigned int endings;
} trie_node;

typedef struct trie {
    const unsigned int L;
    trie_node *root;
} trie;

trie* trie_create(unsigned int L);
void trie_destruct(trie* trie);
void trie_insert(trie* trie, char* key);
bool trie_delete(trie* trie, char* key);
unsigned int trie_lookup(trie* trie, char* key);
void export_trie(trie* trie, FILE* file);
#endif //TRIE_H
