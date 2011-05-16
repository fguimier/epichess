CC= gcc
CFLAGS=-g -Wall -W -pedantic -Werror -std=c99 -D_XOPEN_SOURCE=500 -lSDL -lSDL_image
EXEC=prog

SOURCES= bitboards.c b_deplace.c list.c pieces.c echiquier.c pgn.c pgn_read.c deplace.c sdl.c sdl_event.c main.c gui_tmp.c
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
	rm -f partie
#END

