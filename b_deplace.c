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
    if (deplace_b(init) & a)
        poss |= deplace_b(init);
    if (deplace_f(init) & a)
        poss |= deplace_f(init);
    if (deplace_r(init) & a)
        poss |= deplace_r(init);
    if (deplace_l(init) & a)
        poss |= deplace_l(init);
    if (deplace_br(init) & a)
        poss |= deplace_br(init);
    if (deplace_bl(init) & a)
        poss |= deplace_bl(init);
    if (deplace_fr(init) & a)
        poss |= deplace_fr(init);
    if (deplace_fl(init) & a)
        poss |= deplace_fl(init);
    return poss;
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
bitboard deplace_poss (bitboard init, bitboard (*fct)(bitboard), bitboard l, bitboard a)
{
	if ((init & l) || (fct(init) & a))
		return init;
	init = fct(init);
	return init | deplace_poss(init, fct, l, a);
}

