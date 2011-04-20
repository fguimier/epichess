CC = gcc `sdl-config --cflags --libs`
CFLAGS = -O2 -Wall -W -pedantic -ansi -g

SRCFILES = gui_tmp.c # sources (only .c files)
OUTFILE = tmp

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