CC = gcc `sdl-config --cflags --libs`
CFLAGS = -O2 -Wall -W -Werror -pedantic -ansi

SRCFILES = main.c # sources (only .c files)
OUTFILE = main

## compilation ##

OBJFILES = $(SRCFILES:.c=.o)

all : $(OUTFILE)

$(OUTFILE) : $(OBJFILES)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

## cleaning ##

clean :
	rm -vf *.o $(OUTFILE)

distclean : clean
	rm -vf *~ \#*\#