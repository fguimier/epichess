#include <stdlib.h>
#include <stdio.h>

#include "bitboards.h"

/* deplacement et attaque des cavaliers */
inline bitboard deplace_knight_br( bitboard x )
{
	return x<<17;
}
inline bitboard deplace_knight_bl( bitboard x )
{
	return x<<15;
}
inline bitboard deplace_knight_fr( bitboard x )
{
	return x>>15;
}
inline bitboard deplace_knight_fl( bitboard x )
{
	return x>>17;
}
inline bitboard deplace_knight_rb( bitboard x )
{
	return x<<10;
}
inline bitboard deplace_knight_lb( bitboard x )
{
	return x<<6;
}
inline bitboard deplace_knight_rf( bitboard x )
{
	return x>>6;
}
inline bitboard deplace_knight_lf( bitboard x )
{
	return x>>10;
}
/* deplacements et attaques generaux */
inline bitboard deplace_r( bitboard x )
{
	return x<<1;
}
inline bitboard deplace_l( bitboard x )
{
	return x>>1;
}
inline bitboard deplace_b( bitboard x )
{
	return x<<8;
}
inline bitboard deplace_f( bitboard x )
{
	return x>>8;
}
inline bitboard deplace_br( bitboard x)
{
	return x<<9;
}
inline bitboard deplace_bl( bitboard x )
{
	return x<<7;
}
inline bitboard deplace_fr( bitboard x )
{
	return x>>7;
}
inline bitboard deplace_fl( bitboard x )
{
	return x>>9;
}


void print_ech (bitboard b)
{
    int         i, j=8, k=0;
    char        prtn [8][8];
    bitboard mask = 1;
    for (i = 0; i < 64; i++)
    {
        if (i%8 == 0)
        {
            j--;
            k=0;
        }
        if (i > 0)
            mask = mask<<1;

        if (mask & b)
            prtn[k][j]='1';
        else
            prtn[k][j]='0';
        k++;
    }   
    for (i=0; i < 8; i++)
    {
        for(j=0; j < 8 ; j++) printf("%c ", prtn [j][i]);
        printf ("\n");
    }
    printf ("\n");
}

void pop_white (struct s_bb *tb)
{
    int             i = 1;
    tb->pieces[0] = 0x00;
    tb->pieces[1] = WHITE_P1;
    tb->pieces[2] = WHITE_P2;
    tb->pieces[3] = WHITE_P3;
    tb->pieces[4] = WHITE_P4;
    tb->pieces[5] = WHITE_P5;
    tb->pieces[6] = WHITE_P6;
    tb->pieces[7] = WHITE_P7;
    tb->pieces[8] = WHITE_P8;
    tb->pieces[9] = WHITE_T1;
    tb->pieces[10] = WHITE_T2;
    tb->pieces[11] = WHITE_B1;
    tb->pieces[12] = WHITE_B2;
    tb->pieces[13] = WHITE_C1;
    tb->pieces[14] = WHITE_C2;
    tb->pieces[15] = WHITE_Q;
    tb->pieces[16] = WHITE_K;
    for (; i < 17; i++)
        tb->pieces[0] = tb->pieces[0] | tb->pieces[i];
}
void pop_black (struct s_bb *tb)
{
    int             i = 1;
    tb->pieces[0] = 0x00;
    tb->pieces[1] = BLACK_P1;
    tb->pieces[2] = BLACK_P2;
    tb->pieces[3] = BLACK_P3;
    tb->pieces[4] = BLACK_P4;
    tb->pieces[5] = BLACK_P5;
    tb->pieces[6] = BLACK_P6;
    tb->pieces[7] = BLACK_P7;
    tb->pieces[8] = BLACK_P8;
    tb->pieces[9] = BLACK_T1;
    tb->pieces[10] = BLACK_T2;
    tb->pieces[11] = BLACK_B1;
    tb->pieces[12] = BLACK_B2;
    tb->pieces[13] = BLACK_C1;
    tb->pieces[14] = BLACK_C2;
    tb->pieces[15] = BLACK_Q;
    tb->pieces[16] = BLACK_K;
    for (; i < 17; i++)
        tb->pieces[0] = tb->pieces[0] | tb->pieces[i];

}
void populate (struct s_bb *tb, int col)
{
    if (col)
        pop_white(tb);
    else
        pop_black(tb);
}

