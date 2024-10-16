#  The code presented in this file has been tested with care but is
#  not guaranteed for any purpose. The writer does not offer any
#  warranties nor does he accept any liabilities with respect to
#  the code.
#
#  Ranjan Sinha 28th July 2003
#
#  School of Computer Science and Information Technology,
#  RMIT University, Melbourne, Australia
#  rsinha@cs.rmit.edu.au

# The name of our program:
PROGRAM= sortstring

# These are our C source files:
SRCS= sortstring.c utils.c clock.c benqsort.c multikey.c mbmradix.c msd.c forward8.c forward16.c adaptive.c mkqsort.c burstsortL.c burstsortA.c

# The name of the C-compiler we want to use:
CC= gcc

# The flags (options) that the C-compiler needs:
CFLAGS = -O3            # optimization
#CFLAGS = -g -Wall -ansi      # debugging, warnings
#CFLAGS = -xa           # tcov, profiling, works only with cc
#CFLAGS = -xpg          # gprof, works only with cc

# Names of libraries we need to link with our program:
LDLIBS= -lm

# Object files are derived from the sources, with .c replaced by .o
OBJECTS = ${SRCS:%.c=%.o}

# The first target, the name of our program:
${PROGRAM}: $(OBJECTS)
	$(LINK.c) -o $@ $(OBJECTS) $(LDLIBS)

# To remove generated object files:
clean:
	-rm -f ${OBJECTS}
