#ifndef BITBOARD_H_
#define BITBOARD_H_

typedef u_int64_t bitboard;

#define RIGHT_B 0x8080808080808080
#define LEFT_B  0x0101010101010101
#define TOP_B   0x00000000000000FF
#define BOTT_B  0XFF00000000000000

#define ROUND_B (RIGHT_B | LEFT_B | TOP_B | BOTT_B)

/* pieces blanches de bases */
#define WHITE_P 0x000000000000FF00
#define WHITE_T 0x0000000000000081
#define WHITE_B 0x0000000000000042
#define WHITE_C 0x0000000000000024
#define WHITE_Q 0x0000000000000008
#define WHITE_K 0x0000000000000010
/* pieces noires de base */
#define BLACK_P 0x00FF000000000000
#define BLACK_T 0x8100000000000000
#define BLACK_B 0x4200000000000000
#define BLACK_C 0x2400000000000000
#define BLACK_Q 0x1000000000000000
#define BLACK_K 0x0800000000000000

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

#endif
