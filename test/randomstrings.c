//
// Created by freddo on 2024-10-15.
//


#include <stdio.h>
#include <stdlib.h>
#include "../trie.h"
#include "../trie_export.h"

int main(int argc, char *argv[])
{
    int i,j,k;
    int length = 0;
    int noOfStrings = 10000;
    int value;
    char str[21];

    //noOfStrings = atoi(argv[1]);

    srandom(73802);
    trie* t = trie_create(8);

    for (i=0; i < noOfStrings; i++)
    {
        length = rand() % 20;
        for (j = 0; j < length; j++)
        {
            value = rand() % 127;
            if (value > 64 && value < 91)
                str[j] = value;
            else
                j--;
        }
        str[length] = '\0';
        trie_insert(t, str);
    }

    FILE* f = fopen("bruh.dot", "w");
    export_trie(t, f);
    return 0;
}
