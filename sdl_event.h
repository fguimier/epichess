#ifndef __SDL_EVENT_H
#define __SDL_EVENT_H

#include <SDL/SDL.h>
#include "sdl.h"
#include "list.h"
#include "pgn.h"
#include "pgn_read.h"
 
int twoplayers(struct s_echiquier, SDL_Event, int, char *);

#endif
