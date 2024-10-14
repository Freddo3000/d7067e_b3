#include <stdio.h>
#include "trie.h"
#include "trie_export.h"

int main(void) {
    trie* t = trie_create(8);
    trie_insert(t, "hello");
    trie_insert(t, "world");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "booga");
    printf("Result: %s\n", trie_lookup(t, "ooga") ? "true" : "false");
    printf("Result: %s\n", trie_lookup(t, "oooga") ? "true" : "false");
    printf("Result: %s\n", trie_lookup(t, "wooga") ? "true" : "false");

    FILE* f = fopen("trie.dot", "w");
    export_trie(t, f);

    return 0;
}

