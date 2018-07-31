//
// Created by yyh on 18-7-30.
//
#include "client_fun.h"
#include "mySocket.h"
#include "login.h"

/************************************************************************
函数名称：	void *client_fun(void *arg)
函数功能：	线程函数,处理客户信息
函数参数：	已连接套接字
函数返回：	无
************************************************************************/
void *client_fun(void *arg)
{
    int connfd = (int)arg;      // 传入的已连接套接字
    int flag = 0;
    while (flag != -1){
        flag = getFlag(connfd);
        switch (flag) {
            case RECV_MAIL:
                recvMail();
                break;
            case CHECK_MAIL:
                checkMail();
                break;
            case SEND_MAIL:
                sendMail();
                break;
            case DEL_MAIL:
                delMail();
                break;
            case START_MAIL:
                startMail();
                break;
            case MODIFY_CONTACT:
                modifyContect();
                break;
            case MODIFY_BLACK_LIST:
                modifyBlackList();
                break;
            case STOP_LOOP:
                break;
            case LOGIN:
                servLogin();
            default:
                break;
        }
    }


    printf("client closed!\n");
    close(connfd);	//关闭已连接套接字

    return 	NULL;
}

int getFlag(int socket){
    char buffer[BUFFER_SIZE];
    bzero(buffer, sizeof(buffer));
    char type;
    myRecvMsg(socket, buffer, &type);
    if (strcmp(buffer, "exit") == 0){
        return STOP_LOOP;
    }
    else {
        printf("recv_buffer: %s\n", buffer);
        if (mySendMsg(socket, buffer, sizeof(buffer), MY_MSG) < 0){
            return -1;
        }
        return 0;
    }
}

int recvMail(){

}

int checkMail(){

}

int sendMail(){

}

int delMail() {

}

int startMail() {

}

int modifyContect() {

}

int modifyBlackList() {

}

int servLogin(int sock){
    char id[BUFFER_SIZE];
    char pass[BUFFER_SIZE];
    char type;
    bzero(id, sizeof(id));
    bzero(pass, sizeof(pass));
    myRecvMsg(sock, id, &type);
    myRecvMsg(sock, pass, &type);
    int flag = login(id, pass);
    switch (flag) {
        case 0:
            break;
        case -1:
            perror("文件打开错误");
            break;
        case -2:
            break;
        case -3:
            break;
        case -4:
            break;
        default:
            break;
    }
    return flag;


}