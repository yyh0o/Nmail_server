//
//  Contact.h
//  Contact
//
//  Created by 周彦錞 on 2018/7/31.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#ifndef Contact_h
#define Contact_h



struct CONTACT {
    char ID[12];
    char remark[10];
}; //联系人的结构体

int addContactNum(void);//添加联系人人数
int getContactNum(void);//得到联系人人数
int reduceContactNum(void);//减少联系人人数
int fdContactListByID(char* userID);//找到联系人内相应的ID
int addContactList(char* blackListID);//添加联系人
int rmContactListByID(char* ID);//移除联系人
int displayContactList(void);//显示联系人

#endif /* Contact_h */