#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


struct s_bouton                                                       
{                            
  SDL_Rect *pos;                     
  SDL_Surface *sprite;                                         
};

struct s_bouton *menu_init(int i);

