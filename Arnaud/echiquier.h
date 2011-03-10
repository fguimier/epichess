#ifndef __ECHIQUIER_H
#define __ECHIQUIER_H

#include "pieces.h"

struct s_case
{
    p_piece                 p;
    enum color              c;
    int                     num;
    char                    let;
};
struct s_echiquier
{
    struct s_case                  mat[8][8];
};

struct s_echiquier  echiquier_create ( );
void                echiquier_init ( struct s_echiquier * );
p_piece             echiquier_getPiece ( struct s_echiquier, int, int );
#endif

