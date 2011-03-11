#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


#define h 50

void pause()
{
  int continuer = 1;
  SDL_Event event;

  while (continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
        {
	case SDL_QUIT:
	  continuer = 0;
        }
    }
}

void init()
{
  SDL_Surface *ecran = NULL;
  SDL_Surface *carre = NULL;
  SDL_Rect position;
  size_t i,j;

  ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 100, 100));

  carre = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
  for (j = 0; j < 8; j+=2)
    for (i = 0; i < 8;i+=2)
      {
	SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	position.x = i * h;
	position.y = j * h;
	SDL_BlitSurface(carre, NULL, ecran, &position);
	
	SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	position.x = (i + 1)*h;
	position.y = j * h;
	SDL_BlitSurface(carre, NULL, ecran, &position);

	SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        position.x = (i+1) * h;
        position.y = (j+1) * h;
	SDL_BlitSurface(carre, NULL, ecran, &position);

        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	position.x = i*h;
        position.y = (j+1)* h;
        SDL_BlitSurface(carre, NULL, ecran, &position);

      }
  SDL_Flip(ecran);
}

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  
  init();

  pause();
  /*il manque un free*/
  SDL_Quit();
 
  return EXIT_SUCCESS;
}
