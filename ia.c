#include "ia.h"


tree create_tree (struct s_bb possible)
{
  tree n;

  n = malloc (sizeof (struct s_tree));
  n->brother = NULL;
  n->father = NULL;
  n->poids = 0;
  n->possible = possible;

  return (n);
}

void add_son (tree node, tree t)
{
  if (t == NULL)
    {
      t = node;
    }
  else
    {
      t->son = node;
      node->father = t;
      node->brother = NULL;
    }
}

void add_bro (tree node, tree t)
{
  tree     tmp;

  if (t == NULL)
    {
      t = node;
    }
  else
    {
      if (t->son == NULL)
	{
	  t->son = node;
	  t->brother = NULL;
	  t->father = t;
	}
      else
	{
	  tmp = t->son;
	  while (tmp->brother != NULL)
	    tmp = tmp->brother;
	  tmp->brother = node;
	  node->father = t;
	}
    }
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
