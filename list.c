#include "list.h"

t_list empty(void)
{
  return NULL;
}

int is_empty(t_list l)
{
  return (!l);
}

t_list add(void *x, t_list l)
{
    t_list ll = malloc(sizeof(struct s_list));
    ll->val = x;
    ll->next = l;
    return ll;
}
/*
void print_int(int x)
{
  printf(" %d;",x);
}
*/

size_t length(t_list l)
{
  size_t i=0;
  while (!is_empty(l))
    {
      l = l->next;
      i++;
    }
  return i;
}
/*
int sum(t_list l)
{
  int i = 0;
  while (!is_empty(l))
    {
      i+=l->val;
      l=l->next;
    }
  return i;
}
float avg(t_list l)
{
  int i= 0;
  float count = 0;
  while (!is_empty(l))
    {
      i+=l->val;
      l=l->next;
      count++;
    }
  return (i/count);
  }*/

void destroy_list(t_list l)
{
  t_list t;
  while (!is_empty(l))
    {
      t = l->next;
      if (l->val)
	  free(l->val);
      free(l);
      l=t;
    }
}
/*
void iter(void (*f)(int), t_list l)
{
  while (!is_empty(l))
    {
      f(l->val);
      l=l->next;
    }
}

*/
