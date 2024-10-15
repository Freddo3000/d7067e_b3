#include <assert.h>
#include <stdio.h>
#include "trie.h"
#include "trie_export.h"
#include "sortstring.h"

int main(void) {
    trie* t = trie_create(8);
    trie_insert(t, "hello");
    trie_insert(t, "world");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "booga");

    bool res = false;

    // Test lookups
    res = trie_lookup(t, "hello");
    assert(res==true);
    res = trie_lookup(t, "ooga");
    assert(res==true);
    res = trie_lookup(t, "bruh");
    assert(res==false);

    // Test deletion
    res = trie_delete(t, "world");
    assert(res==true);
    res = trie_lookup(t, "world");
    assert(res==false);
    res = trie_delete(t, "bruh");
    assert(res==false);
    res = trie_delete(t, "ooga");
    assert(res==true);
    res = trie_lookup(t, "ooga");
    assert(res==true);
    res = trie_delete(t, "ooga");
    assert(res==true);
    res = trie_lookup(t, "ooga");
    assert(res==false);
    res = trie_delete(t, "ooga");
    assert(res==false);

    FILE* f = fopen("trie.dot", "w");
    export_trie(t, f);

    unsigned char *l[] = {"bob1", "bob2", "bob1", "bobo"};  // This is an array of char*

    // Optionally, you can explicitly declare a char** and point it to the array of strings
    unsigned char **ptr = l;

    // Print the values to verify
    for (int i = 0; i < 4; i++) {
        printf("%s\n", ptr[i]);
    }
    mkqsort(l, 4, 0);
    // Print the values to verify after sorting
    for (int i = 0; i < 4; i++) {
        printf("%s\n", ptr[i]);
    }
    // bsearch(); ?????
    return 0;
}

