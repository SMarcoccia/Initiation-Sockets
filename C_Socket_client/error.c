
#include "error.h"

void Error_Msg_perror(char const* pMsg)
{
  #ifdef WIN32
    char *pMsg_Error = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL, WSAGetLastError(), 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPSTR)&pMsg_Error, 0, NULL);
    printf("%s : %s\n", pMsg, pMsg_Error);
    LocalFree(pMsg_Error);
  #elif linux
    perror(pMsg);             
  #endif
}
