#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <dirent.h>
#include "echiquier.h"
#include "pieces.h"
#include "deplace.h"
#include "sdl.h"
#include "sdl_event.h"
#include "loop.h"
#include "socketclient.h"

struct s_bouton                                                       
{                            
  SDL_Rect *pos;                     
  SDL_Surface *sprite;                                         
};

struct s_bouton *menu_init(int i);
const char* conv(char *truc);
