#ifndef IA_H_
#define IA_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitboards.h"


typedef struct s_tree  *tree;

struct s_tree
{
  tree           brother;
  tree           son;
  tree           father;
  int            poids;
  struct s_bb    possible;
};

/*void add_bro (tree node, tree t);*/
void add_son (tree node, tree t);
tree create_tree (struct s_bb possible);

#endif
