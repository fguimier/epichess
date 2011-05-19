#ifndef __GPN_EVENT_H
#define __GPN_EVENT_H

#include "echiquier.h"

t_list search_tower(struct s_echiquier *e, struct s_case *cini,
		    struct s_case *cfin, enum color colo,
		    struct s_bb *bb_bl, struct s_bb *);

#endif
