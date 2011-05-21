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

void maj(value v)
{
    printf("%s",String_val(v));
}
