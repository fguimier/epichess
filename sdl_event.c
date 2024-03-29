#include "sdl_event.h"
#include "b_deplace.h"

#define LO 85
#define LA 28

int fill_depl(char *coup, int i, struct s_case *init, struct s_case *cfin,
              t_list pos)
{
  size_t j = length(pos);
  t_list c, l;/*contiennent les cases dont les Colones ou les Lignes snt ==*/

  c=l=NULL;
  c = add(cfin, c);
  l = add(cfin, l);
  printf("%i doublons\n",j);
  if (j > 0)
    {
      while (pos)
        {
	  printf("%c,%i-%c,%i\n",((struct s_case*)(c->val))->let,
		 ((struct s_case*)(l->val))->num,
		 ((struct s_case*)(pos->val))->let,((struct s_case*)(pos->val))->num);
	  if (((struct s_case*)(l->val))->num ==
	      ((struct s_case*)(pos->val))->num)
	    l = add(pos->val, l);
	  if (((struct s_case*)(c->val))->let == 
	      ((struct s_case*)(pos->val))->let)
	    c = add(pos->val, c);
	  pos = pos->next;
        }
    }
  printf("%i col ident ; %i lign ident",length(c),length(l));
  if (length(c) >1 || length(l) >1)
    {
      if (length(l) == 1)
        {
          i++;/*c > 1*/
          coup[i] = 8 - init->num + 48;
        }
      else
	{
          if (length(c) == 1)
            {
              i++;/*l > 1*/
              coup[i] = init->let + 32;
            }
          else
            {
              i++;
              coup[i] = 8 - init->num + 48;
              i++;
              coup[i] = init->let + 32;
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
      pos = search_tower(e, cini, cfin, cini->p->piece_color, 
			 bb_bl, bb_wh);
      i = fill_depl(coup, i, cini, cfin, pos);
      break;
    case cavalier :
      coup[i] = 'N';
      /*recherche d'ambiguité ignorée pour le moment*/

      i = fill_depl(coup, i, cini, cfin, pos);
      break;
    case fou :
      coup[i] = 'B';
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
      printf("%s\n",coup);
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
  /*print_ech(cin);
  print_ech(fin);
  printf("%i,%c\n",cini->num, cini->let);*/
  int i = 1;
  int j = 1;
  if (cini->p->piece_color == blanc)
    {
      while (bb_wh->pieces[i] != cin)
	{
	  /*print_ech(bb_wh->pieces[i]);*/
	  i++;
	}
      /*printf("B %i\n",i);*/
      bb_wh->pieces[0] = bb_wh->pieces[0] & ~bb_wh->pieces[i];
      bb_wh->pieces[0] = bb_wh->pieces[0] | fin;
      /*print_ech(bb_wh->pieces[0]);*/
      if (cfin->p)
        {
          while (bb_bl->pieces[j] != fin)
            j++;
          bb_bl->pieces[j]= 0x0000000000000000;
          bb_bl->pieces[0]=bb_bl->pieces[0] & ~fin;
        }
      bb_wh->pieces[i] = fin;
      /* printf("%i\n",i);*/
    }
  else
    {
      while (bb_bl->pieces[i] != cin)
	{
	  /*  print_ech(bb_bl->pieces[i]);*/
	  i++;
	}
      /*        printf("N %i\n",i);*/
      bb_bl->pieces[0] = bb_bl->pieces[0] & ~bb_bl->pieces[i];
      bb_bl->pieces[0] = bb_bl->pieces[0] | fin;
      /* print_ech(bb_bl->pieces[0]);*/
      if (cfin->p)
	{
	  while (bb_wh->pieces[j] != fin)
	    j++;
	  bb_wh->pieces[j]= 0x0000000000000000;
	  bb_wh->pieces[0]=bb_wh->pieces[0] & ~fin;
	}
      bb_bl->pieces[i] = fin;
    }
  calc_all_dep(bb_bl, bb_wh);
}

int update(struct s_echiquier *e, struct s_case *cini,struct s_case *cfin,
           struct s_bb *bb_bl, struct s_bb *bb_wh, char **mem, t_list *dead,
           enum color *joueur, SDL_Surface *marque, int i)
{
  int mort = 0;
  i = fill_tab(e,mem, i, cini, cfin, bb_bl, bb_wh);
  if (cfin->p)
    mort = 1;
  update_b(bb_bl, bb_wh, cini, cfin);
  *dead= deplacement(e, cini->num, ((int)cini->let)-65,
		     cfin->num, ((int)cfin->let)-65, *dead);
  change_postion(e, cini->num, ((int)cini->let)-65);
  change_postion(e, cfin->num, ((int)cfin->let)-65);
  if (mort == 1)
    blit_dead_sdl(*dead ,e);
  if (*joueur == blanc)
    *joueur = noir;
  else
    *joueur = blanc;
  decolo_sdl(e);
  marque_sdl((int)cini->num, ((int)cini->let)-65, e,
	     marque);
  return i;
}

int twoplayers(struct s_echiquier e, SDL_Event event, int load, char *save, SOCKET soc, int client, int ia)
{
  int i = 1;
  struct s_bb     bb_bl, bb_wh;/*0:pop;1-8:pions;9:tourgauch,10:cavgauch...
				 roiblan=reinenoi*/
  struct s_case *cini = NULL;
  struct s_case *cfin = NULL;
  struct s_case *cinipr = NULL; /*case initiale precedente*/
  struct s_deplace coup_pos[60];
  t_list dead = NULL;
  rez rezo = malloc(sizeof(struct res));
  char **mem = calloc(500,sizeof(char *));
  enum color joueur = noir;
  SDL_Surface *marque;
  /* sert a savoir si on click ou non */
  int click = 0;
  int continuer = 1;
  SDL_Surface *save1 = NULL, *retour = NULL;
  SDL_Rect psave1, pretour;

  printf("Pre-inite OK\n");
      
  psave1.x = 500;
  psave1.y = 500;

  pretour.x = 410;
  pretour.y = 500;

  save1 = SDL_LoadBMP("sprites/1.bmp");
  retour = SDL_LoadBMP("sprites/retour.bmp");

  SDL_BlitSurface(retour, NULL, e.screen, &pretour);
  SDL_BlitSurface(save1, NULL, e.screen, &psave1);
  
  populate (&bb_bl, WHITE);
  populate (&bb_wh, BLACK);
  marque = init_marque_sdl();
    for (; i < 15; i++)
    {
        bb_bl.pieces[i] = 0;
        bb_wh.pieces[i] = 0;
    }
    bb_bl.pieces[15] = 0;
    bb_wh.pieces[15] = deplace_f(deplace_f(deplace_f(1)));
    bb_wh.pieces[9] = 0x100;
    update_piece(&bb_wh);
    update_piece(&bb_bl);
    print_ech(bb_wh.pieces[0] | bb_bl.pieces[0]);
    calc_all_dep(&bb_bl, &bb_wh);
      printf("Pre-inite OK\n");
  if(client)
      {
            recv(soc, rezo, sizeof(struct res),0);
            cinipr = &(e.mat[rezo->di][rezo->dj]);
            cfin = &(e.mat[rezo->ai][rezo->aj]);
            printf("%i%c\n",cfin->num,cfin->let);
            i = update(&e, cinipr,cfin, &bb_bl, &bb_wh, mem,
			     &dead, &joueur, marque, i);
      cini =NULL;
      }

  if (load)
    i = maj(caml_callback(*caml_named_value("parser"),
			  caml_copy_string(save)),&e, &bb_bl, &bb_wh, mem, &dead,
            &joueur, marque, i);

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
		if ((event.button.x >= psave1.x)&&(event.button.x <= psave1.x+LO)&&(event.button.y >= psave1.y)&&(event.button.y <= psave1.y+LA))
		  {
		  /**************************/
		    /* Twilight Sparkle */
		 /**************************/
		      pgn_out(mem, "partie", ia);
		  }
		if ((event.button.x >= pretour.x)&&(event.button.x <= pretour.x+LO)&&(event.button.y >= pretour.y)&&(event.button.y <= pretour.y+LA))
		  {
		    return 1;
		  }
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
	    if (cfin == NULL)
	      {
		cinipr = NULL;
		cini = NULL;
		decolo_sdl(&e);
	      }
	    else
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
                          i = update(&e, cini,cfin, &bb_bl, &bb_wh, mem, 
                                     &dead, &joueur, marque, i);
                          if(ia)
                        {
                              /*la fction retourn 2 bb(A DECLARER) (un des 2 est un nb)*/
                              /*
                                bb = fct(bb_wh, bb_bl); ou ptet que c l'inverse
                                for (xsx=0;xsx < 8;xsx++)
    for(dcd=0;dcd < 8;dcd++)
      {
	b_tmp = get_case(xsx, dcd);
	if ((b_tmp & bb[1])!= 0)
            {xsx_a = xsx; dcd_a = dcd}
      if ((b_tmp & bb_bl[bb[0]])!= 0)
            {xsx_d = xsx; dcd_d = dcd}
      }
	  update(&e,&(e->mat[7-xsx_d][dcd_d]),&(e->mat[7-xsx_a][dcd_a]),mem,&dead,&joueur,marque,i);
      
                              */
                              printf("ia\n");
                        }
                          if(soc)
                        {
                              rezo->di = cini->num;
                              rezo->dj =((int)cini->let)-65;
                              rezo->ai =cfin->num;
                              rezo->aj =((int)cfin->let)-65;
                              send(soc, rezo, sizeof(struct res),0);
                              recv(soc, rezo, sizeof(struct res),0);
                              cini = &(e.mat[rezo->di][rezo->dj]);
                              cfin = &(e.mat[rezo->ai][rezo->aj]);
                              i = update(&e, cini,cfin, &bb_bl, &bb_wh, mem,
				     &dead, &joueur, marque, i);
                        }
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
			  i = update(&e, cinipr,cfin, &bb_bl, &bb_wh, mem,
				     &dead, &joueur, marque, i);
                  if(soc)
                        {
                              rezo->di = cinipr->num;
                              rezo->dj =((int)cinipr->let)-65;
                              rezo->ai =cfin->num;
                              rezo->aj =((int)cfin->let)-65;
                              printf("Envoi\n");
                              send(soc, rezo, sizeof(struct res),0);
                              printf("Recoit\n");
                              recv(soc, rezo, sizeof(struct res),0);
                              cinipr = &(e.mat[rezo->di][rezo->dj]);
                              cfin = &(e.mat[rezo->ai][rezo->aj]);
                               printf("%i%c\n",cfin->num,cfin->let);
                              i = update(&e, cinipr,cfin, &bb_bl, &bb_wh, mem,
				     &dead, &joueur, marque, i);
                               
                        }
			  cini = NULL;
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

  for (; i >= 0;i--)
    {
      printf("lol\n");
      if (mem[i])
	free(mem[i]);
    }
  free(mem);
  return 0;
}
