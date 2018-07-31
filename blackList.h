//
//  BlackList.h
//  BlackList
//
//  Created by 周彦錞 on 2018/7/30.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#ifndef BlackList_h
#define BlackList_h

struct blacklist{
    char ID[12];
};//黑名单的结构体

int addBlackListNum(void);//添加黑名单人数
int getBlackListNum(void);//得到黑名单人数
int reduceBlackListNum(void);//减少黑名单人数
int fdBlackListByID(char* userID);//找到黑名单内相应的ID
int addBlackList(char* blackListID);//添加黑名单
int rmBlackListByID(char* ID);//移除黑名单
int displayBlackList(void);//显示黑名单

#endif /* BlackList_h */
