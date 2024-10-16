/*
   Test bed for array-based string sorting algorithms.

   The program reads a file, whose name is given as a command line
   argument, and creates an array where each element consists of
   one line from the file. The array is sorted a number of times
   using different algorithms.

   To be able to measure the time also for very short files,
   one can give an optional command line parameter n that indicates
   that the file should be sorted n times.

   The code presented in this file has been tested with care but is
   not guaranteed for any purpose. The writer does not offer any
   warranties nor does he accept any liabilities with respect to
   the code.

   Ranjan Sinha 28th July 2003

   School of Computer Science and Information Technology,
   RMIT University, Melbourne, Australia
   rsinha@cs.rmit.edu.au
 
   Some parts are adapted from Nilsson's work with minor modifications

   Stefan Nilsson, 8 jan 1997.

   Laboratory of Information Processing Science
   Helsinki University of Technology
   Stefan.Nilsson@hut.fi
*/

#include "sortstring.h"
#include <math.h>

/*
   Read from stdin and create an array with one element
   per line. Return the number of lines.
*/
static int readlines(char *file_name, string lines[], int maxlines)
{
   int nlines = 0;
   size_t size;
   FILE *in_file;
   string basep, cur, next;

   if (!(in_file = fopen(file_name, "rb"))) {
      perror(file_name);
      exit(-1);
   }
   fseek(in_file, 0, SEEK_END);
   size = ftell(in_file);
   fseek(in_file, 0, SEEK_SET);
   if (!(basep = (string) malloc((size+1)*sizeof(char_t)))) return -1;
   basep[size] = '\n';
   if (fread(basep, 1, size, in_file) < size) {
      perror(file_name);
      exit(-1);
   }

   cur = basep;
   while (cur < basep + size) {
      next = cur;
      while ((next < basep + size) && (*next != '\n'))
         next++;
      *next = '\0';
      lines[nlines] = cur;
      cur = next + 1;
      nlines++;
      if (nlines > maxlines) return -1;
   }
   return nlines;  
}

/*
   Write the array to stdout.
*/
void writelines(string t[], int nlines)
{
   int i;

   for (i = 0;  i < nlines; i++)
      printf("%s\n", t[i]);
   fprintf(stderr, "%s%i\n", "Lines: ", nlines);
}

/*
   Run the sorting algorithm "sort" on the strings
   found in the array "backup" ("backup" has "nlines" entries).
   This array is copied repeatedly (as indicated by "repeat")
   into the "lines" array and the sorting algorithm is
   invoked once for each copy. The experiment is repeated "n"
   times and statistics are computed. The string "s" is
   a text string describing the experiment.
 */
void run(void (*sort)(string *, int), int n,
         string backup[], int nlines, int repeat,
         char *s)
{
   int i, j, k;
   double time[100];  /* Repeat the experiment at most 100 times */
   double min, x_sum, x2_sum, aver, stdev;
   string *lines;

   lines = malloc(nlines * repeat * sizeof(string));
   if (lines == NULL) {
      fprintf(stderr, "Out of memory.\n");
      exit(-1);
   }

   printf("%-20s", s);
   printf(": lines: %d", nlines);
   for (i = 0; i < n; ++i) {
      for (j = 0; j < repeat; ++j)
         for (k = 0; k < nlines; ++k)
            lines[j*nlines + k] = backup[k];
      clockon();
      for (j = 0; j < repeat; ++j)
         sort(lines + j*nlines, nlines);
      clockoff();
      time[i] =  1000 * gettime()/repeat;
      /* writelines(lines, nlines); */
   }
   free(lines);

   x_sum = x2_sum = 0;
   min = DBL_MAX;
   for (i = 0; i < n; ++i) {
      x_sum += time[i];
      x2_sum += time[i]*time[i];
      min = time[i] < min ? time[i] : min;
   }

   /* print normalized value */
   printf(" norm: %.6f ", min/(nlines * log10(nlines)) );

   if (n > 0) {
      aver = x_sum / (double) n;
      stdev = sqrt ((x2_sum - n*aver*aver) / (double) (n - 1));
      printf(" min: %.2f", min);
      printf("  aver: %.2f", aver);
      printf("  stdev: %.2f", stdev);
   }
   printf("  (");
   for (i = 0; i < n-1; ++i)
      printf("%.2f,", time[i]);
   printf("%.2f)\n", time[i]);
 
}

static void printUsage(void)
{
    printf("Sorting Strings\n");
    printf("----------------\n");
    printf("Usage: sortstring <algorithm> <dataset> <again> <repeat> \n\n");
    printf("Algorithms: \n\t 1:Quicksort\n\t 2:MultiKey\n\t 3:MBMradix\n\t 4:MSDradix\n\t 5:Adaptive\n\t 6:Forward8\n\t 7:Forward16\n\t 8:BurstsortL\n\t 9:BurstsortA\n\n");
}
/*
int main(int argc, char *argv[])
{
   #define MAXLINES 40000000   // max #lines in input file

   int nlines;
   int repeat; 	// repeats the same routine, useful for small data
   int again; 	
   int algorithm;
   char *dataset; 
   static string backup[MAXLINES];

   if (argc < 2 || argc > 5) 
   {
      printUsage(); 
      return 1;
   }

   // assign arguments to variables
   algorithm=atoi(argv[1]);
   dataset = (char *) malloc(100 * sizeof(char)); 
   strcpy(dataset, argv[2]);
   again=atoi(argv[3]);
   repeat=atoi(argv[4]);

   if ((nlines = readlines(dataset, backup, MAXLINES)) >= 0) 
   {
      switch(algorithm)
      {
         case 1: run(BenStr,      again, backup, nlines, repeat, "Quicksort"); break;
         case 2: run(multikey2,   again, backup, nlines, repeat, "MultiKey"); break;
         case 3: run(McIlroyCC,   again, backup, nlines, repeat, "MBMradix"); break;
         case 4: run(MSDsort,     again, backup, nlines, repeat, "MSD"); break;
         case 5: run(arssort,     again, backup, nlines, repeat, "Adaptive"); break;
         case 6: run(frssort1,    again, backup, nlines, repeat, "Forward8"); break;
         case 7: run(frssort,     again, backup, nlines, repeat, "Forward16"); break;
         case 8: run(burstsortL,  again, backup, nlines, repeat, "BurstsortL"); break;
         case 9: run(burstsortA,  again, backup, nlines, repeat, "BurstsortA"); break;
      }
      return 0;
   } 
   else 
   {
      fprintf(stderr, "Input file too large.\n");
      return 1;
   }
}
*/