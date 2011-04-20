#ifndef __PIECES_H
#define __PIECES_H

/* definition des donnees */
enum name {pion, tour, fou, cavalier, dame, roi};
enum color {blanc, noir};

typedef struct s_piece      *p_piece;


struct s_piece
{
    enum name               piece_name;
    enum color              piece_color;
};


/* constructeurs des pieces */
p_piece   piece_create ( enum color, enum name );
#endif
