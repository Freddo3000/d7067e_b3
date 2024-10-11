//
// Created by freddo on 2024-10-11.
//

#include "trie_export.h"
void export_bucket(trie *trie, char **bucket, FILE *file) {
    fprintf(file, "bucket%p [label=\"{", bucket);
    bool is_first = true;
    for (int i = 0; i < trie->L; ++i) {
        if (is_first)
            is_first = false;
        else
            fprintf(file, "|");
        if (bucket[i])
            fputs(bucket[i], file);
    }
    fprintf(file, "}\"]\n");
}

void export_node(trie *trie, trie_node *node, FILE *file) {
    fprintf(file, "node%p [label=\"", node);

    bool is_first = true;
    for (int i = 0; i < ALLOWED_CHARS; ++i) {
        if (node->children[i].type == UNDEF)
            continue;
        if (is_first)
            is_first = false;
        else
            fprintf(file, "|");
        fprintf(file, "<%c> %c", i, i);
    }
    fprintf(file, "\"];\n");
    for (int i = 0; i < ALLOWED_CHARS; ++i) {
        if (node->children[i].type == UNDEF)
            continue;
        if (node->children[i].type == TRIE) {
            fprintf(file, "node%p:%c -> node%p;\n", node, i, node->children[i].value.trie);
            export_node(trie, node->children[i].value.trie, file);
        } else {
            fprintf(file, "node%p:%c -> bucket%p;\n", node, i, node->children[i].value.trie);
            export_bucket(trie, node->children[i].value.bucket, file);
        };
    }
}

void export_trie(trie *trie, FILE *file) {
    fprintf(file, "digraph trie {\nnode [shape=record];\n");
    if (trie->root) {
        export_node(trie, trie->root, file);
    }
    fprintf(file, "}");
}
