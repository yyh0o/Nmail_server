//
//  main.c
//  BlackList
//
//  Created by 周彦錞 on 2018/7/29.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#define BLACK_LIST "BlackList.txt"
#define BLACK_NUM "BlackListNum.txt"
#include <stdio.h>
#include <string.h>
#include "blackList.h"

/****************
 查找联系人
 传入需要查找的ID
 返回值 -1时 无文件
 返回值为 i时 找到联系人所在数组的下表
 ****************/
int fdBlackListByID(char* userID){
    int number;
    number = getBlackListNum();
	
	FILE* fp = NULL;
    fp = fopen(BLACK_LIST, "r");
    if(fp == NULL){
        return -1;
    }
    
    struct blacklist list[100];
    fread(list, sizeof(struct blacklist),number, fp);
    for(int i=0;i<number;i++){
        if(strcmp(list[i].ID,userID)==0){
            return i;
        }
    }
    fclose(fp);
    return -1;
}
/*********************
 移除黑名单
 传入需要删除的ID
 返回值为-1时 文件打开失败
 *********************/
int rmBlackListByID(char* ID){
    int number=0;
    number = getBlackListNum();
//    printf("in rmBlackListByID=%d\n",number);
 	
	FILE* fp;
    fp = fopen(BLACK_LIST, "r");
    if(fp == NULL){
        return -1;
    }    
    struct blacklist list[100] = {0};
    fread(list, sizeof(struct blacklist), number, fp);
    fclose(fp);
   
    int a;
    a = fdBlackListByID(ID);
    if (a == -1) {
        return -2;
    }
//    strcpy(list[a].ID,"*");

	FILE* fp1;
    fp1 = fopen(BLACK_LIST, "w+");
    if(fp1 == NULL){
        return -1;
    }    
	bzero(list[a].ID, 12);
    for(int i=0;i<number;i++){
        if(strlen(list[i].ID)!=0){
            fwrite(&list[i], sizeof(struct blacklist), 1, fp1);
        }
    }
    fclose(fp1);
    reduceBlackListNum();
	
    return 0;
}

/******************************
 添加黑名单
 传入需要添加的ID
 返回值为-2时 无黑名单
 返回值为-3时 黑名单内存在该ID
 返回值为-1时 打开文件失败
 ******************************/
int addBlackList(char* blackListID){
    FILE* fp;
    fp=fopen(BLACK_LIST,"r");
    if(fp==NULL)
        return -1;
    struct blacklist list[100] ={0};
    //memset(list,0,100*sizeof(list));
    int number = getBlackListNum();
//    printf("number = %d\n",number);
    int i=0;
    if(number<0)
        return -2;
    if(number>0)
        fread(list,sizeof(list),number,fp);
    fclose(fp);
    if(number!=0){
        for(i=0;i<=number-1;i++){
            if(fdBlackListByID(blackListID)== i)
                return -3;
        }
    }
    FILE* fp1;
    fp1=fopen(BLACK_LIST,"w+");
    if(fp1==NULL)
        return -1;
    strcpy(list[number].ID,blackListID);
    fwrite(list,sizeof(list),number+1,fp);
    addBlackListNum();
    fclose(fp1);
    return 0;
}
/*****************
 添加黑名单人数
 *****************/
int addBlackListNum(void){
    FILE* fp;
    fp = fopen(BLACK_NUM, "r");
    if(fp == NULL){
        return -1;
    }
    int number = 0;
    fread(&number, sizeof(int), 1, fp);
    fclose(fp);
    number++;
    FILE* fp1;
    fp1 = fopen(BLACK_NUM, "w+");
    fwrite(&number, sizeof(int), 1, fp1);
    fclose(fp1);
    return 0;
}
/*****************
 减少黑名单人数
 *****************/
int reduceBlackListNum(void){
    FILE* fp;
    fp = fopen(BLACK_NUM, "r");
    if(fp == NULL){
        return -1;
    }
    int number = 0;
    fread(&number, sizeof(int), 1, fp);
    fclose(fp);
    number--;
    FILE* fp1;
    fp1 = fopen(BLACK_NUM, "w+");
    fwrite(&number, sizeof(int), 1, fp1);
    fclose(fp1);
    return 0;
}
/*****************
 得到黑名单人数
 返回值为黑名单人数
 *****************/
int getBlackListNum(void){
    FILE* fp;
    fp = fopen(BLACK_NUM, "r");
    if(fp == NULL){
        return -1;
    }
    int number = 0;
    fread(&number, sizeof(int), 1, fp);
    fclose(fp);
    return number;
}
/********************
 显示黑名单
 ********************/
int displayBlackList(void){
    FILE* fp = NULL;
    fp=fopen(BLACK_LIST,"r");
    if(fp==NULL)
        return -1;
    struct blacklist temp={0};
//    printf("in displayBlackList = %d\n",getBlackListNum());
    for(int i=0;i<=getBlackListNum()-1;i++){
        fread(&temp,sizeof(temp),1,fp);
        printf("%s\n",temp.ID);
    }
    fclose(fp);
    return 0;
}
/**********
 黑名单测试函数
 **********/
//int main(void){
//    char id1[10],id2[10],id3[10];
//    FILE* fp;
//    fp=fopen(BLACK_LIST,"w+");
//    if(fp==NULL)
//        return -1;
//    fclose(fp);
//    FILE* fp1;
//    fp1 = fopen(BLACK_NUM, "w+");
//    if(fp1 == NULL){
//        return -1;
//    }
////    int number = 0;
////    fwrite(&number, sizeof(int), 1, fp1);
//    fclose(fp1);
//    int a;
//    printf("输入添加ID1:");
//    scanf("%s",id1);
//    addBlackList(id1);
//    displayBlackList();
//    printf("输入添加ID2:");
//    scanf("%s",id2);
//    addBlackList(id2);
//    displayBlackList();
//    printf("输入删除ID3:");
//    scanf("%s",id3);
//    rmBlackListByID(id3);
//    displayBlackList();
//    a = getBlackListNum();
//    printf("%d\n",a);
//}
