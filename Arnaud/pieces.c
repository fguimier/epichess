
#include <stdlib.h>

#include "pieces.h"

/* cree un nouvelle piece de nom (pion, roi, dame...) n et de couleur c, 
 * renvoie un pointeur sur la nouvelle piece
 * */
p_piece piece_create (enum color c, enum name n)
{
    p_piece             p = NULL;
    p = malloc (sizeof (struct s_piece));
    if (!p)
        return p;
    p->piece_name = n;
    p->piece_color = c;
    return p;
}


