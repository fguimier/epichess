#ifndef __PIECES_H
#define __PIECES_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


/* definition des donnees */
enum name {pion, tour, fou, cavalier, dame, roi};
enum color {blanc, noir, bleu, rouge};

typedef struct s_piece      *p_piece;


struct s_piece
{
  enum name               piece_name;
    enum color              piece_color;
  SDL_Surface               *piece_sprite;
};


/* constructeurs des pieces */
p_piece   piece_create ( enum color, enum name );
#endif
