//
// Created by nsu on 18-7-31.
//

#ifndef UNTITLED1_DABAO_H
#define UNTITLED1_DABAO_H

#include <stdio.h>
#include<string.h>
#include"Initialization.h"
#include"mailGoToBox.h"
#include "blackList.h"
struct CONTACT {
    char ID[12];
    char remark[10];
};

void dabaoServerSend(char *ID);
void dabaoClientSend(char *ID);
void clientJieya(char *ID);
void serverJieya(char *ID);

#endif //UNTITLED1_DABAO_H
