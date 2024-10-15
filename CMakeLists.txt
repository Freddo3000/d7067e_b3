cmake_minimum_required(VERSION 3.29)
project(d7067e C)

set(CMAKE_C_STANDARD 23)

add_executable(d7067e main.c
        trie.h
        trie.c
        trie_export.c
        trie_export.h
        bucket.c
        bucket.h)

add_executable(d7067e_randomstrings
        trie.h
        trie.c
        trie_export.c
        trie_export.h
        bucket.c
        bucket.h
        test/randomstrings.c
)
