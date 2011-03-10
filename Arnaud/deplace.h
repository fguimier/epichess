#ifndef __DEPLACE_H
#define __DEPLACE_H

enum    move = {ligne, colonne, diagonnale1, diagonale2};

typedef 
struct s_deplace
{
    size_t      deplace_nbcase;
    enum move   deplace_move;
    p_deplace   deplace_next;
}

#endif
