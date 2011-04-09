#ifndef __SDL_H
#define __SDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "echiquier.h"
#include "deplace.h"

void init_sdl(struct s_echiquier *);
void init_piece_sdl(struct s_echiquier *, int, int);
void change_postion(struct s_echiquier *, int, int);
void reset(struct s_echiquier *);
struct s_case *check_case_sdl(int x, int y, struct s_echiquier *e);
void colo_sdl(struct s_echiquier *, struct s_deplace[]);
void decolo_sdl (struct s_echiquier *);
void free_sdl(struct s_echiquier *);
#endif
