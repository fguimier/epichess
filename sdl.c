#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "sdl.h"

#define h 50
#define deca 120

/* initialise la sdl et charge toutes les sprites sauf les pieces */
void init_sdl(struct s_echiquier *e, SDL_Surface *ecran)
{
  size_t i, j;
  SDL_Rect position;

  
  e->screen = ecran;
  SDL_FillRect(e->screen, NULL, SDL_MapRGB(e->screen->format, 100, 100, 100));

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	/* les cases */

	  e->mat[i][j].sprite =
	    SDL_CreateRGBSurface(SDL_HWSURFACE, h, h, 32, 0, 0, 0, 0);
	  if (e->mat[i][j].c == blanc)
	    SDL_FillRect(e->mat[i][j].sprite,
			 NULL, SDL_MapRGB(e->screen->format, 0, 0, 0));
	  else
	    SDL_FillRect(e->mat[i][j].sprite,
			 NULL, SDL_MapRGB(e->screen->format, 255, 255, 255));
	  position.x = i * h + deca;
	  position.y = j * h;
	  SDL_BlitSurface(e->mat[i][j].sprite, NULL, e->screen, &position);
      }

  SDL_Flip(e->screen);
}

/* initialise le sprite du pion */
void init_piece_sdl (struct s_echiquier *e, int i, int j)
{
  SDL_Rect pos;

  pos.y = h * i;
  pos.x = h * j + deca;

  switch (e->mat[i][j].p->piece_name)
    {
    case pion :
      if (e->mat[i][j].p->piece_color == blanc)
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/BP.png");
      else
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/WP.png");
      break;
    case cavalier :
      if (e->mat[i][j].p->piece_color == blanc)
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/BC.png");
      else
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/WC.png");
      break;
    case tour :
      if (e->mat[i][j].p->piece_color == blanc)
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/BT.png");
      else
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/WT.png");
      break;
    case fou :
      if (e->mat[i][j].p->piece_color == blanc)
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/BF.png");
      else
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/WF.png");
      break;
    case dame :
      if (e->mat[i][j].p->piece_color == blanc)
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/BD.png");
      else
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/WD.png");
      break;
    case roi :
      if (e->mat[i][j].p->piece_color == blanc)
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/BK.png");
      else
	e->mat[i][j].p->piece_sprite = IMG_Load("sprites/WK.png");
      break;
    }
   SDL_BlitSurface(e->mat[i][j].p->piece_sprite, NULL, e->screen, &pos);
   SDL_Flip(e->screen);
}

/* change la position dún sprite
   IMPORTANT : les x et y font references au cases de léchiquier pas */
void change_postion(struct s_echiquier *e, int i, int j)
{
  SDL_Rect pos;
    if (e->mat[i][j].p)
    {
      pos.y = h * i;
      pos.x = h * j + deca;
      SDL_FreeSurface(e->mat[i][j].p->piece_sprite);
      init_piece_sdl(e, i, j);
      SDL_BlitSurface(e->mat[i][j].p->piece_sprite, NULL, e->screen, &pos);
      SDL_Flip(e->screen);
    }
    else
      {
	pos.y = h * i;
	pos.x = h * j + deca;
	SDL_BlitSurface(e->mat[i][j].sprite, NULL, e->screen, &pos);
	SDL_Flip(e->screen);
      }
}


/* remet léchiquier dans son etat normal sans tout recharger */
void reset(struct s_echiquier *e)
{
  e=e;
}

struct s_case *check_case_sdl(int x, int y, struct s_echiquier *e)
{
  size_t i,j;

  if ((x < h*8+deca)&&(x > deca))
    {
	j = (x-deca) / h;
      if ((y < 8*h)&&(y > 0))
	{
	  i = y / h;
	  printf("Case selected\n");
	  return (&(e->mat[i][j]));
	}
    }
  printf("Case not selected\n");
  return NULL;
}

int colo_sdl(struct s_echiquier *e, struct s_deplace tab[])
{
  size_t k = 0;
  int i, j, count;
  SDL_Rect position;

  count = 0;
  while (k < 60)
    {
      i = tab[k].hori;
      j = tab[k].verti;
      if (i != tab[59].hori || j != tab[59].verti)
	{
	    count++;
	  SDL_FreeSurface(e->mat[i][j].sprite);
	  e->mat[i][j].sprite =
	    SDL_CreateRGBSurface(SDL_HWSURFACE, h, h, 32, 0, 0, 0, 0);
	  if (e->mat[i][j].p)
	    {
	      e->mat[i][j].bleu = rouge;
	      if (e->mat[i][j].c == blanc)
		SDL_FillRect(e->mat[i][j].sprite,
			     NULL, SDL_MapRGB(e->screen->format, 125, 0, 0));
	      else
		SDL_FillRect(e->mat[i][j].sprite,
			     NULL, SDL_MapRGB(e->screen->format, 255, 125, 125));
	    }
	  else
	    {
	      e->mat[i][j].bleu = bleu;
	      if (e->mat[i][j].c == blanc)
		SDL_FillRect(e->mat[i][j].sprite,
			     NULL, SDL_MapRGB(e->screen->format, 0, 0, 125));
	      else
		SDL_FillRect(e->mat[i][j].sprite,
			     NULL, SDL_MapRGB(e->screen->format, 125, 125, 255));
	    }
	  position.x = j * h + deca;
	  position.y = i * h;
	  SDL_BlitSurface(e->mat[i][j].sprite, NULL, e->screen, &position);
	  if (e->mat[i][j].p)
	    SDL_BlitSurface(e->mat[i][j].p->piece_sprite, NULL, e->screen,
			    &position);
	}
      k++;
    }
  SDL_Flip(e->screen);
  return count;
}

SDL_Surface *init_marque_sdl()
{
    return (IMG_Load("sprites/marque.png"));
}

void marque_sdl(int x, int y, struct s_echiquier *e,SDL_Surface * s)
{
    SDL_Rect pos;

    pos.y = h * x;
    pos.x = h * y + deca;

    SDL_BlitSurface(s, NULL, e->screen,
		    &pos);
    SDL_Flip(e->screen);
}

void blit_dead_sdl(t_list dead, struct s_echiquier *e)
{
  SDL_Rect pos;
  t_list copy = dead;
  enum color c = ((struct s_piece*)dead->val)->piece_color;
  printf("Blit des morts\n");
  pos.x = pos.y = 0;
  pos.y -= h;
  while (copy)
    {
      if (((struct s_piece*)copy->val)->piece_color == c)
	pos.y += h;
      copy = copy->next;
    }
  if (((struct s_piece*)dead->val)->piece_color == blanc)
    pos.x = 0;
  else
    pos.x = h * 8 + deca;
  if (pos.y >= h * 8)
    {
      pos.y -= h * 8;
      pos.x += h;
    }
  printf("%i,%i\n",pos.x,pos.y);
  SDL_BlitSurface(((struct s_piece*)dead->val)->piece_sprite, NULL, e->screen,
		  &pos);
  SDL_Flip(e->screen);
}

void decolo_sdl (struct s_echiquier *e)
{
  size_t i, j;
  SDL_Rect position;

  for (i = 0; i < 8;i++)
    for(j = 0; j < 8;j++)
      {
	e->mat[i][j].bleu = blanc;
	e->mat[i][j].sprite =
	  SDL_CreateRGBSurface(SDL_HWSURFACE, h, h, 32, 0, 0, 0, 0);
	if (e->mat[i][j].c == blanc)
	  SDL_FillRect(e->mat[i][j].sprite,
		       NULL, SDL_MapRGB(e->screen->format, 0, 0, 0));
	else
	  SDL_FillRect(e->mat[i][j].sprite,
		       NULL, SDL_MapRGB(e->screen->format, 255, 255, 255));
	position.y = i * h;
	position.x = j * h + deca;
	SDL_BlitSurface(e->mat[i][j].sprite, NULL, e->screen, &position);
	if (e->mat[i][j].p)
	    SDL_BlitSurface(e->mat[i][j].p->piece_sprite, NULL, e->screen,
			    &position);
      }
  SDL_Flip(e->screen);
}


/* on libere tout comme il faut */
void free_sdl(struct s_echiquier *e)
{
  size_t i,j;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	printf("FU-%i-%i\n",i,j);
	SDL_FreeSurface(e->mat[i][j].sprite);
	if (e->mat[i][j].p)
	  {
	    SDL_FreeSurface(e->mat[i][j].p->piece_sprite);
	    printf("SION\n");
	  }
      }
}
