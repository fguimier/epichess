#include <stdlib.h>

#include "echiquier.h"

/* si la couleur etait noire, elle devient rouge. Et vise et versa */
enum color          switchColor ( enum color col )
{
    if (col == blanc)
        col = noir;
    else
        col = blanc;
    return col;
}

/* cree un nouvel echiquier vide */
struct s_echiquier  echiquier_create ( )
{
    int                     i, j;
    p_piece                 p = NULL;
    enum color              col = blanc;
    struct s_echiquier      e;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            e.mat[i][j].p = p;
            e.mat[i][j].c = col;
            e.mat[i][j].num = i;
            e.mat[i][j].let = 'A' + j;
            col = switchColor (col);
        }
        col = switchColor (col);
    }

    return e;

}

/* renvoie le pointeur sur la piece a la case de ligne l et de colonne c
 * renvoie null s'il n'y a pas de piece
 * */
p_piece               echiquier_getPiece ( struct s_echiquier e, int l, int c )
{
    return e.mat[l][c].p;
}

/* initialise l'echiquier avec les pieces a leur place de debut de partie
 * modifie l'echiquier pointe par e
 */
void                echiquier_init ( struct s_echiquier *e )
{
    enum name               initOrder [8] = {
                        tour, cavalier, fou, roi, 
                        dame, fou, cavalier, tour};
    enum name               pio = pion;
    int                     i;

    for (i = 0; i < 8; i++)
    {
        e->mat[0][i].p = piece_create (blanc, initOrder[i],i+9);
	e->mat[1][i].p = piece_create (blanc, pio,i+1);
	e->mat[6][i].p = piece_create (noir, pio,i+1);
	if (initOrder [i] == roi)
	    e->mat[7][i].p = piece_create (noir, initOrder[i+1],i+9);
	else if ( initOrder[i] == dame)
	    e->mat[7][i].p = piece_create (noir, initOrder[i-1],i+9);
	else
	    e->mat[7][i].p = piece_create (noir, initOrder[i],i+9);
    }
}


char printC (p_piece p)
{
	if (p->piece_color == blanc)
		return 'W';
		return 'B';
	}
	char printP (p_piece p)
	{
		if (p->piece_name == tour)
		return 'T';
	if (p->piece_name == cavalier)
		return 'C';
		if (p->piece_name == fou)
	return 'F';
		if (p->piece_name == dame)
		return 'D';
	if (p->piece_name == roi)
		return 'R';
	if (p->piece_name == pion)
		return 'P';
	return '\0';
}

void ech_print (struct s_echiquier *e)
{
	int             i, j, z;
	p_piece         p = NULL;
	for (i = 0; i < 8; i++)
	{
		for (z = 0; z < 8; z++) printf("_______");
		printf("\n");
		for (j = 0; j < 8; j++)
		{
			p = e->mat[i][j].p;
			if (p)
				printf ("| %c,%c |", printP(p), printC(p));
			else
				printf("|     |");
			fflush(stdout);
		}
	printf("\n");
	fflush(stdout);
	}
}
