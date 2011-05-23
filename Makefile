CC= gcc
OCAML=ocamlopt
CFLAGS=-g -Wall -W -pedantic -Werror -std=c99 -D_XOPEN_SOURCE=500 -lSDL -lSDL_image -I/usr/lib/ocaml -c
EXEC=prog
OFLAGS= -cc "gcc" -ccopt -g -ccopt -Wall -ccopt -W -ccopt -pedantic -ccopt -Werror -ccopt -std=c99 -ccopt -D_XOPEN_SOURCE=500 -ccopt -lSDL -ccopt -lSDL_image
SOURCES= bitboards.c b_deplace.c list.c pieces.c echiquier.c deplace.c sdl.c pgn.c pgn_read.c sdl_event.c loop.c gui_tmp.c
HEADERS= ${SOURCES:.c=.h}
OBJECTS= ${SOURCES:.c=.o}

all: ${EXEC}

#gen de l'executable
prog: ${OBJECTS}
	${CC} ${CFLAGS} ${SOURCES}
	${OCAML} ${OFLAGS} -c main.ml
	${OCAML} ${OFLAGS} -o ${EXEC} main.cmx ${OBJECTS} 

#nettoyage
clean::
	rm -f *~
	rm -f *.o
	rm -f *.cm*
	rm -f ${EXEC}
#END

