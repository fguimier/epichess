#include <stdlib.h>
#include <stdio.h>

#include "bitboards.h"


/* deplacement et attaque des cavaliers */
static inline bitboard deplace_knight_br( bitboard x ) 
{
	return x<<17;
}
static inline bitboard deplace_knight_bl( bitboard x ) 
{
	return x<<15;
}
static inline bitboard deplace_knight_fr( bitboard x ) 
{
	return x>>15;
}
static inline bitboard deplace_knight_fl( bitboard x ) 
{
	return x>>17;
}
static inline bitboard deplace_knight_rb( bitboard x ) 
{
	return x<<10;
}
static inline bitboard deplace_knight_lb( bitboard x ) 
{
	return x<<6;
}
static inline bitboard deplace_knight_rf( bitboard x ) 
{
	return x>>6;
}
static inline bitboard deplace_knight_lf( bitboard x ) 
{
	return x>>10;
}
/* deplacements et attaques du generaux */
static inline bitboard deplace_r( bitboard x ) 
{
	return x<<1;
}
static inline bitboard deplace_l( bitboard x ) 
{
	return x>>1;
}
static inline bitboard deplace_b( bitboard x ) 
{
	return x<<8;
}
static inline bitboard deplace_f( bitboard x ) 
{
	return x>>8;
}
static inline bitboard deplace_br( bitboard x ) 
{
	return x<<9;
}
static inline bitboard deplace_bl( bitboard x ) 
{
	return x<<7;
}
static inline bitboard deplace_fr( bitboard x ) 
{
	return x>>7;
}
static inline bitboard deplace_fl( bitboard x ) 
{
	return x>>9;
}

void print_ech (bitboard b)
{
    int i;
    bitboard mask = 1;
    for (i = 0; i < 64; i++)
    {
        if (i%8 == 0)
            printf("\n");
        if (i > 0)
            mask = mask<<1;

        if (mask & b)
            printf("1 ");
        else
            printf("0 ");
    }
    printf("\n"); 
}
bitboard deplace_poss (bitboard init, bitboard (*fct)(bitboard), bitboard l, bitboard e)
{	
	if ((init | l) == l || (init | e) == e)
		return init;
	init = fct(init);
	return init | deplace_poss(init, fct, l, e);
}

int main ()
{
    bitboard b, poss, e;
	b = 0x02;
	b = deplace_b(b);
	e = deplace_b(b);
	print_ech(b);
	poss = deplace_poss(b, deplace_b, BOTT_L, e);
	print_ech(poss);
	poss |= deplace_poss(b, deplace_l, LEFT_L, e);
	print_ech(poss);
	poss |= deplace_poss(b, deplace_r, RIGHT_L, e);
	print_ech(poss);
	poss |= deplace_poss(b, deplace_f, TOP_L, e);
	print_ech(poss);
	return 0;
}
