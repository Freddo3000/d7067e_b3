//
// Created by freddo on 2024-10-10.
//
#include "trie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void node_insert(trie *trie, trie_node *node, char *key, unsigned int layer);

trie *trie_create(unsigned int bucket_max, unsigned int bucket_init, unsigned int bucket_growth_factor) {
    trie t = {
            .root = nullptr,
            .bucket_max = bucket_max,
            .bucket_init = bucket_init,
            .bucket_growth_factor = bucket_growth_factor,
    };
    trie *t_out = malloc(sizeof(trie));
    memcpy(t_out, &t, sizeof(trie));
    return t_out;
}

trie_node *create_trie_node() {
    trie_node *node = malloc(sizeof(trie_node));
    for (int i = 0; i < ALLOWED_CHARS; i++)
        node->children[i].type = UNDEF;

    return node;
}

void burst_bucket(trie *t, bucket *b, trie_node *target, unsigned int depth) {
    for (int i = 0; i < b->items; ++i)
        node_insert(t, target, b->values[i], depth + 1);
    bucket_destroy(b);
}

void trie_insert(trie *trie, char *key) {
    if (trie->root == nullptr)
        trie->root = create_trie_node();

    node_insert(trie, trie->root, key, 0);
}

void elem_insert(trie *trie, trie_node_elem *elem, char *key, unsigned int layer) {
    switch (elem->type) {
        case UNDEF:
            elem->value.bucket = bucket_create(trie->bucket_init);
            elem->type = BUCKET;
        case BUCKET:
            bucket *b = elem->value.bucket;
            if (bucket_full(b)) {
                if (key[layer] != '\0' || bucket_items(b) < trie->bucket_max) {
                    bucket_grow(b, trie->bucket_growth_factor);
                    bucket_insert(b, key);
                    return;
                } else {
                    trie_node *n = create_trie_node();
                    burst_bucket(trie, b, n, layer);
                    elem->value.trie = n;
                    elem->type = TRIE;
                }
            } else {
                bucket_insert(b, key);
                return;
            }
        case TRIE:
            node_insert(trie, elem->value.trie, key, ++layer);
    }
}

void node_insert(trie *trie, trie_node *node, char *key, unsigned int layer) {
    trie_node_elem *e = &node->children[*(key + layer)];
    elem_insert(trie, e, key, layer);
}
