#ifndef __ECHIQUIER_H
#define __ECHIQUIER_H

#include "pieces.h"
#include "list.h"
#include "bitboards.h"
#include "b_deplace.h"

struct s_case
{
    p_piece                 p;
    enum color              c;
  enum color                bleu;
    int                     num;
    char                    let;
  SDL_Surface               *sprite;
};
struct s_echiquier
{
    struct s_case                  mat[8][8];
  SDL_Surface                      *screen;
};

struct s_echiquier  echiquier_create ( );
void                echiquier_init ( struct s_echiquier * );
p_piece             echiquier_getPiece ( struct s_echiquier, int, int );
void                ech_print (struct s_echiquier *);
#endif

