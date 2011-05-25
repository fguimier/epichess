#include "pgn.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


void pgn_out(char **mem, char *filename)
{
    int i, j, h, n;
    char *coup = malloc(90);
    FILE *out;
    DIR *dir;
    time_t timestamp;
    char *date = calloc (0,30);
    char *mmh = malloc (250);
    char * tmp = malloc(5);
    struct tm * t;
    int z = 0;

    timestamp = time(NULL);
    t = localtime(&timestamp);
    strcat (date, "[Date \"2011.");
    while(t->tm_mday)
      {
	tmp[z] = t->tm_mday % 10 + '0';
	t->tm_mday /= 10;
	z++;
      }
    tmp[z] = tmp[z-2];
    tmp[z-2] = tmp[z-1];
    tmp[z-1] = tmp[z];
    tmp[z] = 0;
    z = 0;
    strcat (date, tmp);
    strcat (date, ".");
    while(t->tm_mon)
      {
        tmp[z] = t->tm_mon % 10 + '0';
        t->tm_mon /= 10;
        z++;
      }
    tmp[z] = tmp[z-1]+1;
    tmp[z-1] = '0';
    tmp[z+1] = 0;
    strcat (date, tmp);
    strcat (date,"\"]\n");
    i = 1;
    j = 0;
    /* en-tête */
    mmh[0] = 's';mmh[1]='a';mmh[2]='v';mmh[3]='e';mmh[4]='/';mmh[5] = 0;
    strcat(mmh, filename);
    if(!(dir = opendir("save")))
      mkdir("save",0766);
    else
      closedir(dir);
    out = fopen (mmh,"w+");
    printf("%s\n",mmh);
    fwrite("[Event \"Soutenance\"]\n",1,21,out);
    fwrite("[Site \"Villejuif\"]\n",1,19,out);
    printf("%s\n",mmh);
    fwrite(date,1,20,out);
printf("%s\n",mmh);
    fwrite("[Round \"2\"]\n",1,12,out);
    fwrite("[White \"Joueur, 1\"]\n",1,20,out);
    fwrite("[Event \"Joueur, 2\"]\n",1,20,out);
    fwrite("[Result \"*\"]\n",1,13,out);
    fwrite("\n",1,1,out);
printf("%s\n",mmh);
    h = 0;
    /* corps */
    while (mem[i])
	{
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
	      {
		/*for (; h < 80;h++)
		  coup[h] = 0;*/
		fwrite(coup,1,h,out);
	      }
	    else
		{
		    h--;
		    while (coup[h] != ' ')
			h--;
		    fwrite(coup,1,h+1,out);
		    fwrite("\n",1,1,out);
		    n = 0;
		    h++;
		    for (; h < 80; h++)
		      {
			coup[n] = coup[h];
			n++;
		      }
		    h = n;
		}
	}
    printf("%s\n",mmh);
    fclose(out);
    free(coup);
}
