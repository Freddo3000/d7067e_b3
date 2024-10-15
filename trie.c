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

    trie_node_elem e = res.found->children[*(key + res.depth)];
    if (e.type == BUCKET)
        for (int i = 0; i < trie->L; ++i) {
            if (!e.value.bucket[i])
                return false;
            if (!strcmp(e.value.bucket[i] + res.depth, key + res.depth))
                return true;
        }

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

    trie_node_elem e = res.found->children[*(key + res.depth)];
    if (e.type == BUCKET) {
        int i = 0;

        for (;i < trie->L; ++i) {
            if (!e.value.bucket[i])
                return false;
            if (!strcmp(e.value.bucket[i] + res.depth, key + res.depth))
                break;
        }
        free(e.value.bucket[i]);
        for (++i; i < trie->L; ++i) {
            e.value.bucket[i-1] = e.value.bucket[i];
        }
        e.value.bucket[trie->L-1] = nullptr;
        return true;
    }

    return false;
}

void trie_insert(trie *trie, char *key) {
    if (trie->root == nullptr) {
        trie->root = create_trie_node();
    }
    unsigned int layer = 0;
    node_insert(trie, trie->root, key, layer);
}

void create_bucket(trie_node_elem *e, size_t size) {
    //todo: set 0 for malloc
    e->type = BUCKET;
    e->value.bucket = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        e->value.bucket[i] = nullptr;
    }
}

void bucket_insert(trie_node_elem *e, size_t size, char *key) {
    char **b = e->value.bucket;
    for (int i = 0; i < size; i++) {
        if (b[i] == nullptr) {
            char *s = malloc(strlen(key) * sizeof(char));
            strcpy(s, key);
            b[i] = s;
            break;
        }
    }
}

void elem_insert(trie *trie, trie_node_elem *elem, char *key, unsigned int layer) {
    switch (elem->type) {
        case UNDEF:
            create_bucket(elem, trie->L);
        case BUCKET:
            bucket_insert(elem, trie->L, key);
            break;
        case TRIE:
            node_insert(trie, trie->root, key, ++layer);
    }
}

void node_insert(trie *trie, trie_node *node, char *key, unsigned int layer) {
    if (*key == '\0') {
        node->endings++;
    } else {
        trie_node_elem *e = &node->children[*(key + layer)];
        elem_insert(trie, e, key, layer);
    }
}
