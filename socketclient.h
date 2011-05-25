#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "socketserver.h"


int inti_socket();
int init_client();

#endif

