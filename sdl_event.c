#include "sdl_event.h"

void twoplayers(struct s_echiquier e, SDL_Event event)
{
    struct s_case *cini = NULL;
    struct s_case *cfin = NULL;
    struct s_case *cinipr = NULL; /*case initiale precedente*/
    struct s_deplace coup_pos[60];
    enum color joueur = blanc;
    SDL_Surface *marque;
    /* sert a savoir si on click ou non */
    int click = 0;
    int continuer = 1;

    marque = init_marque_sdl();
    while(continuer){

    /* attente d un evt */
    SDL_WaitEvent(&event);
    /* depend de l evt*/
    switch(event.type)
	{
	    /* si on quite... ben on quite la boucle*/
	case SDL_QUIT:
	    continuer = 0;
	    break;
	    /* si on click down */
	case SDL_MOUSEBUTTONDOWN:
	    if (!click)
	      {
		cinipr = cini;
		cini = check_case_sdl(event.button.x, event.button.y, &e);
		if (!cini)
		  {
		    printf("case null\n");
		    decolo_sdl(&e);
		    cini = NULL;
		    click = 0;
		  }
		else
		  {
		    printf("cini : %i\n",cini->num);
		    printf("Pion sur la case ? %i, %c soit %i\n",
			   cini->num, cini->let,((int)cini->let -65));
		    if (cini->p)
		      {
			printf("piece presente\n");
			if (joueur == cini->p->piece_color)
			  {
			    printf("piece de sa couleur\n");
			    decolo_sdl(&e);
			    if (!cinipr)
			      {
				deplace_pos_possible(&e, cini->num,
						  (int)cini->let -65,coup_pos);
				if (!colo_sdl(&e, coup_pos))
				    cini = NULL;
				}
			    else
			      {
				cinipr = NULL;
				cini = NULL;
			      }
			  }
			else
			  cini = NULL;
		      }
		    else
		      {
			if (!cinipr)
			  cini = NULL;
		      }
		    click = 1;
		  }
	      }
            break;

	    /*cas du relachent du click*/
	case SDL_MOUSEBUTTONUP:
          if (click)
	    {
	      click = 0;
	      cfin = check_case_sdl(event.button.x, event.button.y, &e);
	      if (cinipr == NULL)
		{
		  printf("on a clique sur 1 case\n");
		  if (cini != cfin)
		    {
		      printf("ICI\n");
		      if (cfin->bleu == blanc)
			{
			  printf("DEplacement non authorise\n");
			  decolo_sdl(&e);
			  cini = NULL;
			}
		      else
			{
			  printf("Case bleue\n");
			  deplacement(&e, cini->num, ((int)cini->let)-65,
				      cfin->num, ((int)cini->let)-65);
			  change_postion(&e, cini->num, ((int)cini->let)-65);
			  change_postion(&e, cfin->num, ((int)cfin->let)-65);
			  printf("WTF ?\n");
			  if (joueur == blanc)
			    joueur = noir;
			  else
			    joueur = blanc;
			  decolo_sdl(&e);
			  marque_sdl((int)cini->num, ((int)cini->let)-65, &e,
				     marque);
			  cini = NULL;
			}
		    }
		}
	      else
		  {
		      printf("cinipr non nulle\n");
		      if ( cfin != cinipr)
			{
			  if (!cfin->bleu)
			    {
			      printf("DEplacement non authorise\n");
			      decolo_sdl(&e);
			      cini = NULL;
			    }
			  else
			    {
			      printf("Case bleue\n");
			      deplacement(&e, cinipr->num, 
					  ((int)cinipr->let)-65,
					  cfin->num, ((int)cini->let)- 65);
			      change_postion(&e, cinipr->num, 
					     ((int)cinipr->let)- 65);
			      change_postion(&e, cfin->num, ((int)cfin->let)-65);
			      printf("GO !\n");
			      decolo_sdl(&e);
			      marque_sdl((int)cinipr->num, 
					 ((int)cinipr->let)-65, &e, marque);
			      cini = NULL;
			      if (joueur == blanc)
				joueur = noir;
			      else
				joueur = blanc;
			    }
			}
		      else
			{
			  printf("%i%c\n",cfin->num,cfin->let);
			}
		    }
		}
	    }
	
    }
    SDL_FreeSurface(marque);
}
