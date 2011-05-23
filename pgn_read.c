#include "pgn_read.h"
/*fonction dégueulasse qui renvoie la liste des cases à partir d'un bitboard 
  donné*/
t_list b2c(struct s_echiquier *e, bitboard bb)
{
  int i,j;
  bitboard b,c;
  t_list res = NULL;

  c = 0x0000000000000000;
  for (i=0;i < 8;i++)
    for(j=0;j < 8;j++)
      {
	b = get_case(i, j);
	if ((b & bb)!= c)
	  res = add((void *)&(e->mat[7-i][j]),res);
      }
  return res;
}

/* retourne les tours dans le champ de vision depuis cas qui pourrait
   y aller*/
t_list search_tower(struct s_echiquier *e, struct s_case *cini,
                    struct s_case *cfin, enum color colo,
                    struct s_bb *bb_bl, struct s_bb *bb_wh)
{
  int i = cini->num;
  int j = cini->let - 65;
  t_list possi = NULL;
  bitboard pos_i, pos_f, coup_pos,all,zero,res;

  pos_i = get_case(7-i,j);
  if (!cfin)
    printf("lol\n");
  i = cfin->num;
  j = cfin->let - 65;
  pos_f = get_case(7-i, j);
  zero = 0x0000000000000000;
  res = zero;
  printf("pos_i:\n");
  print_ech(pos_i);
  all = bb_bl->pieces[0]|bb_wh->pieces[0];
  /***********on renvoie quoi ?************************/
  if (colo == blanc)
    {
      if ((bb_wh->pieces[9]==zero)|(bb_wh->pieces[10] ==zero))
	return NULL;
      if (bb_wh->pieces[9]==pos_i)
	{
	  coup_pos = dep_rook(bb_wh->pieces[10],bb_bl->pieces[0],all);
	  if ((coup_pos&pos_f)!=zero)
	    res = res | bb_wh->pieces[10];
	}
      else
	{
	  coup_pos = dep_rook(bb_wh->pieces[9],bb_bl->pieces[0],all);
	  if ((coup_pos&pos_f)!=zero)
	    res = res | bb_wh->pieces[9];
	}
    }
  else
    {
      if ((bb_bl->pieces[9]==zero)|(bb_bl->pieces[10] ==zero))
	return NULL;
      if (bb_bl->pieces[9]==pos_i)
	{
	  coup_pos = dep_rook(bb_bl->pieces[10],bb_wh->pieces[0],all);
	  if ((coup_pos&pos_f)!=zero)
	    res = res | bb_bl->pieces[10];
	}
      else
	{
	  coup_pos = dep_rook(bb_bl->pieces[9],bb_wh->pieces[0],all);
	  if ((coup_pos&pos_f)!=zero)
	    res = res | bb_bl->pieces[9];
	}
    }
  print_ech(res);
  possi = b2c(e, res);
  return possi;
}

t_list search_horse(struct s_echiquier *e, struct s_case *cini,
                    struct s_case *cfin, enum color colo,
                    struct s_bb *bb_bl, struct s_bb *bb_wh)
{
  int i = cini->num;
  int j = cini->let - 65;
  t_list possi = NULL;
  bitboard pos_i, pos_f, coup_pos,all,zero,res;
  coup_pos = 0x5;
  colo =colo;

  pos_i = get_case(7-i,j);
  if (!cfin)
    printf("lol\n");
  i = cfin->num;
  j = cfin->let - 65;
  pos_f = get_case(7-i, j);
  zero = 0x0000000000000000;
  res = zero;
  printf("pos_i:\n");
  print_ech(pos_i);
  all = bb_bl->pieces[0]|bb_wh->pieces[0];
  /***********on renvoie quoi ?************************/
  /*    if (colo == blanc)
        {
            if ((bb_wh->pieces[13]==zero)|(bb_wh->pieces[14] ==zero))
                return NULL;
            if (bb_wh->pieces[13]==pos_i)
                {
                    coup_pos = dep_knight(
                        bb_wh->pieces[14],bb_bl->pieces[0],all);
                    if ((coup_pos&pos_f)!=zero)
                        res = res | bb_wh->pieces[14];
                }
            else
                {
                    coup_pos = dep_knight(
                        bb_wh->pieces[13],bb_bl->pieces[0],all);
                    if ((coup_pos&pos_f)!=zero)
                        res = res | bb_wh->pieces[13];
                }
        }
    else
        {
            if ((bb_bl->pieces[13]==zero)|(bb_bl->pieces[14] ==zero))
                return NULL;
            if (bb_bl->pieces[13]==pos_i)
                {
                    coup_pos = dep_knight(
                        bb_bl->pieces[14],bb_wh->pieces[0],all);
                    if ((coup_pos&pos_f)!=zero)
		    res = res | bb_wh->pieces[13];
		    }
		    }
		    else
		    {
            if ((bb_bl->pieces[13]==zero)|(bb_bl->pieces[14] ==zero))
                return NULL;
            if (bb_bl->pieces[13]==pos_i)
                {
                    coup_pos = dep_knight(
                        bb_bl->pieces[14],bb_wh->pieces[0],all);
                    if ((coup_pos&pos_f)!=zero)
                        res = res | bb_bl->pieces[14];
                }
            else
                {
                    coup_pos = dep_knight(
                        bb_bl->pieces[13],bb_wh->pieces[0],all);
                    if ((coup_pos&pos_f)!=zero)
                        res = res | bb_bl->pieces[13];
                }
                }*/
  print_ech(res);
  possi = b2c(e, res);
  return possi;
    
}

/*t_list search_bishop(struct s_echiquier *e, struct s_case *cini,
                    struct s_case *cfin, enum color colo,
                    struct s_bb *bb_bl, struct s_bb *bb_wh)
{
  int i = cini->num;
  int j = cini->let - 65;
  t_list possi = NULL;
  bitboard pos_i, pos_f, coup_pos,all,zero,res;

  pos_i = get_case(7-i,j);
  if (!cfin)
    printf("lol\n");
  i = cfin->num;
  j = cfin->let - 65;
  pos_f = get_case(7-i, j);
  zero = 0x0000000000000000;
  res = zero;
  printf("pos_i:\n");
  print_ech(pos_i);
  all = bb_bl->pieces[0]|bb_wh->pieces[0];
  **********on renvoie quoi ?***********************
  if (colo == blanc)
    {
      if ((bb_wh->pieces[11]==zero)|(bb_wh->pieces[12] ==zero))
        return NULL;
      if (bb_wh->pieces[11]==pos_i)
        {
          coup_pos = dep_bishop(bb_wh->pieces[12],bb_bl->pieces[0],all);
          if ((coup_pos&pos_f)!=zero)
            res = res | bb_wh->pieces[10];
        }
      else
        {
          coup_pos = dep_bishop(bb_wh->pieces[11],bb_bl->pieces[0],all);
          if ((coup_pos&pos_f)!=zero)
            res = res | bb_wh->pieces[9];
        }
    }
  else
    {
      if ((bb_bl->pieces[11]==zero)|(bb_bl->pieces[12] ==zero))
        return NULL;
      if (bb_bl->pieces[11]==pos_i)
        {
          coup_pos = dep_bishop(bb_bl->pieces[12],bb_wh->pieces[0],all);
          if ((coup_pos&pos_f)!=zero)
            res = res | bb_bl->pieces[12];
        }
      else
        {
          coup_pos = dep_bishop(bb_bl->pieces[11],bb_wh->pieces[0],all);
          if ((coup_pos&pos_f)!=zero)
            res = res | bb_bl->pieces[11];
        }
    }
  print_ech(res);
  possi = b2c(e, res);
  return possi;
}
*/








void updates_b(struct s_bb *bb_bl, struct s_bb *bb_wh, struct s_case *cini,
	       struct s_case *cfin)
{
  bitboard fin = get_case(7-cfin->num,(cfin->let-65));
  bitboard cin = get_case(7-cini->num,(cini->let-65));
  int i = 1;
  int j = 1;
  printf("quatre\n");
  if (cini->p->piece_color == blanc)
    {
      while (bb_wh->pieces[i] != cin)
	i++;
      bb_wh->pieces[0] = bb_wh->pieces[0] & ~bb_wh->pieces[i];
      bb_wh->pieces[0] = bb_wh->pieces[0] | fin;
      if (cfin->p)
	{
	  while (bb_bl->pieces[j] != fin)
	    j++;
	  bb_bl->pieces[j]= 0x0000000000000000;
	  bb_bl->pieces[0]=bb_bl->pieces[0] & ~fin;
	}
      bb_wh->pieces[i] = fin;
    }
  else
    {
      while (bb_bl->pieces[i] != cin)
	i++;
      bb_bl->pieces[0] = bb_bl->pieces[0] & ~bb_bl->pieces[i];
      bb_bl->pieces[0] = bb_bl->pieces[0] | fin;
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
  calc_all_dep(bb_wh, bb_bl);
}

void updates_e(struct s_echiquier *e, struct s_case *cini,struct s_case *cfin,
               t_list *dead, enum color *joueur, SDL_Surface *marque)
{
  int mort = 0;
  if (cfin->p)
    mort = 1;
  printf("cinco\n");
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
}

void *search_cini(struct s_echiquier *e,char *coup, int j,
		  enum color *joueur, struct s_bb *bb_wh,
		  struct s_bb *bb_bl, bitboard bfin)
{
  bitboard given, zero, all;
  struct s_bb *bb, *bb_e;
  int i = 0;
  t_list res = NULL;
  zero = 0x0000000000000000;
  given = zero;
  all = bb_bl->pieces[0] | bb_wh->pieces[0];
  j-=3;
  if (*joueur == blanc)
    {
      bb = bb_wh;
      bb_e = bb_bl;
    }
  else
    {
      bb = bb_bl;
      bb_e = bb_wh;
    }
  printf("coup[j] : %c\n",coup[j]);
  if (coup[j]=='x')
    j--;
  if (coup[j] >'0' && coup[j]<'9')
    {
      for(;i < 9;i++)
	given |= get_case(i, coup[j]-'1'); 
      j--;
    }
  if (coup[j] >='a' && coup[j]<'i')
    {
      for(;i < 9;i++)
	given |= get_case(coup[j]-'a',i);
      j--;
    }
  printf("tertio\n");
  switch(coup[j])
    {
    case 'K':
      res = b2c(e, bb->pieces[16]);
      break;
    case 'Q':
      res = b2c(e, bb->pieces[15]);
      break;
    case 'B':
      if ((bb->pieces[12] != zero) &&
	  ((given == zero && (bfin & bb->possib[12]) != zero)||
	   (given !=zero && ((bb->pieces[12] | given) == given))))
	res = b2c(e, bb->pieces[12]);
      else
	res = b2c(e, bb->pieces[11]);
      break;
    case 'R':
      printf("Tour\n");
      print_ech(bb_e->pieces[0]);
      print_ech(all);
      print_ech(bfin);
      print_ech(bb->pieces[9]);
      print_ech(bb->possib[9]);
      print_ech(bb->possib[10]);
      print_ech(given);
      if (bb->pieces[9] != zero)
	{
	  if ((given == zero && ((bfin & bb->possib[9]) != zero))||
	      (given !=zero && ((bb->pieces[9] | given) == given)))
	    res = b2c(e, bb->pieces[9]);
	}
      else
	res = b2c(e, bb->pieces[10]);
      break;
    case 'N':
      if ((bb->pieces[13] != zero) &&
	  (((given == zero && bfin & bb->possib[13]) != zero)||
	   (given !=zero && ((bb->pieces[13] | given) == given))))
	res = b2c(e, bb->pieces[13]);
      else
	res = b2c(e, bb->pieces[14]);
    default :
      for(i=1;i <9;i++)
	{
	  printf("Pion\n");
	  print_ech(bb_e->pieces[0]);
	  print_ech(all);
	  print_ech(bb->possib[i]);
	  print_ech(given);
	  if(bb->pieces[i] != zero &&
	     ((bfin & bb->possib[i]) !=zero))
	    if ((given == zero)||
		(((given != zero) && ((bb->pieces[i] | given) == given))))
	      {
		res = b2c(e, bb->pieces[i]);
		break;
	      }
	}
      break;
    }
  return (res->val);
}

int updates(char * coup, struct s_echiquier *e,struct s_bb *bb_bl, 
	    struct s_bb *bb_wh, char **mem, t_list *dead,
	    enum color *joueur, SDL_Surface *marque, int i)
{
  struct s_case *cini, *cfin;
  int j = 0;
  int h = 0;
  bitboard bfin;
  /*trouver les cini et cfin*/
  printf("Primo\n");
  if(*joueur == blanc)
    {
      mem[i] = malloc(30);
      while(coup[j])
	{
	  mem[i][j] = coup[j];
	  j++;
	}
      mem[i][j] = ' ';
      mem[i][j+1] = 0;
      cfin = &(e->mat[7-coup[j-1]+'1'][coup[j-2]-'a']);
      printf("cfin : %i,%i\n",coup[j-2]-'a',coup[j-1]-'1');
      print_ech(get_case(7-cfin->num,cfin->let-'A'));
      bfin = get_case(7-cfin->num,cfin->let-'A');
      printf("Deuxio\n");
      cini = (struct s_case *)search_cini(e, coup, j, joueur, bb_wh, bb_bl, bfin);
    }
  else
    {
      while(mem[i][j])
	j++;
      while(coup[h])
	{
	  mem[i][j] = coup[h];
	  j++;
	  h++;
	}
      mem[i][j] = ' ';
      mem[i][j+1] = 0;
      cfin = &(e->mat[7-coup[h-1]+'1'][coup[h-2]-'a']);
      printf("cfin : %i,%i\n",coup[h-2]-'a',coup[h-1]-'1');
      bfin = get_case(7-cfin->num,cfin->let-'A');
      print_ech(bfin);
      cini = (struct s_case *)search_cini(e, coup, h, joueur, bb_wh, bb_bl, bfin);
      i++;
    }
  updates_b(bb_bl, bb_wh, cini, cfin);
  updates_e(e, cini, cfin, dead, joueur, marque);
  return i;
}

int maj(value v,struct s_echiquier *e, struct s_bb *bb_bl, struct s_bb *bb_wh,
        char **mem, t_list *dead, enum color *joueur,
        SDL_Surface *marque, int i)
{
  if (Is_long(v))
    return i;
  i = updates(String_val(Field(v,0)),e,bb_bl,bb_wh,mem,dead,joueur,marque, i);
  printf("i :%i",i);
  i = maj(Field(v,1),e,bb_bl,bb_wh,mem,dead,joueur,marque,i);
  return i;
}
