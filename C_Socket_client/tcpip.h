#ifndef __TCPIP_H__
#define __TCPIP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#include "ctypes.h"

// Recherche à partir du nom de domaine l'adresse IP.
char * Tcpip_Search_IP_Of_Host(char * pNameHost); 

#endif