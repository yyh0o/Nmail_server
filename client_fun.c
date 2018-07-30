//
// Created by yyh on 18-7-30.
//
#include "client_fun.h"
#include "mySocket.h"

/************************************************************************
函数名称：	void *client_fun(void *arg)
函数功能：	线程函数,处理客户信息
函数参数：	已连接套接字
函数返回：	无
************************************************************************/
void *client_fun(void *arg)
{
    int recv_len = 0;
    char recv_buf[1024] = "";	// 接收缓冲区
    int connfd = (int)arg; // 传过来的已连接套接字

//    while((recv_len = recv(connfd, recv_buf, sizeof(recv_buf), 0)) > 0)
//    {
//        printf("recv_buf: %s\n", recv_buf); // 打印数据
//        send(connfd, recv_buf, recv_len, 0); // 给客户端回数据
//    }
//

//    FILE* fp = fopen("../1.png","r");
//    mySendFile(connfd, "1.png", 6, fp);
//    fclose(fp);

    // 接收数据
    while (1){
        char type;
        recv_len = myRecvMsg(connfd, recv_buf, &type);
        printf("recv_buf: %s\n", recv_buf); // 打印数据
        mySendMsg(connfd, recv_buf, recv_len, MY_MSG);//给客户端回数据
        if (recv_len <= 0)
            break;
        if (type == MY_MSG_EXIT)
            break;
    }


    printf("client closed!\n");
    close(connfd);	//关闭已连接套接字

    return 	NULL;
}
