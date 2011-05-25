#include "socketclient.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define PORT 4242
 
int init_client(void)
{
  int erreur = 0;
  SOCKET sock;
  SOCKADDR_IN sin;
  char* addr_ip = malloc(sizeof(char));
  /* Si les sockets Windows fonctionnent */
  if(!erreur)
    {
      /* Création de la socket */
      sock = socket(AF_INET, SOCK_STREAM, 0);
      scanf("%s", addr_ip);
      printf("%s", addr_ip);
      /* Configuration de la connexion */
      sin.sin_addr.s_addr = inet_addr(addr_ip);
      sin.sin_family = AF_INET;
      sin.sin_port = htons(PORT);
 
      /* Si l'on a réussi à se connecter */
      if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        {
	  printf("Connection à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
         }   
	  /* Si l'on reçoit des informations : on les affiche à l'écran 
	  if(recv(sock, buffer, 32, 0) != SOCKET_ERROR)
	    printf("Recu : %s\n", buffer);
        }
       sinon, on affiche "Impossible de se connecter" */
      else
        {
	  printf("Impossible de se connecter\n");
        }
 
      /* On ferme la socket */
      
 

    }
 
  /* On attend que l'utilisateur tape sur une touche, puis on ferme */
  
 printf("lolilol");
  return sock;
}
