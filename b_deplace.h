/*	file :	b_deplace.h	*/
/*	created by :	moya_a	*/
/*	date :	Tue Apr 19 16:30:25 CEST 2011	*/

#ifndef B_DEPLACE_H_
#define B_DEPLACE_H_

#include "bitboards.h"
typedef struct s_forth *forth;
struct s_forth
{
    struct s_bb        *black;
    struct s_bb        *white;
    int         col;
};

/* calcul les deplacements possibles,
 * prend en param :
 * - le bitboard ou est la piece
 * - le pointeur sur la fonction de deplacement
 * - les bitboards d arret, ex: les bords de l echiquier, le bitboard enemi
 * renvoie un bitboard avec les deplacement possibles
 */
bitboard deplace_poss ( bitboard, bitboard (*fct)(bitboard), bitboard, bitboard );
bitboard dep_knight (bitboard, bitboard);
bitboard dep_pawn (bitboard, bitboard, bitboard, int);
bitboard dep_queen (bitboard,  bitboard, bitboard);
bitboard dep_rook (bitboard,  bitboard, bitboard);
bitboard dep_bishop (bitboard,  bitboard, bitboard);
bitboard dep_king (bitboard, bitboard);

void calc_all_dep (struct s_bb *, struct s_bb *);
#endif 
