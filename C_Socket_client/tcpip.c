
#include "tcpip.h"

#define SIZE_IP 16

char * Tcpip_Search_IP_Of_Host(char * pNameHost)
{
  char ip[SIZE_IP];
  struct hostent *host;
  struct in_addr **addr_list;

  if( (host = gethostbyname(pNameHost)) == NULL)
  {
    perror("recv()"); // Erreur msdn.
    return NULL;
  }
  addr_list = (struct in_addr**)host->h_addr_list;
  strcpy(ip, inet_ntoa(*addr_list[0]));

  return 0;
}
