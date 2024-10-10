//
// Created by freddo on 2024-10-10.
//
#pragma once
#ifndef TRIE_H
#define TRIE_H

typedef struct trie_node_elem trie_node_elem;
typedef struct trie_node trie_node;

typedef enum node_type {
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
    trie_node_elem* children;
} trie_node;

typedef struct trie {
    const unsigned int L;
    trie_node root;
} trie;
#endif //TRIE_H
