
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h> 
#include <locale.h>
#include <WinSock2.h>
#include <windows.h>


#include "ctypes.h"
#include "portability.h"
#include "error.h"

#define PORT 80

struct SPerso{
  char nom[256];
  char prenom[256];
  s32 age;
};

struct SPerso gPerso;


int main(void)
{
  freopen("CON", "w", stdout);
  Portability_WindowsInit();

  sprintf(gPerso.nom, "MatinBonheur Sébastien");
  sprintf(gPerso.prenom, "Sebastien");
  gPerso.age = 26;

  // Socket et contexte d'adressage du serveur.
  SOCKADDR_IN sin; 
  SOCKET sock=0;
  socklen_t recsize = sizeof(sin);
  
  // Socket et contexte d'adressage du client.
  SOCKADDR_IN csin;
  SOCKET csock=0;
  socklen_t crecsize = sizeof(csin);
  u32 sock_err = 0, sock_err2 = 0, sock_err3 = 0;
  const char *pMsgWelcome = "Bienvenu a toi cher Client !\n";
  const char *pMsgWelcome2 = "Passe une agreable journee !\n";

  // Création d'une socket.
  sock = socket(AF_INET, SOCK_STREAM, 0);
  printf("Numero socket serveur = %d\n", sock);

  // Ouverture en mode TCP/IP.
  if(sock != INVALID_SOCKET)
  {
    // Configuration.
    sin.sin_family = AF_INET; // Protocole familiale (IP).
    sin.sin_addr.s_addr = htonl(INADDR_ANY); // Adresse IP automatique.
    sin.sin_port = htons(PORT); // Listage du port.
    // bind lie un socket avec une structure sockaddr.
    sock_err = bind(sock, (SOCKADDR*)&sin, recsize);

    // Socket fonctionne ?
    if(sock_err != SOCKET_ERROR)
    {
      // Démarrage du listage (mode server).
      sock_err = listen(sock, 5); // On écoute le port sur le socket sock.

      if(sock_err != SOCKET_ERROR)
      {
        // Attente pendant laquelle le client se connecte.
        printf("Merci de patienter pendant que le client se connecte.\n");
        while((csock = accept(sock, (SOCKADDR*)&csin, &crecsize)))
        {
          printf("Un client se connecte avec la socket %d ; IP %s : %d\n", csock, inet_ntoa(csin.sin_addr), 
          htons(csin.sin_port));
          sock_err = send(csock, pMsgWelcome, strlen(pMsgWelcome), 0);
          sock_err2 = send(csock, pMsgWelcome2, strlen(pMsgWelcome2), 0); // Prends que le premier pMsgWelcome2.
          sock_err3 = send(csock, (char *)&gPerso, sizeof(gPerso), 0);
          if(sock_err != SOCKET_ERROR)
            printf("Chaine envoyee : %s\n", pMsgWelcome);
          if(sock_err2 != SOCKET_ERROR)
            printf("Chaine envoyee : %s\n", pMsgWelcome2);
          if(sock_err3 != SOCKET_ERROR)
            printf("Structure envoyee !\n");
          else
            printf("Erreur de transmission\n");
          shutdown(csock, 2);
        }
      }
      else
      {
        Error_Msg_perror("listen()");
      }
    }
    else
    {
      Error_Msg_perror("bind()");
    }

    // Fermeture de la socket client et de la socket serveur.
    // printf("Fermeture de la socket client.\n");
    // closesocket(csock);
    printf("Fermeture de la socket serveur.\n");
    shutdown(csock, 2);
    closesocket(sock);
    printf("Fermeture du serveur terminee.\n");
  }
  else
  {
    Error_Msg_perror("socket");
  }
  Portability_WindowsClean();
  return 0;
}

