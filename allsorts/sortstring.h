/*
   Global declarations for a testbed for sorting algorithms
   operating on arrays of character strings.

   The code presented in this file has been tested with care but is
   not guaranteed for any purpose. The writer does not offer any
   warranties nor does he accept any liabilities with respect to
   the code.

   Ranjan Sinha, 28th July 2003.

   School of Computer Science and Information Technology,
   RMIT University, Melbourne, Australia
   rsinha@cs.rmit.edu.au
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define CHARS 256
#define ALPHABET 256
#define BITS 8
#define TRUE 1
#define FALSE 0
#define MAXBLOCKS 100
#define INSERTBREAK 20 /* buckets will use insertsort if items below   */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define EXIT  exit(EXIT_FAILURE)
#define NULLTERM '\0'
#define ERR_PRINT_OUT_OF_MEMORY printf("Error: Out of memory \n")

typedef int boolean;
typedef int character;
typedef unsigned char char_t;
typedef char_t *string;

typedef struct listrec *list;
struct listrec {
   string str;
   list next;
   int length;
};

typedef struct {
   void *block[MAXBLOCKS];
   int allocnr;
   int nr;
   int blocksize;
   void *current, *first, *last;
} memory;

void initmem(memory *m, int elemsize, int blocksize);
void *allocmem(memory *m, int elemsize);
void *deallocmem(memory *m, int elemsize);
void resetmem(memory *m);
void freemem(memory *m);

void BenStr(string a[], int n);
void McIlroyCC(string a[], int n);
void multikey2(string a[], int n);
void arssort(string a[], int n);
void frssort(string strings[], int scnt);
void frssort1(string strings[], int scnt);
void MSDsort(string strings[], int scnt);
void burstsortL(string a[], int n);
void burstsortA(string a[], int n);

list ListInsertsort(list head, list *tail , int length);
void mkqsort(unsigned char **a, int n, int depth);
void inssort(unsigned char **a, int n, int d);
int scmp( unsigned char *s1, unsigned char *s2 );

void clockon();
void clockoff();
double gettime();
