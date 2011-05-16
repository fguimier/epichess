#include "pgn_read.h"
/* retourne la premiere tour dans le champ de vision depuis cas qui pourrait
   y aller*/
t_list search_tower(struct s_echiquier *e, struct s_case *cas, enum color colo,
		    struct s_bb *bb_bl, struct s_bb *bb_wh)
{
  int i = cas->num;
  int j = cas->let - 65;
  t_list possi = NULL;
  bitboard pos_i, coup_pos,all;
  e=e;
  pos_i = get_case(i,j);
  all = bb_bl->pieces[0]|bb_wh->pieces[0];
  /***********on renvoie quoi ?************************/
  if (colo == blanc)
      coup_pos = dep_rook(pos_i,bb_bl->pieces[0],all);/*bit de la tour, bit des ennemi, bit des all*/
  else
      coup_pos = dep_rook(pos_i,bb_wh->pieces[0],all);
  
  return possi;
}

t_list search_horse(struct s_echiquier *e, struct s_case *cas)
{
    /*huhuhuhu*/
    e =e;cas=cas;
    return NULL;
}
