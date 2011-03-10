#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "echiquier.h"
#include "pieces.h"

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

int main ()
{
    struct s_echiquier            e;

    e = echiquier_create();
    echiquier_init ( &e );
    ech_print( &e );
    return 0;    
}
