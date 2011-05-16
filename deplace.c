#include <stdlib.h>

#include "pieces.h"
#include "deplace.h"
#include "echiquier.h"

/*le tableau doit etre initialise a au moins 90 cases et la fonction va retourner toutes les cases vers ou le pion situe sur la case a la ligne l et la colonne c  de l'echiquier e peut aller. chaque case du tableau est une structure deux entiers : la position sur l'echiquier*/

void deplace_pos_possible (struct s_echiquier *e, int l, int c, struct s_deplace *pos_possible)
{
  int                i,j;

  for (i = 0; i < 60; i ++)
    {
      pos_possible[i].hori = l;
      pos_possible[i].verti = c;
    }

  switch (e->mat[l][c].p->piece_name)

    {

       /*==========================*/
      /* *** deplacement pion *** */
     /*==========================*/

    case pion :

      if (e->mat[l][c].p->piece_color == blanc)
	{
	  if (l+1 <= 7)
	    {
	      if (c+1 <= 7 &&e->mat[l+1][c+1].p != NULL &&  e->mat[l+1][c+1].p->piece_color == noir)
		{
		  pos_possible[0].verti = (pos_possible[0].verti + 1);
		  pos_possible[0].hori = (pos_possible[0].hori + 1);
		}
	      if (c-1 >= 0 &&e->mat[l+1][c-1].p != NULL &&  e->mat[l+1][c-1].p->piece_color == noir)
		{
		  pos_possible[1].verti = (pos_possible[1].verti - 1);
		  pos_possible[1].hori = (pos_possible[1].hori + 1);
		}
	    }
	}
      if (e->mat[l][c].p->piece_color == noir)
	{
	  if (l-1 >= 0)
	    {
	      if (c-1 >= 0 && e->mat[l-1][c-1].p != NULL && e->mat[l-1][c-1].p->piece_color == blanc)
		{
		  pos_possible[2].verti = (pos_possible[2].verti - 1);
		  pos_possible[2].hori = (pos_possible[2].hori - 1);
		}
	      if (c+1 <= 7 && e->mat[l-1][c+1].p != NULL && e->mat[l-1][c+1].p->piece_color == blanc)
		{
		  pos_possible[3].verti = (pos_possible[3].verti + 1);
		  pos_possible[3].hori = (pos_possible[3].hori - 1);
		}
	    }
	}

      if (l == 1 && e->mat[l][c].p->piece_color == blanc)
	{
	  if (e->mat[l+1][c].p == NULL)
	    {
	      pos_possible[5].hori = (pos_possible[5].hori + 1);
	      if (e->mat[l+2][c].p == NULL)
		pos_possible[6].hori = (pos_possible[6].hori + 2);
	    }
	}
      else if (l == 6 && e->mat[l][c].p->piece_color == noir)
	{
	  if (e->mat[l-1][c].p == NULL)
	    {
	      pos_possible[5].hori = (pos_possible[5].hori - 1);
	      if (e->mat[l-2][c].p == NULL)
		pos_possible[6].hori = (pos_possible[6].hori - 2);
	    }
	}
      else
	{
	  if (l+1 <= 7 && l-1 >= 0)
	    {
	      if ((e->mat[l+1][c].p == NULL && e->mat[l][c].p->piece_color == blanc) || (e->mat[l-1][c].p == NULL && e->mat[l][c].p->piece_color == noir))
		{
		  if ( e->mat[l][c].p->piece_color == blanc)
		    pos_possible[7].hori = (pos_possible[7].hori + 1);
		  else
		    pos_possible[7].hori = (pos_possible[7].hori - 1);
		}
	    }
	}

      break;

       /*==========================*/
      /* *** deplacement tour *** */
     /*==========================*/

    case tour :

	j = 1;

	for (i = 0; i < 7; i++)
	  {
	    if (l+j > 7)
	      break;
	    if (e->mat[l+j][c].p == NULL)
	      {
		pos_possible[i].hori = (pos_possible[i].hori + j);
	      }
	    else if (e->mat[l+j][c].p->piece_color != e->mat[l][c].p->piece_color)
	      {
		pos_possible[i].hori = (pos_possible[i].hori + j);
		break;
	      }
	    else
	      break;
	    j++;
	  }

	j = 1;

	for (i = 7; i < 14; i++)
          {
	    if (c+j > 7)
	      break;
	    if (e->mat[l][c+j].p == NULL)
	      {
		pos_possible[i].verti = (pos_possible[i].verti + j);
	      }
	    else if (e->mat[l][c+j].p->piece_color != e->mat[l][c].p->piece_color)
	      {
		pos_possible[i].verti = (pos_possible[i].verti + j);
		break;
	      }
	    else
	      break;
            j++;
	  }

	j = -1;

	for (i = 14; i < 21; i++)
	  {
	    if (l+j < 0)
	      break;
	    if (e->mat[l+j][c].p == NULL)
	      {
		pos_possible[i].hori = (pos_possible[i].hori + j);
	      }
	    else if (e->mat[l+j][c].p->piece_color != e->mat[l][c].p->piece_color)
	      {
		pos_possible[i].hori = (pos_possible[i].hori + j);
		break;
	      }
	    else
	      break;
	    j--;
          }

	j = -1;

	for (i = 21; i < 28; i++)
	  {
	    if (c+j < 0)
	      break;
	    if (e->mat[l][c+j].p == NULL)
	      {
		pos_possible[i].verti = (pos_possible[i].verti + j);
	      }
	    else if (e->mat[l][c+j].p->piece_color != e->mat[l][c].p->piece_color)
	      {
                pos_possible[i].verti = (pos_possible[i].verti + j);
                break;
              }
            else
              break;
	    j--;
          }

	break;

	 /*=========================*/
	/* *** deplacement fou *** */
       /*=========================*/

    case fou :

      j = 1;
      printf ("fou !");
      for (i = 0; i < 7; i++)
	{
	  printf ("foufou1");
	  if (l+j > 7 || c+j > 7)
	    break;
	  if (e->mat[l+j][c+j].p == NULL)
	    {
	      pos_possible[i].hori = (pos_possible[i].hori + j);
	      pos_possible[i].verti = (pos_possible[i].verti + j);
	    }
	  else if (e->mat[l+j][c+j].p->piece_color != e->mat[l][c].p->piece_color)
	    {
	      pos_possible[i].hori = pos_possible[i].hori + j;
              pos_possible[i].verti = pos_possible[i].verti + j;
	      break;
	    }
	    else
	      break;
	  j++;
	}

      j = -1;

      for (i = 7; i < 14; i++)
	{
	  printf ("foufou2");
	  if (l+j < 0 || c+j < 0)
	    break;
	  if (e->mat[l+j][c+j].p == NULL)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti + j) ;
            }
          else if (e->mat[l+j][c+j].p->piece_color != e->mat[l][c].p->piece_color)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti + j) ;
              break;
            }
	    else
	      break;
	  j--;
	}

      j = 1;

      for (i = 14; i < 21; i++)
	{
	  printf ("foufou3");
	  if (l+j > 7 || c-j < 0)
	    break;
	  if (e->mat[l+j][c-j].p == NULL)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti - j) ;
            }
          else if (e->mat[l+j][c-j].p->piece_color != e->mat[l][c].p->piece_color)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti - j) ;
              break;
            }
	    else
	      break;
	    j++;
	}

      j = 1;

      for (i = 21; i < 28; i++)
	{
	  printf ("foufou4");
	  if (l-j < 0 || c+j > 7)
	    break;
	  if (e->mat[l-j][c+j].p == NULL)
	    {
	      pos_possible[i].hori = (pos_possible[i].hori - j) ;
	      pos_possible[i].verti = (pos_possible[i].verti + j) ;
	    }
	  else if (e->mat[l-j][c+j].p->piece_color != e->mat[l][c].p->piece_color)
	    {
	      pos_possible[i].hori = (pos_possible[i].hori - j) ;
              pos_possible[i].verti = (pos_possible[i].verti + j) ;
	      break;
	    }
	  else
	    break;
	  j++;
	}

      break;

       /*==========================*/
      /* *** deplacement dame *** */
     /*==========================*/

    case dame :

      j = 1;

      for (i = 0; i < 7; i++)
	{
	  if (l+j > 7)
	    break;
	  if ( e->mat[l+j][c].p == NULL)
	    pos_possible[i].hori = (pos_possible[i].hori + j) ;
	  else if (e->mat[l+j][c].p->piece_color != e->mat[l][c].p->piece_color)
	    {
	      pos_possible[i].hori = (pos_possible[i].hori + j) ;
	      break;
	    }
	  else
	    {
	      break;
	    }
	  j++;
	}

      j = 1;

      for (i = 7; i < 14; i++)
	{
	  if (c+j > 7)
	    break;
	  if (e->mat[l][c+j].p == NULL)
	    pos_possible[i].verti = (pos_possible[i].verti + j) ;
	  else if (e->mat[l][c+j].p->piece_color != e->mat[l][c].p->piece_color)
	    {
	      pos_possible[i].verti = (pos_possible[i].verti + j) ;
	      break;
	    }
	  else
	    break;
	  j++;
	}

      j = -1;

      for (i = 14; i < 21; i++)
	{
	  if (l+j < 0)
	    break;
	  if (e->mat[l+j][c].p == NULL)
	    pos_possible[i].hori = (pos_possible[i].hori + j) ;
	  else if (e->mat[l+j][c].p->piece_color != e->mat[l][c].p->piece_color)
	    {
	      pos_possible[i].hori = (pos_possible[i].hori + j) ;
	      break;
	    }
	  else
	    break;
	  j--;
	}

      j = -1;

      for (i = 21; i < 28; i++)
	{
	  if (c+j < 0)
	    break;
	  if (e->mat[l][c+j].p == NULL)
	    pos_possible[i].verti = (pos_possible[i].verti + j) ;
	  else if (e->mat[l][c+j].p->piece_color != e->mat[l][c].p->piece_color)
	    {
	      pos_possible[i].verti = (pos_possible[i].verti + j) ;
	      break;
	    }
	  else
	    break;
	  j--;
	}

      j = 1;

      for (i = 28; i < 35; i++)
	{
	  if (l+j > 7 || c+j > 7)
	    break;
          if (e->mat[l+j][c+j].p == NULL)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti + j) ;
            }
          else if (e->mat[l+j][c+j].p->piece_color != e->mat[l][c].p->piece_color)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
	      pos_possible[i].verti = (pos_possible[i].verti + j) ;
              break;
            }
	  else
	    break;
	  j++;
	}

      j = -1;

      for (i = 35; i < 42; i++)
        {
	  if (l+j < 0 || c+j < 0)
	    break;
          if (e->mat[l+j][c+j].p == NULL)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti + j) ;
            }
          else if (e->mat[l+j][c+j].p->piece_color != e->mat[l][c].p->piece_color)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
	      pos_possible[i].verti = (pos_possible[i].verti + j) ;
              break;
            }
	  else
	    break;
	  j--;
	}

      j = 1;

      for (i = 42; i < 49; i++)
        {
	  if (l+j > 7 || c-j < 0)
	    break;
          if (e->mat[l+j][c-j].p == NULL)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti - j) ;
            }
          else if (e->mat[l+j][c-j].p->piece_color != e->mat[l][c].p->piece_color)
            {
              pos_possible[i].hori = (pos_possible[i].hori + j) ;
              pos_possible[i].verti = (pos_possible[i].verti - j) ;
              break;
            }
	  else
	    break;
	  j++;
        }

      j = 1;

      for (i = 49; i < 56; i++)
        {
	  if (l-j < 0 || c+j > 7)
	    break;
          if (e->mat[l-j][c+j].p == NULL)
            {
              pos_possible[i].hori = (pos_possible[i].hori - j) ;
              pos_possible[i].verti = (pos_possible[i].verti + j) ;
	    }
          else if ( e->mat[l-j][c+j].p->piece_color != e->mat[l][c].p->piece_color)
            {
              pos_possible[i].hori = (pos_possible[i].hori - j) ;
              pos_possible[i].verti = (pos_possible[i].verti + j) ;
              break;
            }
          else
            break;
          j++;
	}

      break;

       /*==========================*/
      /* *** deplacement roi ***  */
     /*==========================*/

    case roi :

      j = 1;

      if (e->mat[l][c].p->piece_color == blanc)
	{

	  if (l+j <= 7 && c-j >= 0)
	    {
	      if ((e->mat[l+j][c-j].p == NULL) || (e->mat[l+j][c-j].p != NULL && e->mat[l+j][c-j].p->piece_color == noir))
		{
		  pos_possible[0].hori = (pos_possible[0].hori + j) ;
		  pos_possible[0].verti = (pos_possible[0].verti - j) ;
		}
	    }

	  if  (c-j >= 0)
	    {
	      if ((e->mat[l][c-j].p == NULL) || (e->mat[l][c-j].p != NULL && e->mat[l][c-j].p->piece_color == noir))
		{
		  pos_possible[1].verti = (pos_possible[1].verti - j) ;
		}
	    }

	  if (l-j >= 0 && c-j >= 0)
	    {
	      if ((e->mat[l-j][c-j].p == NULL) || (e->mat[l-j][c-j].p != NULL && e->mat[l-j][c-j].p->piece_color == noir))
		{
		  pos_possible[2].hori = (pos_possible[2].hori - j) ;
		  pos_possible[2].verti = (pos_possible[2].verti - j) ;
		}
	    }

	  if (l-j >= 0)
	    {
	      if ((e->mat[l-j][c].p == NULL) || (e->mat[l-j][c].p != NULL && e->mat[l-j][c].p->piece_color == noir))
		{
		  pos_possible[3].hori = (pos_possible[3].hori - j) ;
		}
	    }

	  if (l-j >= 0 && c+j <= 7)
	    {
	      if ((e->mat[l-j][c+j].p == NULL) || (e->mat[l-j][c+j].p != NULL && e->mat[l-j][c+j].p->piece_color == noir))
		{
		  pos_possible[4].hori = (pos_possible[4].hori - j) ;
		  pos_possible[4].verti = (pos_possible[4].verti + j) ;
		}
	    }

	  if (c+j <= 7)
	    {
	      if ((e->mat[l][c+j].p == NULL) || (e->mat[l][c+j].p != NULL && e->mat[l][c+j].p->piece_color == noir))
		{
		  pos_possible[5].verti = (pos_possible[5].verti + j) ;
		}
	    }

	  if (l+j <= 7 &&  c+j <= 7)
	    {
	      if ((e->mat[l+j][c+j].p == NULL) || (e->mat[l+j][c+j].p != NULL && e->mat[l+j][c+j].p->piece_color == noir))
		{
		  pos_possible[6].hori = (pos_possible[6].hori + j) ;
              pos_possible[6].verti = (pos_possible[6].verti + j) ;
		}
	    }

	  if (l+j <= 7)
	    {
	      if ((e->mat[l+j][c].p == NULL) ||(e->mat[l+j][c].p != NULL && e->mat[l+j][c].p->piece_color == noir))
		{
		  pos_possible[7].hori = (pos_possible[7].hori + j) ;
		}
	    }
	}

      else
        {
          if (l+j <= 7 && c-j >= 0)
            {
              if ((e->mat[l+j][c-j].p == NULL) || (e->mat[l+j][c-j].p != NULL && e->mat[l+j][c-j].p->piece_color == blanc))
                {
                  pos_possible[0].hori = (pos_possible[0].hori + j) ;
                  pos_possible[0].verti = (pos_possible[0].verti - j) ;
                }
            }

          if  (c-j >= 0)
            {
              if ((e->mat[l][c-j].p == NULL) || (e->mat[l][c-j].p != NULL && e->mat[l][c-j].p->piece_color == blanc))
                {
                  pos_possible[1].verti = (pos_possible[1].verti - j) ;
                }
            }

          if (l-j >= 0 && c-j >= 0)
            {
              if ((e->mat[l-j][c-j].p == NULL) || (e->mat[l-j][c-j].p != NULL && e->mat[l-j][c-j].p->piece_color == blanc))
                {
                  pos_possible[2].hori = (pos_possible[2].hori - j) ;
                  pos_possible[2].verti = (pos_possible[2].verti - j) ;
                }
            }

          if (l-j >= 0)
            {
              if ((e->mat[l-j][c].p == NULL) || (e->mat[l-j][c].p != NULL && e->mat[l-j][c].p->piece_color == blanc))
                {
                  pos_possible[3].hori = (pos_possible[3].hori - j) ;
                }
            }

          if (l-j >= 0 && c+j <= 7)
            {
              if ((e->mat[l-j][c+j].p == NULL) || (e->mat[l-j][c+j].p != NULL && e->mat[l-j][c+j].p->piece_color == blanc))
                {
                  pos_possible[4].hori = (pos_possible[4].hori - j) ;
                  pos_possible[4].verti = (pos_possible[4].verti + j) ;
                }
            }

	  if (c+j <= 7)
            {
              if ((e->mat[l][c+j].p == NULL) || (e->mat[l][c+j].p != NULL && e->mat[l][c+j].p->piece_color == blanc))
                {
                  pos_possible[5].verti = (pos_possible[5].verti + j) ;
                }
            }

          if (l+j <= 7 && c+j <= 7)
            {
              if ((e->mat[l+j][c+j].p == NULL) || (e->mat[l+j][c+j].p != NULL && e->mat[l+j][c+j].p->piece_color == blanc))
                {
                  pos_possible[6].hori = (pos_possible[6].hori + j) ;
		  pos_possible[6].verti = (pos_possible[6].verti + j) ;
                }
            }

          if (l+j <= 7)
            {
              if ((e->mat[l+j][c].p == NULL) ||(e->mat[l+j][c].p != NULL && e->mat[l+j][c].p->piece_color == blanc))
                {
                  pos_possible[7].hori = (pos_possible[7].hori + j) ;
                }
            }
	}

      break;

       /*===============================*/
      /* *** deplacement cavalier ***  */
     /*===============================*/

    case cavalier :

      j = 1;

      if (l-2 >= 0 && c-j >= 0)
	{
	  if (e->mat[l-2][c-j].p == NULL || (e->mat[l-2][c-j].p->piece_color != e->mat[l][c].p->piece_color))
	    {

	      pos_possible[0].hori = (pos_possible[0].hori - 2) ;
	      pos_possible[0].verti = (pos_possible[0].verti - j) ;
	    }
	}

      if (l+2 <= 7 && c+j <= 7)
	{
	  if (e->mat[l+2][c+j].p == NULL || (e->mat[l+2][c+j].p != NULL && e->mat[l+2][c+j].p->piece_color != e->mat[l][c].p->piece_color))
	    {
              pos_possible[1].hori = (pos_possible[1].hori + 2) ;
              pos_possible[1].verti = (pos_possible[1].verti + j) ;
            }
	}

      j = -1;

      if (l-2 >= 0 && c-j <= 7)
	{
	  if (e->mat[l-2][c-j].p == NULL || (e->mat[l-2][c-j].p != NULL && e->mat[l-2][c-j].p->piece_color != e->mat[l][c].p->piece_color))
	    {
	      pos_possible[2].hori = (pos_possible[2].hori - 2) ;
	      pos_possible[2].verti = (pos_possible[2].verti - j) ;
	    }
	}

      if (l+2 <= 7 && c+j >= 0)
	{
	  if (e->mat[l+2][c+j].p == NULL || (e->mat[l+2][c+j].p != NULL && e->mat[l+2][c+j].p->piece_color != e->mat[l][c].p->piece_color))
	    {
              pos_possible[3].hori = (pos_possible[3].hori + 2) ;
              pos_possible[3].verti = (pos_possible[3].verti + j) ;
            }
	}

      j = 1;

      if (l+j <= 7 && c+2 <= 7)
	{
	  if (e->mat[l+j][c+2].p == NULL || (e->mat[l+j][c+2].p != NULL && e->mat[l+j][c+2].p->piece_color != e->mat[l][c].p->piece_color))
	    {
	      pos_possible[4].hori = (pos_possible[4].hori + j) ;
	      pos_possible[4].verti = (pos_possible[4].verti + 2) ;
	    }
	}

      if (l-j >= 0 && c+2 <= 7)
	{
	  if (e->mat[l-j][c+2].p == NULL || (e->mat[l-j][c+2].p != NULL && e->mat[l-j][c+2].p->piece_color != e->mat[l][c].p->piece_color))
	    {
              pos_possible[5].hori = (pos_possible[5].hori - j) ;
              pos_possible[5].verti = (pos_possible[5].verti + 2) ;
            }
	}

      j = -1;

      if (l+j >= 0 && c-2 >= 0)
	{
	  if (e->mat[l+j][c-2].p == NULL || (e->mat[l+j][c-2].p != NULL && e->mat[l+j][c-2].p->piece_color != e->mat[l][c].p->piece_color))
	    {
	      pos_possible[6].hori = (pos_possible[6].hori + j);
	      pos_possible[6].verti = (pos_possible[6].verti - 2);
	    }
	}

      if (l-j <= 7  && c-2 >= 0)
	{
	  if (e->mat[l-j][c-2].p == NULL || (e->mat[l-j][c-2].p != NULL && e->mat[l-j][c-2].p->piece_color != e->mat[l][c].p->piece_color))
	    {
              pos_possible[7].hori = (pos_possible[7].hori - j);
              pos_possible[7].verti = (pos_possible[7].verti - 2);
	    }
	}
      break;
    }

    ech_print(e);
}

void petit_roque (struct s_echiquier *e, int l, int c)
{
    e=e;l=l;c=c;
/*
  if (e->mat[l][c].p->piece_color == blanc)
    {
      e->mat[l][c].p = NULL ;
      e->mat[l][c-2].p = piece_create (blanc, roi);

      e->mat[l][c-3].p = NULL;
      e->mat[l][c-1].p = piece_create (blanc, tour);
    }
  else
    {
      e->mat[l][c].p = NULL ;
      e->mat[l][c-2].p = piece_create (noir, roi);

      e->mat[l][c-3].p = NULL;
      e->mat[l][c-1].p = piece_create (noir, tour);
      }*/
}

void grand_roque (struct s_echiquier *e, int l, int c)
{
    e=e;l=l;c=c;
/*
  if (e->mat[l][c].p->piece_color == blanc)
    {
      e->mat[l][c].p = NULL ;
      e->mat[l][c-2].p = piece_create (blanc, roi);

      e->mat[l][c-4].p = NULL;
      e->mat[l][c-1].p = piece_create (blanc, tour);
    }
  else
    {
      e->mat[l][c].p = NULL ;
      e->mat[l][c-2].p = piece_create (noir, roi);

      e->mat[l][c-4].p = NULL;
      e->mat[l][c-1].p = piece_create (noir, tour);
      }*/
}

t_list deplacement (struct s_echiquier *e, int l_init, int c_init, int l_final, int c_final, t_list dead)
{
  printf("%i,%i -> %i,%i\n",l_init,c_init,l_final,c_final);
  if (e->mat[l_final][c_final].p)
    dead = add(e->mat[l_final][c_final].p, dead);
  e->mat[l_final][c_final].p = e->mat[l_init][c_init].p;
  e->mat[l_init][c_init].p = NULL;
  /*ech_print(e);*/
  return dead;
}
