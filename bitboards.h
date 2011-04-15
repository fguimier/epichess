#include <stdlib.h>
#include <stdio.h>


/* deplacement et attaque des cavaliers */
static inline bitboard deplace_knight_br( bitboard );
static inline bitboard deplace_knight_bl( bitboard );
static inline bitboard deplace_knight_fr( bitboard );
static inline bitboard deplace_knight_fl( bitboard );
static inline bitboard deplace_knight_rb( bitboard );
static inline bitboard deplace_knight_lb( bitboard );
static inline bitboard deplace_knight_rf( bitboard );
static inline bitboard deplace_knight_lf( bitboard );
/* deplacements et attaques du generaux */
static inline bitboard deplace_r( bitboard );
static inline bitboard deplace_l( bitboard );
static inline bitboard deplace_b( bitboard );
static inline bitboard deplace_f( bitboard );
static inline bitboard deplace_br( bitboard );
static inline bitboard deplace_bl( bitboard );
static inline bitboard deplace_fr( bitboard );
static inline bitboard deplace_fl( bitboard );
/* fonction qui affiche l echiquier */
void print_ech (bitboard );
/* calcul les deplacements possibles,
 * prend en param :
 * - le bitboard ou est la piece
 * - le pointeur sur la fonction de deplacement
 * - les bitboards d arret, ex: les bords de l echiquier, le bitboard enemi
 * renvoie un bitboard avec les deplacement possibles
 */
bitboard deplace_poss ( bitboard, bitboard (*fct)(bitboard), bitboard, bitboard );
