#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <stdint.h>

typedef uint64_t   bitboard;

struct s_bb {
    bitboard pieces [17];
    bitboard possib [17];
    int color;
};

/* definition des couleurs */
#define BLACK       0
#define WHITE       1

/* definition des bordures de l'echiquier */
#define RIGHT_B     0x8080808080808080
#define LEFT_B      0x0101010101010101
#define BOTT_B      0x00000000000000FF
#define TOP_B       0XFF00000000000000
#define ROUND_B (RIGHT_B | LEFT_B | TOP_B | BOTT_B)

/* pieces blanches de bases */
#define WHITE_P1    0x0000000000000100
#define WHITE_P2    0x0000000000000200
#define WHITE_P3    0x0000000000000400
#define WHITE_P4    0x0000000000000800
#define WHITE_P5    0x0000000000001000
#define WHITE_P6    0x0000000000002000
#define WHITE_P7    0x0000000000004000
#define WHITE_P8    0x0000000000008000

#define WHITE_T1    0x0000000000000001
#define WHITE_T2    0x0000000000000080
#define WHITE_B1    0x0000000000000002
#define WHITE_B2    0x0000000000000040
#define WHITE_C1    0x0000000000000004
#define WHITE_C2    0x0000000000000020
#define WHITE_Q     0x0000000000000010
#define WHITE_K     0x0000000000000008

/* pieces noires de base */
#define BLACK_P1    0x0001000000000000
#define BLACK_P2    0x0002000000000000
#define BLACK_P3    0x0004000000000000
#define BLACK_P4    0x0008000000000000
#define BLACK_P5    0x0010000000000000
#define BLACK_P6    0x0020000000000000
#define BLACK_P7    0x0040000000000000
#define BLACK_P8    0x0080000000000000

#define BLACK_T1    0x0100000000000000
#define BLACK_T2    0x8000000000000000
#define BLACK_B1    0x0200000000000000
#define BLACK_B2    0x4000000000000000
#define BLACK_C1    0x0400000000000000
#define BLACK_C2    0x2000000000000000
#define BLACK_Q     0x1000000000000000
#define BLACK_K     0x0800000000000000

/* deplacement et attaque des cavaliers */
bitboard deplace_knight_br( bitboard );
bitboard deplace_knight_bl( bitboard );
bitboard deplace_knight_fr( bitboard );
bitboard deplace_knight_fl( bitboard );
bitboard deplace_knight_rb( bitboard );
bitboard deplace_knight_lb( bitboard );
bitboard deplace_knight_rf( bitboard );
bitboard deplace_knight_lf( bitboard );
/* deplacements et attaques du generaux */
bitboard deplace_r( bitboard );
bitboard deplace_l( bitboard );
bitboard deplace_b( bitboard );
bitboard deplace_f( bitboard );
bitboard deplace_br( bitboard );
bitboard deplace_bl( bitboard );
bitboard deplace_fr( bitboard );
bitboard deplace_fl( bitboard );

/* fonction qui affiche l echiquier */
bitboard get_case (int, int);
void print_ech (bitboard );
void populate (struct s_bb *, int);

#endif
