#include "sdl_event.h"
#include "b_deplace.h"
int fill_depl(char *coup, int i, struct s_case *init, struct s_case *cfin,
	      t_list pos)
{
  size_t j = length(pos);
  t_list c, l;/*contiennent les cases dont les Colones ou les Lignes snt ==*/

  c=l=NULL;
  if (pos)/*a delete*/
    {
	c = add(init, c);
	l = add(init, l);
      pos = pos->next;
    }
  if (j > 1)
    {
      while (pos)
	{
	    if (((struct s_case*)(c->val))->num ==
		((struct s_case*)(pos->val))->num)
		add(c, pos->val);
	    if (((struct s_case*)(l->val))->let == 
		((struct s_case*)(pos->val))->let)
		add(l, pos->val);
	    pos = pos->next;
	}
    }
  if (length(c) >1 || length(l) >1)
    {
      if (length(l) == 1)
	{
	  i++;/*c > 1*/
	  coup[i] = cfin->num + 48;
	}
      else
	{
	  if (length(c) == 1)
	    {
	      i++;/*l > 1*/
	      coup[i] = cfin->let + 32;
	    }
	  else
	    {
	      i++;
	      coup[i] = cfin->num + 48;
	      i++;
	      coup[i] = cfin->let + 32;
	    }
	}
    }
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

int fill_coup(struct s_echiquier *e, char *coup, int i, struct s_case *cini,
	      struct s_case *cfin, struct s_bb *bb_bl, struct s_bb *bb_wh)
{
    /* il manque roque, simple et grand, la mise en échec, la promotion
       -> variables en plus pour éviter les multiples roques */
  t_list pos = NULL;

  switch(cini->p->piece_name)
    {
    case pion :
	    /*recherche d'ambiguité ignorée pour le moment*/
	    i--;
	    i = fill_depl(coup, i, cini, cfin, pos);
	    break;
	case tour :
	    coup[i] = 'R';
            pos = search_tower(e, cini, cini->p->piece_color, bb_bl, bb_wh);
	    i = fill_depl(coup, i, cini, cfin, pos);
            break;
	case cavalier :
            coup[i] = 'N';
            /*recherche d'ambiguité ignorée pour le moment*/

            i = fill_depl(coup, i, cini, cfin, pos);
            break;
	case fou :
            coup[i] = 'N';
            /*recherche d'ambiguité ignorée pour le moment*/
	    
            i = fill_depl(coup, i, cini, cfin, pos);
            break;
	case dame :
	    coup[i] = 'Q';
	    /*recherche d'ambiguité ignorée pour le moment*/

	    i = fill_depl(coup, i, cini, cfin, pos);
	    break;
	case roi :
	    coup[i] = 'K';
	    i = fill_depl(coup, i, cini, cfin, pos);
	    break;
	}
    return i;
}


int fill_tab(struct s_echiquier *e, char **mem, int i, struct s_case *cini,
	     struct s_case *cfin, struct s_bb *bb_bl, struct s_bb *bb_wh)
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
	    
	    j = fill_coup(e, coup, j, cini, cfin, bb_bl, bb_wh);
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
	    j = fill_coup(e, coup, j, cini, cfin, bb_bl, bb_wh);
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

void update_b(struct s_bb *bb_bl, struct s_bb *bb_wh, struct s_case *cini,
	      struct s_case *cfin)
{
  /*trouver bitboard, trouver cfin, le mettre en cfin, maj de bb[0], noir -
    blanc & avec les noirs ->*/
    bitboard fin = get_case(7-cfin->num,(cfin->let-65));
    bitboard cin = get_case(7-cini->num,(cini->let-65));
  print_ech(cin);
  print_ech(fin);
  printf("%i,%c\n",cini->num, cini->let);
  int i = 1;
  int j = 1;
  if (cini->p->piece_color == blanc)
    {
      while (bb_wh->pieces[i] != cin)
	  {
	      print_ech(bb_wh->pieces[i]);
	      i++;
	  }
      printf("B %i\n",i);
      bb_wh->pieces[0] = bb_wh->pieces[0] & ~bb_wh->pieces[i];
      bb_wh->pieces[0] = bb_wh->pieces[0] | fin;
      print_ech(bb_wh->pieces[0]);
      if (cfin->p)
	{
	  while (bb_bl->pieces[j] != fin)
	    j++;
	  bb_bl->pieces[j]= 0x0000000000000000;
	  bb_bl->pieces[0]=bb_bl->pieces[0] & ~fin;
	}
      bb_wh->pieces[i] = fin;
      printf("%i\n",i);
    }
  else
      {
	  while (bb_bl->pieces[i] != cin)
	      {
		  print_ech(bb_bl->pieces[i]);
		  i++;
	      }
	  printf("N %i\n",i);
	  bb_bl->pieces[0] = bb_bl->pieces[0] & ~bb_bl->pieces[i];
	  bb_bl->pieces[0] = bb_bl->pieces[0] | fin;
	  print_ech(bb_bl->pieces[0]);
	  if (cfin->p)
	      {
		  while (bb_wh->pieces[j] != fin)
		      j++;
		  bb_wh->pieces[j]= 0x0000000000000000;
		  bb_wh->pieces[0]=bb_bl->pieces[0] & ~fin;
	      }
	  bb_bl->pieces[i] = fin;
      }

}

void twoplayers(struct s_echiquier e, SDL_Event event)
{
    int i = 1;
    bitboard        que = WHITE_P2, poss;
    struct s_bb     bb_bl, bb_wh;/*0:pop;1-8:pions;9:tourgauch,10:cavgauch...
				  roiblan=reinenoi*/
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
    int mort = 0;

    populate (&bb_bl, WHITE);/*init*/
    populate (&bb_wh, BLACK)/*je vous emmerde*/;
    marque = init_marque_sdl();
    print_ech(~que);
    poss = dep_queen(que, 0x00,0x00);
    print_ech (que);
    poss = dep_pawn(que, bb_bl.pieces[0], bb_wh.pieces[0], WHITE);
    print_ech(poss);

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
			  i = fill_tab(&e,mem, i, cini, cfin, &bb_bl, &bb_wh);
			  if (cfin->p)
			    mort = 1;
			  update_b(&bb_bl, &bb_wh, cini, cfin);
			  dead= deplacement(&e, cini->num, ((int)cini->let)-65,
				      cfin->num, ((int)cfin->let)-65, dead);
			  change_postion(&e, cini->num, ((int)cini->let)-65);
			  change_postion(&e, cfin->num, ((int)cfin->let)-65);
			  if (mort == 1)
			    blit_dead_sdl(dead ,&e);
			  mort = 0;
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
			      i = fill_tab(&e, mem, i, cinipr, cfin,
					   &bb_bl, &bb_wh);
			      printf("hmm\n");
			      if (cfin->p)
				mort = 1;
			      update_b(&bb_bl, &bb_wh, cinipr, cfin);
			      dead = deplacement(&e, cinipr->num,
					  ((int)cinipr->let)-65,
					cfin->num, ((int)cfin->let)- 65, dead);
			      printf("mmh\n");
			      change_postion(&e, cinipr->num,
					     ((int)cinipr->let)- 65);
			      change_postion(&e, cfin->num,
					     ((int)cfin->let)-65);
			      printf("GO !\n");
			      if (mort)
				blit_dead_sdl(dead ,&e);
			      mort = 0;
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
