#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "echiquier.h"
#include "pieces.h"
#include "deplace.h"
#include "sdl.h"


int main ()
{
    struct s_echiquier            e;
    struct s_case *cini = NULL;
    struct s_case *cfin = NULL;
    struct s_case *cinipr = NULL; /*case initiale precedente*/
    size_t i,j;
    struct s_deplace coup_pos[60];
    SDL_Event event;
    int continuer = 1;
    enum color joueur = blanc;
    /* sert a savoir si on click ou non */
    int click = 0;

    e = echiquier_create();
    echiquier_init ( &e );

    /* code de flo */
    init_sdl(&e);
    /* init de la place des pieces*/
    for (i = 0; i < 8;i++)
      for (j = 0; j < 2;j++)
	    init_piece_sdl (&e, j, i);
    for (i = 0; i < 8;i++)
      for (j = 7; j > 5;j--)
        init_piece_sdl (&e, j, i);

    ech_print( &e );

/* tant quon ferme pas sdl */
    while(continuer)
      {
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
		printf("cini : %i\n",cini->num);
		if (!cini)
		  {
		    printf("case null\n");
		    decolo_sdl(&e);
		    cini = NULL;
		  }
		else
		  {
		    printf("Pion sur la case ? %i, %c soit %i\n",cini->num, cini->let,((int)cini->let -65));
		    if (cini->p)
		      {
			printf("piece presente\n");
			if (joueur == cini->p->piece_color)
			  {
			    printf("piece blanche\n");
			    decolo_sdl(&e);
			    deplace_pos_possible(&e, cini->num,
						 (int)cini->let -65,coup_pos);
			    colo_sdl(&e, coup_pos);
			  }
			else
			  cini = NULL;
		      }
		  }
		click = 1;
	      }
	    break;

 /*   deplacement(&e, 0, 1, 2, 2);
          change_postion(&e,2,2);
          change_postion(&e,0,1);*/

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
			    decolo_sdl(&e);
			    cini = NULL;
			  }
		      }
		    else
		      /* si on est sur une case bleu go sion pas clean */
		      if (cfin->bleu!=blanc)
			{
			  printf("Case bleue\n");
			  deplacement(&e, cini->num, ((int)cini->let)-65,
				      cfin->num, ((int)cini->let)-65);
			  /*deplacement_sdl;*/
			  printf("WTF ?\n");
			  if (joueur == blanc)
			    joueur = noir;
			  else
			    joueur = blanc;
			  decolo_sdl(&e);
			  cini = NULL;
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
			    deplacement(&e, cinipr->num, ((int)cinipr->let)-65,
					cfin->num, ((int)cini->let)- 65);
			    change_postion(&e, cinipr->num, ((int)cinipr->let)-65);
			    change_postion(&e, cfin->num, ((int)cfin->let)-65);
			    printf("GO !\n");
			    decolo_sdl(&e);
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
    free_sdl(&e);

    return 0;
}
