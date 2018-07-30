//
// Created by yyh on 18-7-30.
//

#ifndef NMAIL_SERVER_CLIENT_FUN_H
#define NMAIL_SERVER_CLIENT_FUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
void *client_fun(void *arg);


#endif //NMAIL_SERVER_CLIENT_FUN_H
