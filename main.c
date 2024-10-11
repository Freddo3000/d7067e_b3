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

    FILE* f = fopen("trie.dot", "w");
    export_trie(t, f);

    return 0;
}

