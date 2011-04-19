/*	file :	b_deplace.c	*/
/*	created by :	moya_a	*/
/*	date :	Tue Apr 19 16:30:25 CEST 2011	*/


#include "b_deplace.h"
bitboard dep_queen (bitboard init,  bitboard e, bitboard a)
{
    bitboard poss;
    poss = deplace_poss (init, deplace_b, e | BOTT_B, a);
    poss |= deplace_poss (init, deplace_f, e | TOP_B, a);
    poss |= deplace_poss (init, deplace_r, e | RIGHT_B, a);
    poss |= deplace_poss (init, deplace_l, e | LEFT_B, a);
    poss |= deplace_poss (init, deplace_br, e | BOTT_B | RIGHT_B, a);
    poss |= deplace_poss (init, deplace_bl, e | BOTT_B | LEFT_B, a);
    poss |= deplace_poss (init, deplace_fr, e | TOP_B | RIGHT_B, a);
    poss |= deplace_poss (init, deplace_fl, e | TOP_B | LEFT_B, a);
    return ((~init) & poss);
}
bitboard dep_rook (bitboard init,  bitboard e, bitboard a)
{
    bitboard poss;
    poss = deplace_poss (init, deplace_b, e | BOTT_B, a);
    poss |= deplace_poss (init, deplace_f, e | TOP_B, a);
    poss |= deplace_poss (init, deplace_r, e | RIGHT_B, a);
    poss |= deplace_poss (init, deplace_l, e | LEFT_B, a);
    return ((~init) & poss);
}
bitboard dep_bishop (bitboard init,  bitboard e, bitboard a)
{
    bitboard poss;
    poss = deplace_poss (init, deplace_br, e | BOTT_B | RIGHT_B, a);
    poss |= deplace_poss (init, deplace_bl, e | BOTT_B | LEFT_B, a);
    poss |= deplace_poss (init, deplace_fr, e | TOP_B | RIGHT_B, a);
    poss |= deplace_poss (init, deplace_fl, e | TOP_B | LEFT_B, a);
    return ((~init) & poss);
}
bitboard dep_king (bitboard init, bitboard a)
{
    bitboard poss = 0x00;
    poss |= deplace_b(init);
    poss |= deplace_f(init);
    poss |= deplace_r(init);
    poss |= deplace_l(init);
    poss |= deplace_br(init);
    poss |= deplace_bl(init);
    poss |= deplace_fr(init);
    poss |= deplace_fl(init);
    
    return poss & ~a;
}
bitboard dep_pawn (bitboard init, bitboard l, bitboard a, int col)
{
    bitboard        place, lim;
    if (col)
    {
        place = 0x000000000000FF00;
        if ((init | place) == place)
            lim = init << 16;
        else
            lim = init << 8;
        return deplace_poss(init, deplace_f, lim | l, a);
    }
    else
    {
        place = 0x00FF000000000000;
        if ((init | place) == place)
            lim = init >> 16;
        else
            lim = init >> 8;
        return  deplace_poss(init, deplace_b, lim | l, a);
    }
}
bitboard deplace_poss (bitboard init, bitboard (*fct)(bitboard), bitboard l, bitboard a)
{
    a &= ~init;
	if ((init & l) || (fct(init) & a))
		return init;
	init = fct(init);
	return init | deplace_poss(init, fct, l, a);
}

