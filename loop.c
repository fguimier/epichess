#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "echiquier.h"
#include "pieces.h"
#include "deplace.h"
#include "sdl.h"
#include "sdl_event.h"

int shellmon (SDL_Surface *patamon, int load, char *save, SOCKET soc, int client, int ia)
{
    struct s_echiquier            e;
    size_t i,j;
    SDL_Event event;

    e = echiquier_create(patamon);
    echiquier_init ( &e );
      printf("Pre-inite OK\n");
      if(client)
      sleep(1);
    /* code de flo */
    init_sdl(&e, patamon);
    /* init de la place des pieces*/
    for (i = 0; i < 8;i++)
      for (j = 0; j < 2;j++)
	    init_piece_sdl (&e, j, i);
    for (i = 0; i < 8;i++)
      for (j = 7; j > 5;j--)
        init_piece_sdl (&e, j, i);
      printf("Pre-inite OK\n");
    ech_print( &e );

    i = twoplayers(e, event, load, save, soc, client, ia);
    printf("Donc\n");
    free_sdl(&e);
    printf("Mmmh\n");
    return i;
}
