//
//  main.c
//  Contact
//
//  Created by 周彦錞 on 2018/7/31.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

//
//  main.c
//  BlackList
//
//  Created by 周彦錞 on 2018/7/29.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#define CONTACT_LIST "ContactList.txt"
#define CONTACT_NUM "ContactListNum.txt"
#include <stdio.h>
#include <string.h>
#include "contact.h"

/****************
 查找联系人
 传入需要查找的ID
 返回值 -1时 无文件
 返回值为 i时 找到联系人所在数组的下表
 ****************/
int fdContactListByID(char* userID){
    int number;
    number = getContactListNum();

    FILE* fp = NULL;
    fp = fopen(CONTACT_LIST, "r");
    if(fp == NULL){
        return -1;
    }

    struct CONTACT list[100];
    fread(list, sizeof(struct CONTACT),number, fp);
    for(int i=0;i<number;i++){
        if(strcmp(list[i].ID,userID)==0){
            return i;
        }
    }
    fclose(fp);
    return -1;
}
/*********************
 移除联系人
 传入需要删除的ID
 返回值为-1时 文件打开失败
 *********************/
int rmContactListByID(char* ID){
    int number=0;
    number = getContactListNum();
//    printf("in rmBlackListByID=%d\n",number);

    FILE* fp;
    fp = fopen(CONTACT_LIST, "r");
    if(fp == NULL){
        return -1;
    }
    struct CONTACT list[100] = {0};
    fread(list, sizeof(struct CONTACT), number, fp);
    fclose(fp);

    int a;
    a = fdContactListByID(ID);
    if (a == -1) {
        return -2;
    }
    //    strcpy(list[a].ID,"*");

    FILE* fp1;
    fp1 = fopen(CONTACT_LIST, "w+");
    if(fp1 == NULL){
        return -1;
    }
    bzero(list[a].ID, 12);
    for(int i=0;i<number;i++){
        if(strlen(list[i].ID)!=0){
            fwrite(&list[i], sizeof(struct CONTACT), 1, fp1);
        }
    }
    fclose(fp1);
    reduceContactListNum();

    return 0;
}

/******************************
 添加联系人
 传入需要添加的ID
 返回值为-2时 无联系人
 返回值为-3时 联系人内存在该ID
 返回值为-1时 打开文件失败
 ******************************/
int addContactList(char* ContactListID){
    FILE* fp;
    fp=fopen(CONTACT_LIST,"r");
    if(fp==NULL)
        return -1;
    struct CONTACT list[100] ={0};
    //memset(list,0,100*sizeof(list));
    int number = getContactListNum();
//    printf("number = %d\n",number);
    int i=0;
    if(number<0)
        return -2;
    if(number>0)
        fread(list,sizeof(struct CONTACT),number,fp);
    fclose(fp);
    if(number!=0){
        for(i=0;i<=number-1;i++){
            if(fdContactListByID(ContactListID)== i)
                return -3;
        }
    }
    FILE* fp1;
    fp1=fopen(CONTACT_LIST,"w+");
    if(fp1==NULL)
        return -1;
    strcpy(list[number].ID,ContactListID);
    fwrite(list,sizeof(struct CONTACT),number+1,fp);
    addContactListNum();
    fclose(fp1);
    return 0;
}
/*****************
 添加联系人人数
 *****************/
int addContactListNum(void){
    FILE* fp;
    fp = fopen(CONTACT_NUM, "r");
    if(fp == NULL){
        return -1;
    }
    int number = 0;
    fread(&number, sizeof(int), 1, fp);
    fclose(fp);
    number++;
    FILE* fp1;
    fp1 = fopen(CONTACT_NUM, "w+");
    fwrite(&number, sizeof(int), 1, fp1);
    fclose(fp1);
    return 0;
}
/*****************
 减少联系人人数
 *****************/
int reduceContactListNum(void){
    FILE* fp;
    fp = fopen(CONTACT_NUM, "r");
    if(fp == NULL){
        return -1;
    }
    int number = 0;
    fread(&number, sizeof(int), 1, fp);
    fclose(fp);
    number--;
    FILE* fp1;
    fp1 = fopen(CONTACT_NUM, "w+");
    fwrite(&number, sizeof(int), 1, fp1);
    fclose(fp1);
    return 0;
}
/*****************
 得到联系人人数
 返回值为联系人人数
 *****************/
int getContactListNum(void){
    FILE* fp;
    fp = fopen(CONTACT_NUM, "r");
    if(fp == NULL){
        return -1;
    }
    int number = 0;
    fread(&number, sizeof(int), 1, fp);
    fclose(fp);
    return number;
}
/********************
 显示联系人
 ********************/
int displayContactList(void){
    FILE* fp = NULL;
    fp=fopen(CONTACT_LIST,"r");
    if(fp==NULL)
        return -1;
    struct CONTACT temp={0};
//    printf("in displayBlackList = %d\n",getContactListNum());
    for(int i=0;i<=getContactListNum()-1;i++){
        fread(&temp,sizeof(temp),1,fp);
        printf("%s\n",temp.ID);
    }
    fclose(fp);
    return 0;
}
/**********
 联系人测试函数
 **********/
//int main(void){
//    char id1[10],id2[10],id3[10];
//    FILE* fp;
//    fp=fopen(CONTACT_LIST,"w+");
//    if(fp==NULL)
//        return -1;
//    fclose(fp);
//    FILE* fp1;
//    fp1 = fopen(CONTACT_NUM, "w+");
//    if(fp1 == NULL){
//        return -1;
//    }
//    //    int number = 0;
//    //    fwrite(&number, sizeof(int), 1, fp1);
//    fclose(fp1);
//    int a,b;
//    printf("输入添加ID1:");
//    scanf("%s",id1);
//    addContactList(id1);
//    displayContactList();
//    printf("输入添加ID2:");
//    scanf("%s",id2);
//    addContactList(id2);
//    displayContactList();
//    b = getContactListNum();
//    printf("%d\n",b);
//    printf("输入删除ID3:");
//    scanf("%s",id3);
//    rmContactListByID(id3);
//    displayContactList();
//    a = getContactListNum();
//    printf("%d\n",a);
//}
