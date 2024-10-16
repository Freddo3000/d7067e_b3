#include <assert.h>
#include <stdio.h>
#include "trie.h"
#include "trie_export.h"
#include "allsorts/mkqsort.c"

int main(void) {
    trie* t = trie_create(100);
    /*
    trie_insert(t, "hello");
    trie_insert(t, "hell");
    trie_insert(t, "world");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "oops");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
    trie_insert(t, "ooga");
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
    assert(res==true);
    res = trie_delete(t, "ooga");
    assert(res==true);

    */
    char* l[] = {
        "wane",
        "way",
        "west",
        "bat",
        "barn",
        "bark",
        "by",
        "by",
        "by",
        "byte",
        "bytes",
    };
    for (int i = 0; i < 11; ++i) {
        trie_insert(t, l[i]);
    }

    FILE* f = fopen("trie.dot", "w");
    export_trie(t, f);

    mkqsort((unsigned char**) l, 11, 0);

    return 0;
}

