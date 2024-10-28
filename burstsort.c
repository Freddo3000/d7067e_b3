//
// Created by freddo on 16/10/24.
//

#include "burstsort.h"
#include <stdlib.h>
#include "trie_export.h"

char** _traverse(char **out, unsigned int depth, char *path, trie_node* n, void (*sort)(char **, int, int)) {
    if (n->children[0].type == BUCKET) {
        bucket* b = &n->children[0].value.bucket;
        for (int i = 0; i < b->items; ++i) {
            out[0] = b->values[i];
            out++;
        }
    }
    for (int i = 1; i < ALLOWED_CHARS; ++i) {
        trie_node_elem* e = &n->children[i];
        switch (e->type) {
            case UNDEF:
                continue;
            case TRIE:
                path[depth] = (char) i;
                path[depth+1] = '\0';
                out = _traverse(out, depth+1, path, e->value.trie, sort);
                //free(n);
                path[depth] = '\0';
                continue;
            case BUCKET:
                bucket* b = &e->value.bucket;
                sort(b->values, b->items, (int) depth);
                for (int j = 0; j < b->items; ++j) {
                    out[0] = e->value.bucket.values[j];
                    out++;
                }
                //bucket_destroy(b);
        }
    }
    return out;
}

void burstsort(char **strings, unsigned int n, unsigned int L, void (*sort)(char **, int, int)) {
    if (!n)
        return;

    char p[100] = "\0"; // alloc a string to just store the current working path...

    trie *t = trie_create(8191, 16,4);

    for (int i = 0; i < n; ++i)
        trie_insert(t, strings[i]);

    //FILE* f = fopen("trie.dot", "w");
    //export_trie(t, f);

    _traverse(strings, 0, p, t->root, sort);
    free(t);
}