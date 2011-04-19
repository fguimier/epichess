/*	file :	b_deplace.c	*/
/*	created by :	moya_a	*/
/*	date :	Tue Apr 19 16:30:25 CEST 2011	*/


#include "b_deplace.h"

bitboard deplace_poss (bitboard init, bitboard (*fct)(bitboard), bitboard l, bitboard a)
{
    a=a;
	if ((init | l) == l)
		return init;
	init = fct(init);
	return init | deplace_poss(init, fct, l, a);
}
bitboard deplace_pawn (bitboard init, bitboard l, bitboard a, int col)
{
    bitboard        place, lim;
    if (col)
    {
        place = 0x000000000000FF00;
        if ((init | place) == place)
            lim = init << 16;
        else
            lim = init << 8;
        return deplace_poss(init, deplace_b, lim | l, a);
    }
    else
    {
        place = 0x00FF000000000000;
        if ((init | place) == place)
            lim = init >> 16;
        else
            lim = init >> 8;
        return  deplace_poss(init, deplace_f, lim | l, a);
    }
}

