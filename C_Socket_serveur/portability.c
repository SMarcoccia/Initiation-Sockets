
#include "portability.h"

void Portability_WindowsInit(void)
{
  #ifdef WIN32
    WSADATA WSAData;
    // Initialisation de la bibliothèque WinSock.
    int err = WSAStartup(MAKEWORD(2,2), &WSAData);
    if(err < 0)
    {
      puts("WSAStartup failed !\n");
      exit(EXIT_FAILURE);
    }
  #endif
}

void Portability_WindowsClean(void)
{
  #ifdef WIN32 
    WSACleanup();
  #endif
}