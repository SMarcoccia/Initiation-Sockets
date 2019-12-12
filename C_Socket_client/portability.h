#ifndef __PORTABILITY_H__
#define __PORTABILITY_H__

#include <stdio.h>
#include <errno.h>

#ifdef WIN32
  #include <WinSock2.h>
  typedef int socklen_t;
#elif defined (linux)
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <arpa/inet.h>
   #include <unistd.h>

   #define INVALID_SOCKET -1
   #define SOCKET_ERROR -1
   #define closesocket(s) close(s)

   typedef int SOCKET;
   typedef struct sockaddr_in SOCKADDR_IN;
   typedef struct sockaddr SOCKADDR;
#endif

//Définition variables et appel des fonctions nécessaire au fonctionnement des sockets sous windows.
void Portability_WindowsInit(void);
// Libération des ressources allouées par windowsInit().
void Portability_WindowsClean(void);

#endif