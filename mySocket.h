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

#define MY_MSG '1'  //普通标志
#define MY_MSG_EXIT 'x' //退出标志
#define MY_MSG_FILE 'f' //文件标志


#define BUFFER_SIZE                1024
#define FILE_NAME_MAX_SIZE         512


typedef struct {
    char type; //消息类型
    int len;  //数据长度
} myMsgHead;//数据头


struct sockaddr new_addr(unsigned short port, char* IP);
int new_server_sock(unsigned short port);
int new_connected_sock(const char* ip, unsigned short port);
int mySendMsg(int sockfd, char *buf, int len, char type);
int  myRecvMsg(int sockdf, char *buf, char* type);
int mySendFile(int sockdf, const char* fileName,int nameLen, FILE* fp);
int myRecvFile(int sockdf, const char* path, int pathlen);

#endif //NMAIL_SERVER_MYSOCKET_H
