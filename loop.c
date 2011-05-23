#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "echiquier.h"
#include "pieces.h"
#include "deplace.h"
#include "sdl.h"
#include "sdl_event.h"

int shellmon (SDL_Surface *patamon, int load, char *save)
{
    struct s_echiquier            e;
    size_t i,j;
    SDL_Event event;

    e = echiquier_create(patamon);
    echiquier_init ( &e );

    /* code de flo */
    init_sdl(&e, patamon);
    /* init de la place des pieces*/
    for (i = 0; i < 8;i++)
      for (j = 0; j < 2;j++)
	    init_piece_sdl (&e, j, i);
    for (i = 0; i < 8;i++)
      for (j = 7; j > 5;j--)
        init_piece_sdl (&e, j, i);

    ech_print( &e );

    twoplayers(e, event, load, save);
      
    free_sdl(&e);

    return 0;
}
