//
// Created by freddo on 2024-10-10.
//
#include "trie.h"

#include <stdlib.h>
#include <string.h>

void node_insert(trie *trie, trie_node *node, char *key);

trie *trie_create(unsigned int L) {
    trie t = {
        .L = L,
        .root = nullptr,
    };
    trie *trie = malloc(sizeof(trie));
    memcpy(trie, &t, sizeof(trie));
    return trie;
}

trie_node *create_trie_node() {
    trie_node *node = malloc(sizeof(trie_node));
    node->endings = 0;
    for (int i = 0; i < ALLOWED_CHARS; i++) {
        node->children[i].type = UNDEF;
    }

    return node;
}

void trie_insert(trie *trie, char *key) {
    if (trie->root == nullptr) {
        trie->root = create_trie_node();
    }
    node_insert(trie, trie->root, key);
}

void create_bucket(trie_node_elem *e, size_t size) {
    //todo: set 0 for malloc
    e->type = BUCKET;
    e->value.bucket = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        e->value.bucket[i] = nullptr;
    }
}

void bucket_insert(trie_node_elem *e, size_t size, char* key) {
    char **b = e->value.bucket;
    for (int i = 0; i < size; i++) {
        if (b[i] == nullptr) {
            char* s = malloc(strlen(key)*sizeof(char));
            strcpy(s, key);
            b[i] = s;
            break;
        }
    }
}

void elem_insert(trie *trie, trie_node_elem *elem, char *key) {
    switch (elem->type) {
        case UNDEF:
            create_bucket(elem, trie->L);
        case BUCKET:
            bucket_insert(elem, trie->L, key + 1);
            break;
        case TRIE:
            node_insert(trie, trie->root, key + 1);
    }
}

void node_insert(trie *trie, trie_node *node, char *key) {
    if (*key == '\0') {
        node->endings++;
    } else {
        trie_node_elem *e = &node->children[*key];
        elem_insert(trie, e, key);
    }
}
