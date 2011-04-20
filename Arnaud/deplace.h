#ifndef __DEPLACE_H
#define __DEPLACE_H


#include "echiquier.h"

/*enum    move = {ligne, colonne, diagonnale1, diagonale2};*/


struct s_deplace
{
  /*size_t      deplace_nbcase;
    enum move   deplace_move;
    p_deplace   deplace_next;*/
  int verti;
  int hori;
};

void deplace_pos_possible (struct s_echiquier *, int, int, struct s_deplace *);
void petit_roque (struct s_echiquier *, int, int);
void grand_roque (struct s_echiquier *, int, int);
void deplacement (struct s_echiquier *, int, int, int, int, struct s_deplace *);


#endif
