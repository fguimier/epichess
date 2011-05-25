#ifndef IA_H_
#define IA_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitboards.h"
#include "pieces.h"

typedef struct s_tree  *tree;

struct s_tree
{
  tree           brother;
  tree           son;
  tree           father;
  int            poids;
  struct s_bb    possible_white;
  struct s_bb    possible_black;
};

tree create_tree (struct s_bb, struct s_bb);
tree add_son (tree, tree);
tree add_bro (tree, tree);
int max (int, int);
int profondeur (tree);
void updates_ia(struct s_bb *, struct s_bb *, bitboard,bitboard, int);
tree create_possible_tree (struct s_bb *, struct s_bb *, int);
void xxx (struct s_bb *,  struct s_bb *, int , tree, tree);
#endif
