#include "socketserver.h"

#define PORT 4242
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1



int init_server(void)
{
int erreur = 0;

  SOCKADDR_IN sin;
  SOCKET sock;
  SOCKET csock=-1;
  int recsize = sizeof sin;
  /*pthread_t *thread;*/
  int sock_err;
  /*char piece[1];
  char pos[2];
  */

  if(!erreur)
    {
      sock = socket(AF_INET, SOCK_STREAM, 0);
      get_ip();
      if(sock != INVALID_SOCKET)
        {
	  printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

	  sin.sin_addr.s_addr = htonl(INADDR_ANY);
	  sin.sin_family = AF_INET;
	  sin.sin_port = htons(PORT);
	  sock_err = bind(sock, (SOCKADDR*) &sin, recsize);

	  if(sock_err != SOCKET_ERROR)
            {
	      sock_err = listen(sock, 5);
	      printf("Listage du port %d...\n", PORT);

	      if(sock_err != SOCKET_ERROR)
                {
		  /* Création de l'ensemble de lecture */
		  

		  while(csock == (-1))
                    {
		      /* On vide l'ensemble de lecture et on lui ajoute 
			 la socket serveur */
		      /*FD_ZERO(&readfs);
		      FD_SET(sock, &readfs);

		       Si une erreur est survenue au niveau du select 
		      if(select(sock + 1, &readfs, NULL, NULL, NULL) < 0)
                        {
			  perror("select()");
			  exit(errno);
                        }

		       On regarde si la socket serveur contient des 
			 informations à lire 
		      if(FD_ISSET(sock, &readfs))
                        {
			   Ici comme c'est la socket du serveur cela signifie 
                            forcement qu'un client veut se connecter au serveur. 
                            Dans le cas d'une socket cliente c'est juste des 
                            données qui serons reçues ici*/

			  SOCKADDR_IN csin;
			  int crecsize = sizeof csin;

			  /* Juste pour l'exemple nous acceptons le client puis 
			     nous refermons immédiatement après la connexion */
                    listen(sock,1);
			  csock = accept(sock, (SOCKADDR *) &csin, (socklen_t * restrict)&crecsize);
			printf("Un client s'est connecte\n"); 
		    }
		  
			
		  
                 return csock;       
                    
                }
            }
        }
    }

  return EXIT_SUCCESS;
}

void get_ip()
{
  FILE *fd;
  char *ip_addr = malloc(20);
  system("cmd=`/sbin/ifconfig`;y=${cmd#*inet addr:};y=${y%% *};echo $y >ipaddr");
  fd = fopen("ipaddr", "r+");
  fscanf(fd, "%s", ip_addr);
  fclose(fd);
  fprintf(stderr,"IP Address:%s\n", ip_addr);
  return;
}
