//
// Created by freddo on 2024-10-10.
//
#include "trie.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void node_insert(trie *trie, trie_node *node, char *key, unsigned int layer);

trie *trie_create(unsigned int L) {
    trie t = {
        .L = L,
        .root = nullptr,
    };
    trie *trie = malloc(sizeof(trie));
    memcpy(trie, &t, sizeof(trie));
    return trie;
}

struct cls_node {
    trie_node *found;
    unsigned int depth;
};

struct cls_node _closest_node(char *key, trie_node *current, unsigned int depth) {
    trie_node_elem *child = &current->children[*(key + depth)];
    if (child->type == TRIE) {
        return _closest_node(key, child->value.trie, ++depth);
    }
    struct cls_node found = {
        .found = current,
        .depth = depth,
    };
    return found;
}

struct cls_node closest_node(trie *trie, char *key) {
    if (trie->root == nullptr) {
        struct cls_node found = {
            .found = nullptr,
            .depth = -1
            };
        return found;
    }
    unsigned int depth = 0;
    return _closest_node(key, trie->root, depth);
}

trie_node *create_trie_node() {
    trie_node *node = malloc(sizeof(trie_node));
    node->endings = 0;
    for (int i = 0; i < ALLOWED_CHARS; i++) {
        node->children[i].type = UNDEF;
    }

    return node;
}

bool trie_lookup(trie *trie, char *key) {
    struct cls_node res = closest_node(trie, key);
    assert(res.found != nullptr);

    if (res.depth == strlen(key))
        return res.found->endings > 0;

    trie_node_elem* e = &res.found->children[*(key + res.depth)];
    if (e->type == BUCKET)
        return bucket_lookup(&e->value.bucket, key, res.depth);

    return false;
}

bool trie_delete(trie *trie, char *key) {
    struct cls_node res = closest_node(trie, key);
    assert(res.found != nullptr);

    if (res.depth == strlen(key)) {
        if (res.found->endings)
            return --res.found->endings > 0;
        return false;
    }

    trie_node_elem* e = &res.found->children[*(key + res.depth)];
    if (e->type == BUCKET) {
        return bucket_delete(&e->value.bucket, key, res.depth);
    }

    return false;
}

void burst_bucket(trie* t, bucket* b, trie_node* target, unsigned int depth) {
    for (int i = 0; i < b->capacity; ++i) {
        if (b->values[i] == nullptr)
            break;
        node_insert(t, target, b->values[i], depth+1);
    }
    free(b->values);
}

void trie_insert(trie *trie, char *key, bool clone) {
    if (trie->root == nullptr)
        trie->root = create_trie_node();

    char* str;
    if (clone) {
        str = malloc(strlen(key) * sizeof(char) + 1);
        strcpy(str, key);
    } else str = key;
    node_insert(trie, trie->root, str, 0);
}

void elem_insert(trie *trie, trie_node_elem *elem, char *key, unsigned int layer) {
    switch (elem->type) {
        case UNDEF:
            bucket_init(&elem->value.bucket, trie->L);
            elem->type = BUCKET;
        case BUCKET:
            if (bucket_full(&elem->value.bucket)) {
                trie_node* n = create_trie_node();
                burst_bucket(trie, &elem->value.bucket, n, layer);
                elem->value.trie = n;
                elem->type = TRIE;
            } else {
                bucket_insert(&elem->value.bucket, key, layer);
                break;
            }
        case TRIE:
            node_insert(trie, elem->value.trie, key, ++layer);
    }
}

void node_insert(trie *trie, trie_node *node, char *key, unsigned int layer) {
    if (*(key+layer) == '\0') {
        node->endings++;
        //free(key); // todo: fails when not cloning values to heap...
    } else {
        trie_node_elem *e = &node->children[*(key + layer)];
        elem_insert(trie, e, key, layer);
    }
}
