//
// Created by yyh on 18-7-30.
//

#ifndef NMAIL_SERVER_MYSOCKET_H
#define NMAIL_SERVER_MYSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

struct sockaddr new_addr(unsigned short port, char* IP);
int new_server_sock(unsigned short port);
int mySendMsg(int sockfd, char *buf, int len, char type);
int  myRecveMsg(int sockdf, char *buf, char* type);

#endif //NMAIL_SERVER_MYSOCKET_H
