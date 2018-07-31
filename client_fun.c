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

//    while (!loginState){
//        servLogin(sock, &loginState);
//    }

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
            case SINGUP:
                break;
            case LOGOUT:
                servLogOut(sock);
                flag = -1024;
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
    int flag = 0;
    char buffer[BUFFER_SIZE] = {0};
    char type;
    char id[BUFFER_SIZE] = {0};
    char pass[BUFFER_SIZE] = {0};
    myRecvMsg(socket, id, &type);
    myRecvMsg(socket, pass, &type);
    myRecvMsg(socket, buffer, &type);
    if (strcmp(buffer, "1") == 0){
        flag = 1;
    }
    else if (strcmp(buffer, "2") == 0){
        flag = 2;
    }
    else if (strcmp(buffer, "3") == 0){
        flag = 3;
    }
    else if (strcmp(buffer, "4") == 0){
        flag = 4;
    }
    else if (strcmp(buffer, "5") == 0){
        flag = 5;
    }
    else if (strcmp(buffer, "6") == 0){
        flag = 6;
    }
    else if (strcmp(buffer, "7") == 0){
        flag = 7;
    }else if (strcmp(buffer, "8") == 0){
        flag = 8;
    }
    else if (strcmp(buffer, "9") == 0){
        flag = 9;
        mySendMsg(socket, &flag, sizeof(flag), MY_MSG);
        return flag;
    }
    else if (strcmp(buffer, "10") == 0){
        flag = 10;
    }
    else if (strcmp(buffer, "-1024") == 0){
        flag = -1024;
        mySendMsg(socket, &flag, sizeof(flag), MY_MSG);
        return flag;
    }

    if (flag != 8){
        int state = login(id, pass);
        if (state != -4){
            flag = state;
        }
    }
    mySendMsg(socket, &flag, sizeof(flag), MY_MSG);
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