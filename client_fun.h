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

#define STOP_LOOP -1024
#define RECV_MAIL 1
#define SEND_MAIL 2
#define CHECK_MAIL 3
#define DEL_MAIL 4
#define START_MAIL 5
#define MODIFY_CONTACT 6
#define MODIFY_BLACK_LIST 7
#define LOGIN 8
#define SINGUP 9
#define LOGOUT 10
#define FLAG_SIZE 100

void *client_fun(void *arg);
int getFlag(int socket);
int recvMail();
int checkMail();
int sendMail();
int delMail();
int startMail();
int modifyContect();
int modifyBlackList();
int servLogin(int sock);
int servSignUp(int sock);
int servLogOut(int sock);


#endif //NMAIL_SERVER_CLIENT_FUN_H
