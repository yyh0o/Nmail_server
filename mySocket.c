//
// Created by yyh on 18-7-30.
//
#include "mySocket.h"
#include "client_fun.h"

typedef struct {
    char type; //消息类型
    int len;  //数据长度
} myMsgHead;//数据头

#define


/***********************************************************************
 * 创建一个地址结构体
 * @param port 连接地址端口
 * @param IP 连接地址IP,若是服务端则传NULL
 * @return 返回一个struct sockaddr结构体
 */
struct sockaddr new_addr(unsigned short port, char *IP) {
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (IP) {
        inet_pton(AF_INET, IP, &addr.sin_addr);
    } else {
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    return *((struct sockaddr *) &addr);
}

/*************************************************************************
 * 创建一个服务器的sock
 * @param port 服务器端口
 * @return  返回一个绑定到端口的套接字
 */
int new_server_sock(unsigned short port) {
    int sockfd;
    int err_log = 0;

    struct sockaddr addr = new_addr(port, NULL); //创建并初始化服务器地址结构体
    sockfd = socket(AF_INET, SOCK_STREAM, 0);   // 创建TCP套接字
    if (sockfd < 0) {
        perror("socket error");
        exit(-1);
    }


    printf("Binding server to port %d\n", port);

    // 绑定
    err_log = bind(sockfd, &addr, sizeof(addr));
    if (err_log != 0) {
        perror("bind");
        close(sockfd);
        exit(-1);
    }

    // 监听，套接字变被动
    err_log = listen(sockfd, 10);
    if (err_log != 0) {
        perror("listen");
        close(sockfd);
        exit(-1);
    }

    printf("Waiting client...\n");
    return sockfd;
}


/********************************************************************
 *
 * @param sockfd 已建立连接的套接字
 * @param buf 发送数据缓冲区
 * @param len 发送数据长度
 * @param type 发送数据类型
 * @return 返回接收数据长度
 */
int mySendMsg(int sockfd, char *buf, int len, char type) {
    myMsgHead msgHead;
    msgHead.type = type;
    msgHead.len = len;

    send(sockfd, &msgHead, sizeof(myMsgHead), 0);
    return send(sockfd, buf, len, 0);
}

/***********************************************************
 *
 * @param sockdf 已建立连接的套接字
 * @param buf 接收数据的缓冲区
 * @param type 用于储存接受文件的数据类型
 * @return 返回接收文件的大小
 */
int  myRecveMsg(int sockdf, char *buf, char* type) {
    myMsgHead head;
    char* buffer = (char*)malloc(sizeof(myMsgHead)+1);

    recv(sockdf, buffer, sizeof(myMsgHead), 0);
    memcpy(&head, buffer, sizeof(myMsgHead));
    recv(sockdf,buf,head.len,0);
    free(buffer);
    buffer = NULL;

    *type = head.type;
    return head.len;
}