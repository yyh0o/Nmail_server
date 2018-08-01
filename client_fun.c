//
// Created by yyh on 18-7-30.
//
#include "client_fun.h"
#include "mySocket.h"
#include "login.h"
#include "Initialization.h"

/************************************************************************
函数名称：	void *client_fun(void *arg)
函数功能：	线程函数,处理客户信息
函数参数：	已连接套接字
函数返回：	无
************************************************************************/
void *client_fun(void *arg)
{
    int sock = (int)arg;      // 传入的已连接套接字

    int flag = 0;
    while (flag != STOP_LOOP){
        if ((flag = getFlag(sock)) != -4){

        }
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
                servLogin(sock);
                break;
            case SINGUP:
                servSignUp(sock);
                break;
            case LOGOUT:
                servLogOut(sock);
                break;
            default:
                break;
        }

    }


    printf("client closed!\n");
    close(sock);	//关闭已连接套接字

    return 	NULL;
}

int getFlag(int socket){
    char id[FLAG_SIZE] = {0};
    char pass[FLAG_SIZE] = {0};

    int flag = 0;
    char type;
    if(myRecvMsg(socket, &flag, &type) <= 0){
        return STOP_LOOP;
    }
    myRecvMsg(socket, id, &type);
    myRecvMsg(socket, pass, &type);
    if (flag == LOGOUT){
        mySendMsg(socket, &flag, sizeof(flag), MY_MSG);
        return flag;
    }
    int check = login(id, pass);

    if (check == -4 && flag != 8) {
        return DO_NOTHING;
    }
    else {
        mySendMsg(socket, &flag, sizeof(flag), MY_MSG);
    }

    return flag;
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

int servLogin(int sock) {
    char id[FLAG_SIZE] = {0};
    char pass[FLAG_SIZE] = {0};
    char type;
    myRecvMsg(sock, id, &type);
    myRecvMsg(sock, pass, &type);
    int flag = login(id, pass);
    mySendMsg(sock, &flag, sizeof(flag), MY_MSG);
    return flag;


}

int servLogOut(int sock){
    char id[FLAG_SIZE] = {0};
    char type;
    myRecvMsg(sock, id, &type);
    logout(id);
    mySendMsg(sock, "OK", sizeof("OK"), MY_MSG);
    return 0;
}

int servSignUp(int sock) {
    char id[FLAG_SIZE] = {0};
    char pass[FLAG_SIZE] = {0};
    char type;
    myRecvMsg(sock, id, &type);
    myRecvMsg(sock, pass, &type);
    int flag = selfInitiallization(id, pass);
    mySendMsg(sock, &flag, sizeof(flag), MY_MSG);
    return flag;
}