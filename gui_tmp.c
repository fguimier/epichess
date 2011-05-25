#include "gui.h"


#define LO 85
#define LA 28
#define PATHSAVE 92
int gui()
{
 SDL_Surface *ecran = NULL, *fond = NULL, *new = NULL, *load = NULL, *quit = NULL, *level = NULL, *easy = NULL, *medium = NULL, *hard = NULL, *fond2 = NULL;
 SDL_Surface *fond3;
 SDL_Rect pfond3;
 SDL_Rect pnew, pload, pquit, plevel, peasy, pmedium, phard, pfond, pfond2;
 SDL_Event click;
 SDL_Event key;
 int continuer = 1;
 int i = 0;
 int refresh = 1;
 int qqchose = 1;
 char *test = malloc(sizeof(char));
 char* loadtext = malloc(sizeof(char));
 char *accu = malloc(sizeof(char));
 TTF_Font *p_font = malloc(256);
 TTF_Font *p_font2 = malloc(256);
 SDL_Surface *s_text = malloc(sizeof(struct SDL_Surface)*3);
 SDL_Rect *rect_dest = malloc(sizeof(struct SDL_Rect));
 SDL_Surface *s_accu = malloc(sizeof(struct SDL_Surface)*3);
 SDL_Rect *rect_accu = malloc(sizeof(struct SDL_Rect));
 SDL_Color color;
 SDL_Color color2;
 const char *tmp;
 DIR* rep = NULL;
 struct dirent* fichierLu = NULL;
 SOCKET csock = 0;
 

 printf("dd : %d", sizeof(struct res));
  color.r = 0;
  color.g = 0;
  color.b = 0;

  color2.r = 255;
  color2.g = 255;
  color2.b = 255;

  rect_dest->x = 360;
  rect_dest->y = 118;

  rect_accu->x = 5;
  rect_accu->y = 430;
 
  pfond.x = 0;
  pfond.y = 0;

  pfond3.x = 0;
  pfond3.y = 425;

  pfond2.x = 350;
  pfond2.y = 120;

  pnew.x = 50;
  pnew.y = 60;

  pload.x = 50;
  pload.y = 120;

  pquit.x = 50;
  pquit.y = 180;

  plevel.x = 200;
  plevel.y = 60;

  peasy.x = 200;
  peasy.y = 120;

  pmedium.x = 200;
  pmedium.y = 180;

  phard.x = 200;
  phard.y = 240;

  strcat(loadtext,"save/");

   SDL_Init(SDL_INIT_VIDEO);
/* ----- Initialisation de SDL_ttf ----- */
   if (TTF_Init ()< 0)
    {
      printf("you're all going to die down here !\n The Red Queen \n");
    }
  /* Chargement de l'icône AVANT SDL_SetVideoMode */
  /*DL_WM_SetIcon(SDL_LoadBMP("sdl_icone.bmp"), NULL);*/
  p_font = TTF_OpenFont("arial.ttf", 16);
  p_font2 = TTF_OpenFont("arial.ttf", 16);
  ecran = SDL_SetVideoMode(640, 640, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("EpiChess", NULL);


  fond = SDL_LoadBMP("sprites/echec.bmp");
  fond2 = SDL_LoadBMP("sprites/fond2.bmp");
  fond3 = SDL_LoadBMP("sprites/fond3.bmp");
  new =  SDL_LoadBMP("sprites/new.bmp");
  load = SDL_LoadBMP("sprites/2.bmp");
  quit = SDL_LoadBMP("sprites/3.bmp");
  level =SDL_LoadBMP("sprites/4.bmp");
  easy = SDL_LoadBMP("sprites/5.bmp");
  medium=SDL_LoadBMP("sprites/6.bmp");
  hard = SDL_LoadBMP("sprites/7.bmp");

  while(qqchose)
    {
  SDL_BlitSurface(fond, NULL, ecran, &pfond);
  SDL_BlitSurface(new, NULL, ecran, &pnew);
  SDL_BlitSurface(load, NULL, ecran, &pload);
  SDL_BlitSurface(quit, NULL, ecran, &pquit);
  SDL_BlitSurface(level, NULL, ecran, &plevel);
  SDL_BlitSurface(easy, NULL, ecran, &peasy);
  SDL_BlitSurface(medium, NULL, ecran, &pmedium);
  SDL_BlitSurface(hard, NULL, ecran, &phard);
  continuer = 1;
  refresh = 1;
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
	  qqchose = 0;
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  if ((click.button.x >= pnew.x)&&(click.button.x <= pnew.x+LO)&&(click.button.y >= pnew.y)&&(click.button.y <= pnew.y+LA))
	    {
		if(!shellmon(ecran, 0, "partie",csock,0))
		  {
		    /*ptêt un peu crade...*/
		    continuer = 0;
		    refresh = 0;
		    qqchose =0;
	          }
		else 
		  {continuer =0;}
	    }
	  else if ((click.button.x >= pload.x)&&(click.button.x <= pload.x+LO)&&(click.button.y >= pload.y)&&(click.button.y <= pload.y+LA))
	    {
	      accu[0] = 0;
	      rep = opendir("save");
	      fichierLu = readdir(rep);
	      while ((fichierLu = readdir(rep)) != NULL)
		{
		  strcat(accu,fichierLu->d_name);
		  strcat(accu,"\n");
		}
	      SDL_BlitSurface(fond2, NULL, ecran, &pfond2);
	      SDL_BlitSurface(fond3, NULL, ecran, &pfond3);
	      s_accu = TTF_RenderText_Solid(p_font2, accu, color2);
	      rect_accu->w = s_accu->w;
	      rect_accu->h = s_accu->h;
	      SDL_BlitSurface(s_accu, NULL, ecran, rect_accu);
 test = malloc(sizeof(char));
	      SDL_Flip(ecran);
	      closedir(rep);
	      while(strcmp(test,"return"))
		{
		  SDL_Flip(ecran);
		  SDL_WaitEvent(&key);
		  switch (key.type)
		    {
		    case SDL_KEYDOWN:
		      {
		        test = SDL_GetKeyName(key.key.keysym.sym);
			printf("coucou : %s\n", test);
			if((strcmp(test,"return")) && (strcmp(test, "backspace")) && (strcmp(test,"space")))
			  strcat(loadtext, test);
			if(!strcmp(test, "backspace"))
			  loadtext[((strlen(loadtext))-1)] = '\0';			
			if(!strcmp(test,"space"))
			     strcat(loadtext, " ");
			if(strlen(loadtext))
			  {			  
			    tmp = conv(loadtext);
			    s_text = TTF_RenderText_Solid(p_font, loadtext, color);
			    rect_dest->w = s_text->w;
			    rect_dest->h = s_text->h;
			    SDL_BlitSurface(fond2, NULL, ecran, &pfond2);
			    SDL_Flip(ecran);
			    SDL_BlitSurface (s_text, NULL, ecran, rect_dest);
			    SDL_Flip(ecran);
			  }
		      }
		      break;
		    }
		  i++;
		}
	      printf("le texte taper est : %s \n", loadtext);
	      if(!shellmon(ecran,1,loadtext, csock, 0))
	       {
	         continuer = 0;
	         refresh = 0;
		 qqchose = 0;
	       }
	      else
		{
		  continuer = 0;
		}
	      printf("LOAD !\n");

	    }
	  else if ((click.button.x >= peasy.x)&&(click.button.x <= peasy.x+LO)&&(click.button.y >= peasy.y)&&(click.button.y <= peasy.y+LA))
	    printf("EASY !\n");
	  else if ((click.button.x >= pmedium.x)&&(click.button.x <= pmedium.x+LO)&&(click.button.y >= pmedium.y)&&(click.button.y <= pmedium.y+LA))
	    {
	      csock = init_client();
            printf("Pre-inite du client OK\n");
	      if(!shellmon(ecran,0,"petit",csock, 1))
	       {
	         continuer = 0;
	         refresh = 0;
		   qqchose = 0;
	       }
	      else
		{
		  continuer = 0;
		}
	      if(csock != 0)
		closesocket(csock);
	    }
	  else if ((click.button.x >= phard.x)&&(click.button.x <= phard.x+LO)&&(click.button.y >= phard.y)&&(click.button.y <= phard.y+LA))
	    {
	      csock = init_server();
            printf("Pre-inite du serveur OK\n");
	      if(!shellmon(ecran,0,"partie",csock,0))
	       {
	         continuer = 0;
	         refresh = 0;
		 qqchose = 0;
	       }
	      else
		{
		  continuer = 0;
		}
	      if(csock != 0)
		closesocket(csock);
	    }
	    
	  else if ((click.button.x >= pquit.x)&&(click.button.x <= pquit.x+LO)&&(click.button.y >= pquit.y)&&(click.button.y <= pquit.y+LA))
	    {
	    printf("QUIT !\n");
	    continuer = 0;
	    qqchose = 0;
	    }

	  break;
     	}
    }
    }
  TTF_CloseFont(p_font);
  SDL_FreeSurface(fond2);
  SDL_FreeSurface(new);
  SDL_FreeSurface(load);
  SDL_FreeSurface(quit);
  SDL_FreeSurface(level);
  SDL_FreeSurface(easy);
  SDL_FreeSurface(medium);
  SDL_FreeSurface(hard);

  SDL_Quit();

  return EXIT_SUCCESS;
}



const char* conv(char *truc)
{
  const char *tmp = truc;
  return(tmp);

}
