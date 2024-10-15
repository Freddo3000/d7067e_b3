#include <assert.h>
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

    return 0;
}

