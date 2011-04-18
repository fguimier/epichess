#include "pgn_read.h"
/* retourne la premiere tour dans le champ de vision depuis cas qui pourrait
   y aller*/
t_list search_tower(struct s_echiquier *e, struct s_case *cas, enum color colo)
{
  int i = cas->num;
  int j = cas->let - 65;
  int ii = i;
  int jj = j;
  t_list pos = NULL;

  i++;
  while(i < 8 && !e->mat[i][j]->p)
      i++;
  if (i < 8 && cas->p->piece_name == tour &&
      e->mat[i][j]->p.piece_color == colo)
    pos = add(pos, e->mat[i][j]->c);
  i = ii;

  i--;
  while(i > 0 && !e->mat[i][j]->p)
    i--;
  if (i > 0 && cas->p->piece_name == tour &&
      e->mat[i][j]->p.piece_color == colo)
    pos = add(pos, e->mat[i][j]->c);
  i = ii;

  j++;
  while(j < 8 && !e->mat[i][j]->p)
    j++;
  if (j < 8 && cas->p->piece_name == tour &&
      e->mat[i][j]->p.piece_color == colo)
    pos = add(pos, e->mat[i][j]->c);
  j = jj;

  j--;
  while(j > 0 && !e->mat[i][j]->p)
    j--;
  if (j > 0 && cas->p->piece_name == tour &&
      e->mat[i][j]->p.piece_color == colo)
    pos = add(pos, e->mat[i][j]->c);

  return pos;
}

t_list search_horse(struct s_echiquier *e, struct s_case *cas)
{
  int i = cas->num;
  int j = cas->let - 65;
  int ii = i;
  int jj = j;
  t_list pos = NULL;

  if (i < 65)
    pos = add(pos, e->mat[i][j]->c);
}
