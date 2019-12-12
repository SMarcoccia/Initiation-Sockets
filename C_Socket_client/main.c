#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <WinSock2.h>
#include <windows.h>

#include "ctypes.h"

#include "portability.h"
#include "tcpip.h"
#include "error.h"

#define PORT 80
#define HOST_Name "www.google.com"
#define HOST_IP "127.0.0.1"

struct SPerso{
  char nom[256];
  char prenom[256];
  s32 age;
};

struct SPerso gPerso;

int main(void)
{
  errno = 0;
  freopen("CON", "w", stdout); // Forcer la redirection vers le shell.
  Portability_WindowsInit();

  // char *pIP = Tcpip_Search_IP_Of_Host(HOST_Name);

  // Socket et contexte d'adressage du client.
  SOCKADDR_IN sin;
  SOCKET sock; // typedef unsigned __int64 UINT_PTR(basetsd.h); puis typedef UINT_PTR SOCKET;(WinSock2.h)

  // Création d'une socket.
  sock = socket(AF_INET, SOCK_STREAM, 0);
  printf("No socket client = %d\n", sock);

  // Ouverture en mode TCP/IP.
  // char pTab[64] = "";

  if(sock != INVALID_SOCKET)
  {
    // Configuration.
    sin.sin_addr.s_addr = inet_addr(HOST_IP); // Adresse IP de l'hôte en automatique. 
    sin.sin_family = AF_INET; // IP.
    sin.sin_port = htons(PORT); // Le port.
    
    while(1)
    {
      // Débuter une connexion sur une socket ?
      if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
      {
        printf("Connexion a l'IP : %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
        break;
      }
      else
      {
        printf("Connection impossible\n");
        // TODO : mettre un time.
      }
    }

    // char *message;
    char pServer_reply[2000];
    // message = "GET / HTTP/1.1\r\n\r\n";
    // printf("message = %s\n", message);
    // if(send(sock, message, strlen(message), 0) != SOCKET_ERROR)
    //   printf("Chaine envoyee : %s\n", message);
    // else
    //   Error_Msg_perror("recv()");

    if(recv(sock, pServer_reply, 2000, 0) != SOCKET_ERROR)
      printf("pServer_reply = %s\n", pServer_reply);
    else
    {
      Error_Msg_perror("recv()");
    }
    if(recv(sock, (char *)&gPerso, sizeof(gPerso), 0) != SOCKET_ERROR)
    {
      printf("pServer_reply = %s\n", gPerso.nom);
      printf("pServer_reply = %s\n", gPerso.prenom);
      printf("pServer_reply = %d\n", gPerso.age);
    }
    else
      Error_Msg_perror("recv()");
  }

  closesocket(sock); 
  Portability_WindowsClean();
  return 0;
}
