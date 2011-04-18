#include "sdl_event.h"

int fill_depl(char *coup, int i, struct s_case *cfin)
{
    if (cfin->p)
	{
	    i++;
	    coup[i] = 'x';
	}
    i++;
    coup[i] = cfin->let + 32;
    i++;
    coup[i] = 8 - cfin->num + 48;
    i++;
    return i;
}

int fill_coup(char *coup, int i, struct s_case *cini, struct s_case *cfin)
{
    /* il manque roque, simple et grand, la mise en échec, la promotion
       -> variables en plus pour éviter les multiples roques */
    
    switch(cini->p->piece_name)
	{
	case pion :
	    /*recherche d'ambiguité ignorée pour le moment*/
	    i--;
	    i = fill_depl(coup, i, cfin);
	    break;
	case tour :
	    coup[i] = 'R';
            /*recherche d'ambiguité ignorée pour le moment*/

	    i = fill_depl(coup, i, cfin);
            break;
	case cavalier :
            coup[i] = 'N';
            /*recherche d'ambiguité ignorée pour le moment*/

            i = fill_depl(coup, i, cfin);
            break;
	case fou :
            coup[i] = 'N';
            /*recherche d'ambiguité ignorée pour le moment*/
	    
            i = fill_depl(coup, i, cfin);
            break;
	case dame :
	    coup[i] = 'Q';
	    /*recherche d'ambiguité ignorée pour le moment*/

	    i = fill_depl(coup, i, cfin);
	    break;
	case roi :
	    coup[i] = 'K';
	    i = fill_depl(coup, i, cfin);
	    break;
	}
    return i;
}

int fill_tab(char **mem, int i, struct s_case *cini, struct s_case *cfin)
{
    char coup[30];
    int j = 0;
    int h = i;

    if (mem[i])
	{
	    /*les blancs ont déjà joué*/
	    while (mem[i][j])
		{
		    coup[j] = mem[i][j];
		    j++;
		}
	    j = fill_coup(coup, j, cini, cfin);
	    coup[j] = ' ';
	    j++;
            coup[j] = 0;
	    for (; j >= 0; j--)
		mem[i][j] = coup[j];
	    printf("coup : %s\n",coup);
	    i++;
	}
    else
	{
	    mem[i] = malloc(30);
	    while(h)
		{
		    mem[i][j] = (h%10)+48;
		    h = (h - (h%10)) / 10;
		    j++;
		}
	    j--;
	    h = j;
	    for (;j >= 0; j--)
		coup[h-j] = mem[i][j];
	    j = h;
	    j++;
	    coup[j] = '.';
	    j++;
	    j = fill_coup(coup, j, cini, cfin);
	    mem[i][j] = ' ';
	    mem[i][j+1] = 0;
	    j--;
	    for (; j >= 0; j--)
		{
		    mem[i][j] = coup[j];
		}
	    printf("coup : %s\n",mem[i]);
	}
    return i; 
}

void twoplayers(struct s_echiquier e, SDL_Event event)
{
    int i = 1;
    struct s_case *cini = NULL;
    struct s_case *cfin = NULL;
    struct s_case *cinipr = NULL; /*case initiale precedente*/
    struct s_deplace coup_pos[60];
    t_list dead = NULL;
    char **mem = calloc(500,sizeof(char *));
    enum color joueur = blanc;
    SDL_Surface *marque;
    /* sert a savoir si on click ou non */
    int click = 0;
    int continuer = 1;

    marque = init_marque_sdl();
    dead = dead;
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
			    if (!cinipr)
			      {
				decolo_sdl(&e);
				deplace_pos_possible(&e, cini->num,
						  (int)cini->let -65,coup_pos);
				if (!colo_sdl(&e, coup_pos))
				    cini = NULL;
			      }
			    else
			      {
				if (cinipr == cini)
				  {
				      /*reclick sur la même case ->glisse*/
				      cini = cinipr;
				  }
				else
				  {
				      decolo_sdl(&e);
				      cinipr = NULL;
				      cini = NULL;
				  }
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
			  i = fill_tab(mem, i, cini, cfin);
			  deplacement(&e, cini->num, ((int)cini->let)-65,
				      cfin->num, ((int)cfin->let)-65, dead);
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
			      i = fill_tab(mem, i, cinipr, cfin);
			      printf("hmm\n");
			      deplacement(&e, cinipr->num, 
					  ((int)cinipr->let)-65,
					cfin->num, ((int)cfin->let)- 65, dead);
			      printf("mmh\n");
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
    pgn_out(mem, "partie");
    for (; i >= 0;i--)
	{
	    if (mem[i])
		free(mem[i]);
	}
    free(mem);
}
