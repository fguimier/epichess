#include "pgn.h"

void pgn_out(char **mem, char *filename)
{
    int i, j, h, n;
    char *coup = malloc(90);
    FILE *out;
    i = 1;
    j = 0;
    /* en-tête */
    out = fopen (filename,"w+");
    fwrite("[Event \"Soutenance\"]\n",1,21,out);
    fwrite("[Site \"Villejuif\"]\n",1,19,out);
    fwrite("[Date \"2011.??.??\"]\n",1,20,out);
    fwrite("[Round \"2\"]\n",1,12,out);
    fwrite("[White \"Joueur, 1\"]\n",1,20,out);
    fwrite("[Event \"Joueur, 2\"]\n",1,20,out);
    fwrite("[Result \"*\"]\n",1,13,out);
    fwrite("\n",1,1,out);

    /* corps */
    while (mem[i])
	{
	    printf("%s",mem[i]);
	    h = 0;
	    while (h < 80)
		{
		    if (mem[i][j])
			{
			    coup[h] = mem[i][j];
			    h++;
			    j++;
			}
		    else
			{
			    j = 0;
			    i++;
			    if (!mem[i])
				break;
			}
		}
	    if (!mem[i])
		fwrite(coup,1,h,out);
	    else
		{
		    h--;
		    while (coup[h] != ' ')
			h--;
		    fwrite(coup,1,h+1,out);
		    n = 0;
		    for (; h < 80; h++)
			{
			    coup[n] = coup[h];
			    n++;
			}
		    h = n;
		}
	}
    free(coup);
}
