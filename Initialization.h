//
// Created by nsu on 18-7-29.
//

#ifndef UNTITLED_INITIALIZATION_H
#define UNTITLED_INITIALIZATION_H
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "blackList.h"

#define USERLIST "server/userRegistrationlist.txt"//用户注册列表文件
#define USERNUMBER "server/userNumber.txt"//已注册用户数量
typedef struct{
    char userId[20];
    char passWord[20];
    int state;
}REGISTERINFOR;//注册信息结构体
int sysInitiallization();
int selfInitiallization(char* userId,char*passWord);
int fwUser(char * userId,char* passWord);
int getUserNum();
int setUserNum();

#endif //UNTITLED_INITIALIZATION_H
