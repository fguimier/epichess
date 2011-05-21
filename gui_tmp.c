#include "gui.h"


#define LO 85
#define LA 28

int gui()
{
  SDL_Surface *ecran = NULL, *fond = NULL, *new = NULL, *load = NULL, *save = NULL, *quit = NULL, *level = NULL, *easy = NULL, *medium = NULL, *hard = NULL ;
  SDL_Rect pnew, pload, psave, pquit, plevel, peasy, pmedium, phard, pfond;
  SDL_Event click; 
  int continuer = 1;
  int refresh = 1;
  pfond.x = 0;
  pfond.y = 0;

  pnew.x = 50;
  pnew.y = 60;

  pload.x = 50;
  pload.y = 120;

  psave.x = 50;
  psave.y = 180;

  pquit.x = 50;
  pquit.y = 240;

  plevel.x = 200;
  plevel.y = 60;

  peasy.x = 200;
  peasy.y = 120;

  pmedium.x = 200;
  pmedium.y = 180;

  phard.x = 200;
  phard.y = 240;

  SDL_Init(SDL_INIT_VIDEO);

  /* Chargement de l'icône AVANT SDL_SetVideoMode */
  /*DL_WM_SetIcon(SDL_LoadBMP("sdl_icone.bmp"), NULL);*/

  ecran = SDL_SetVideoMode(640, 640, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("EpiChess", NULL);

  fond = SDL_LoadBMP("sprites/echec.bmp");
  new =  SDL_LoadBMP("sprites/new.bmp");
  load = SDL_LoadBMP("sprites/1.bmp");
  save = SDL_LoadBMP("sprites/2.bmp");
  quit = SDL_LoadBMP("sprites/3.bmp");
  level =SDL_LoadBMP("sprites/4.bmp");
  easy = SDL_LoadBMP("sprites/5.bmp");
  medium=SDL_LoadBMP("sprites/6.bmp");
  hard = SDL_LoadBMP("sprites/7.bmp");

  SDL_BlitSurface(fond, NULL, ecran, &pfond);
  SDL_BlitSurface(new, NULL, ecran, &pnew);
  SDL_BlitSurface(load, NULL, ecran, &pload);
  SDL_BlitSurface(save, NULL, ecran, &psave);
  SDL_BlitSurface(quit, NULL, ecran, &pquit);
  SDL_BlitSurface(level, NULL, ecran, &plevel);
  SDL_BlitSurface(easy, NULL, ecran, &peasy);
  SDL_BlitSurface(medium, NULL, ecran, &pmedium);
  SDL_BlitSurface(hard, NULL, ecran, &phard);


  while (continuer)
    {
      if (refresh)
	{
  SDL_Flip(ecran);
  refresh = 0;
	}
      SDL_WaitEvent(&click);
      switch(click.type)
	{
	case SDL_QUIT:
	  continuer = 0;
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  if ((click.button.x >= pnew.x)&&(click.button.x <= pnew.x+LO)&&(click.button.y >= pnew.y)&&(click.button.y <= pnew.y+LA))
	    {
	    shellmon(ecran);
	    /*ptêt un peu crade...*/
	    continuer = 0;
	    refresh = 0;
	    }
	  else if ((click.button.x >= psave.x)&&(click.button.x <= psave.x+LO)&&(click.button.y >= psave.y)&&(click.button.y <= psave.y+LA))
	    printf("SAVE !\n");
	  else if ((click.button.x >= pload.x)&&(click.button.x <= pload.x+LO)&&(click.button.y >= pload.y)&&(click.button.y <= pload.y+LA))
	    printf("LOAD !\n");
	  else if ((click.button.x >= peasy.x)&&(click.button.x <= peasy.x+LO)&&(click.button.y >= peasy.y)&&(click.button.y <= peasy.y+LA))
	    printf("EASY !\n");
	  else if ((click.button.x >= pmedium.x)&&(click.button.x <= pmedium.x+LO)&&(click.button.y >= pmedium.y)&&(click.button.y <= pmedium.y+LA))
	    printf("MOYEN !\n");
	  else if ((click.button.x >= phard.x)&&(click.button.x <= phard.x+LO)&&(click.button.y >= phard.y)&&(click.button.y <= phard.y+LA))
	    printf("HARD !\n");
	  else if ((click.button.x >= pquit.x)&&(click.button.x <= pquit.x+LO)&&(click.button.y >= pquit.y)&&(click.button.y <= pquit.y+LA))
	    {
	    printf("QUIT !\n");
	    continuer = 0;
	    }

	  break;
	}
    }

  SDL_FreeSurface(new);
  SDL_FreeSurface(load);
  SDL_FreeSurface(save);
  SDL_FreeSurface(quit);
  SDL_FreeSurface(level);
  SDL_FreeSurface(easy);
  SDL_FreeSurface(medium);
  SDL_FreeSurface(hard);

  SDL_Quit();

  return EXIT_SUCCESS;
}
