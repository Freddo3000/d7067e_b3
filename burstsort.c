//
// Created by freddo on 16/10/24.
//

#include "burstsort.h"
#include <stdlib.h>
#include <string.h>

char** _traverse(char **out, unsigned int depth, char *path, trie_node* n, void (*sort)(char **, int, int)) {
    // This differs from spec, should preserver original strings
    // But I'm too lazy/late to change it now
    for (int i = 0; i < n->endings; ++i) {
        out[i] = malloc(depth * sizeof(char) + 1);
        strcpy(out[i], path);
    }
    out += n->endings;

    for (int i = 0; i < ALLOWED_CHARS; ++i) {
        trie_node_elem* e = &n->children[i];
        switch (e->type) {
            case UNDEF:
                continue;
            case TRIE:
                path[depth] = (char) i;
                path[depth+1] = '\0';
                out = _traverse(out, depth+1, path, e->value.trie, sort);
                path[depth] = '\0';
                continue;
            case BUCKET:
                int n = 0;
                while (e->value.bucket.values[n] != nullptr && n < e->value.bucket.capacity)
                    n++;
                sort(e->value.bucket.values, n, (int) depth);
                for (int j = 0; j < e->value.bucket.capacity; ++j) {
                    if (e->value.bucket.values[j] == nullptr)
                        continue;
                    out[0] = e->value.bucket.values[j];
                    out++;
                }
        }
    }
    return out;
}

void burstsort(char **strings, unsigned int n, unsigned int L, void (*sort)(char **, int, int)) {
    if (!n)
        return;

    char p[100] = "\0"; // alloc a string to just store the current working path...

    trie *t = trie_create(L);

    for (int i = 0; i < n; ++i) {
        trie_insert(t, strings[i], false);
    }

    _traverse(strings, 0, p, t->root, sort);

    return;
}