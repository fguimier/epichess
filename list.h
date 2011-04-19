#ifndef __LIST_H
#define __LIST_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/* Definition du type t_list */
typedef struct s_list  *t_list;
/* Definition de la structure s_list */
struct s_list
{
    void       *val;
    t_list     next;
};

t_list empty(void);
int is_empty(t_list);
t_list add(void *, t_list);
size_t length(t_list);
void destroy_list(t_list);

#endif
