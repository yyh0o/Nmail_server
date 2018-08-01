//
//  packaging.h
//  22222
//
//  Created by 周彦錞 on 2018/8/1.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#ifndef packaging_h
#define packaging_h
struct MAILHEAD{
    char targetID[25];
    char originID[25];
    char data[30];
    char title[50];
    int state;
    int sendstate;
};
struct MAILBODY{
    char content[500];
    int aooendixState;
    char appenfixName[50];
};
int separate(char* title);//文件拆封
int packaging(char* targetID,char* title,char* content);//文件封装

#endif /* packaging_h */
