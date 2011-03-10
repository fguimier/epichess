CC= gcc
CFLAGS=-g -Wall -W -pedantic -Werror -ansi -D_XOPEN_SOURCE=500
EXEC=prog

SOURCES= pieces.c echiquier.c main.c
HEADERS= ${SOURCES:.c=.h}
OBJECTS= ${SOURCES:.c=.o}

all: ${EXEC}

#gen de l'executable	
prog: ${OBJECTS}
	${CC} ${CFLAGS} -o ${EXEC} ${OBJECTS}

#nettoyage
clean::
	rm -f *~
	rm -f *.o
	rm -f ${EXEC}
#END

