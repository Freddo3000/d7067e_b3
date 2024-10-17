//
// Created by freddo on 2024-10-15.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../trie.h"
#include "../trie_export.h"
#include "../burstsort.h"
#include "../allsorts/sortstring.h"

int main(int argc, char *argv[])
{
    int i,j,k;
    int length = 0;
    int noOfStrings = 1048576;
    int value;
    char str[21];
    char** strings = malloc(noOfStrings * sizeof(char**));
    char** strings_cpy = malloc(noOfStrings * sizeof(char**));

    //noOfStrings = atoi(argv[1]);

    srandom(73802);

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
        strings[i] = malloc(length*sizeof(char) + 1);
        strcpy(strings[i], str);
    }
    memcpy(strings_cpy, strings, noOfStrings * sizeof(char*));


    clock_t begin = clock();
    arssort((unsigned char **) strings_cpy, noOfStrings);
    clock_t end = clock();
    printf("mkqsort: Start: %ld, End: %ld, Time taken: %ld\n",
           begin,
           end,
           end - begin
    );

    begin = clock();
    burstsort(strings_cpy, noOfStrings, 64, (void (*)(char **, int, int)) arssort);
    end = clock();
    printf("mkqsort: Start: %ld, End: %ld, Time taken: %ld\n",
           begin,
           end,
           end - begin
    );

    memcpy(strings_cpy, strings, noOfStrings * sizeof(char*));

    return 0;
}
