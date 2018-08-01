//
//  main.c
//  packaging
//
//  Created by 周彦錞 on 2018/7/31.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include "packaging.h"
//#include "configuration.c"
//#include "packaging.h"

/*********************
 将文件封装
 返回值为-1 文件打开失败
 返回值为0 运行完成
 */
int packaging(char* targetID,char* title,char* content){
//    FILE* fp;
//    fp = fopen("/Users/kevin/Documents/GitHub/NeuMail/configuration/configuration.txt", "r");
//    if(fp == NULL){
//        return -1;
//    }
//    struct configurationFile temp;
//    fread(&temp, sizeof(temp), 1, fp);
//    fclose(fp);
    struct MAILHEAD head;
    struct MAILBODY body;
    char title1[50];
//    strcpy(head.originID, temp.userId);
    strcpy(head.targetID, targetID);
    strcpy(body.content, content);
    time_t timep;
    time(&timep);
    strcpy(head.data, asctime(gmtime(&timep)));
    strcpy(head.title, title);
    head.state = 0;
    strcpy(title1,"client/TemporaStorage/");
    strcat(title1,title);
    strcat(title1,".txt");
    FILE* fp1;
    fp1 = fopen(title1, "w+");
    if( fp1 == NULL){
        return -1;
    }
    fwrite(&head, sizeof(head), 1, fp1);
    fwrite(&body, sizeof(body), 1, fp1);
    fclose(fp1);
    return 0;
}
/****************
 文件拆封
 将文件变成字符串
 返回值为-1 文件打开失败
 返回值为0 运行完成
 */
int separate(char* title){
//    configuration("111@111","1212.22.22.2","2222");
//    packaging("123123","34343433","3423243423");
    char title1[50];
    strcpy(title1,"client/TemporaStorage/");
    strcat(title1,title);
    strcat(title1,".txt");
    struct MAILHEAD head;
    struct MAILBODY body;
    FILE* fp1;
    fp1 = fopen(title1, "r");
    if(fp1 == NULL){
        return -1;
    }
    fread(&head, sizeof(head), 1, fp1);
    fread(&body, sizeof(body), 1, fp1);
    printf("%s\n",head.targetID);
//    printf("%s\n",head.originID);
    printf("%s\n",head.data);
    printf("%s\n",head.title);
    printf("%s\n",body.content);
    fclose(fp1);
    return 0;
}

