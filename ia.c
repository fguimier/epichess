#include "ia.h"
#include "b_deplace.h"

tree create_tree (struct s_bb possible_white, struct s_bb possible_black)
{
  tree n;

  n = malloc (sizeof (struct s_tree));
  n->son = NULL;
  n->brother = NULL;
  n->father = NULL;
  n->poids = 0;
  n->possible_white = possible_white;
  n->possible_black = possible_black;

  return (n);
}

tree add_son (tree node, tree t)
{
  if (t == NULL)
    {
      t = node;
    }
  else
    {
      t->son = node;
      node->father = t;
    }
   return (t);
}

tree add_bro (tree node, tree t)
{
   tree tmp = t;
    
  if (t == NULL)
    {
      t = node;
    }
  else
    { 
        while (tmp->brother != NULL)
            {
                tmp = tmp -> brother; 
            }
           tmp->brother = node;
           node->father = tmp->father; 
           
	}
  return (t);
}

int max (int a, int b)
{
  if (a > b)
    return (a);
  else
    return (b);
}

int profondeur (tree t)
{
  int h;
  tree l;

  h = -1;
  l = t->son;

  while (l != NULL)
    {
      h = max (h, profondeur (l));
      l = l->brother;
    }
  return (h+1);
}

void updates_ia(struct s_bb *bb_bl, struct s_bb *bb_wh,
	       bitboard bini,bitboard bfin, int color)
{
  int i = 1;
  int j = 1;
  /*printf("update\n");*/
  if (color == WHITE)
    {
      while (bb_wh->pieces[i] != bini)
	i++;
      bb_wh->pieces[0] = bb_wh->pieces[0] & ~bb_wh->pieces[i];
      bb_wh->pieces[0] = bb_wh->pieces[0] | bfin;
      
     for (j = 1; j < 17; j ++)
      {
        if (bb_bl->pieces[j] == bfin)
            {
              /*print_ech (bb_bl->pieces[j]);
              printf ("%i\n", j);*/
          bb_bl->pieces[j]= 0x0000000000000000;
          bb_bl->pieces[0]=bb_bl->pieces[0] & bfin;
          break;
          }
      }
      bb_wh->pieces[i] = bfin;
    }
  else
    {
      while (bb_bl->pieces[i] != bini)
        i++;
      bb_bl->pieces[0] = bb_bl->pieces[0] & ~bb_bl->pieces[i];
      bb_bl->pieces[0] = bb_bl->pieces[0] | bfin;
      for (j = 1; j < 17; j ++)
      {
        if (bb_wh->pieces[j] == bfin)
            {
              /*print_ech (bb_wh->pieces[j]);
              printf ("%i\n", j);*/
          bb_wh->pieces[j]= 0x0000000000000000;
          bb_wh->pieces[0]=bb_wh->pieces[0] & bfin;
          break;
          }
          
        }
      bb_bl->pieces[i] = bfin;
    }
   calc_all_dep (bb_bl,bb_wh);
}



tree create_possible_tree (struct s_bb *white, struct s_bb *black, int prof)
{
  int                      color = BLACK;
  tree                     t,poss,poss_temp2;
  int                      i = 0;
  calc_all_dep (white,black);
  t = create_tree (*white,*black);
  poss = NULL;
  poss_temp2 = t;
  while (i < prof)
    {
      if (color == WHITE)
	{
	  xxx(black, white, color, poss, poss_temp2);
	  color = BLACK;
	}
      else
	{
	  xxx(black, white, color, poss, poss_temp2);
	  color = WHITE;
	}
	/*printf("COULEUUUUUUUR : %d\n", color);*/
    poss_temp2 = poss_temp2->son;
	      /*bfin = bitboard final = on copie bini. dans une boucle de 64 fois on decale cette copie vers la droite de 1. en meme tps on decale vers la gauche bfin qui au depart vaut 1. des que la copie est impaire, on arrete, on cree le noeud et on repart.
	       */
	  i++;
    }
  return (t);
}

void xxx (struct s_bb *black,  struct s_bb *white, int color, tree poss, tree poss_temp2)
{
  int                      j = 1;
  int                      k = 0;
  bitboard mask;
  struct s_bb              b_save;
  tree                     new;
  
  if (color == BLACK)
        b_save = *black;
  else
        b_save = *white;
        
  do       
        { 
          for (j = 1; j < 17; j++)
            {
               mask = 1;
               
               for (k = 0; k < 64; k++)
	          {

	               if (mask & b_save.possib[j])
	                 {
	                 if (color == BLACK)
                                *black = b_save;
                          else
                                *white = b_save;     
	                   updates_ia (black, white, b_save.pieces[j], mask, color);
	                   /*if (color == BLACK)
                       print_ech(black->pieces[0]);
                       else
                       print_ech(white->pieces[0]);*/
	                   new = create_tree (*white, *black);
	                   poss = add_bro (new, poss);		                   
	                 }
	             if (k > 0)
	               mask = mask<<1;		              
	          }     
	     }
	     /*printf("coucou\n");	     */
	     poss_temp2 = add_son (poss, poss_temp2);
	     poss_temp2 = poss_temp2->brother;
	     /*printf("%p\n", (void*)poss_temp2);
	     printf("BROTHER\n");*/

	}
  while (poss_temp2 != NULL);
}


