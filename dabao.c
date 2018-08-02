//
// Created by nsu on 18-7-31.
//
#include"dabao.h"
void dabaoServerSend(char *ID){
    MAILHEAD mailhead[100];
    MAILBODY mailbody[100];
    int mailnumber=0;
    struct blacklist bllist[100];
    int bllistnumber=0;
    struct CONTACT  conlist[100];
    int connumber=0;
    char lujing[50];
    char temp1[50];
    char temp2[50];
    char temp3[50];
    char temp4[50];
    char temp5[50];
    char temp6[50];
    memset(lujing,0,50);
    memset(temp1,0,50);
    memset(temp2,0,50);
    memset(temp3,0,50);
    memset(temp4,0,50);
    memset(temp5,0,50);
    memset(temp6,0,50);
    strcpy(lujing,"server/");
    strcat(lujing,ID);
    strcpy(temp1,lujing);
    strcpy(temp2,lujing);
    strcpy(temp3,lujing);
    strcpy(temp4,lujing);
    strcat(lujing,"/mailBox/");
    strcpy(temp5,lujing);
    strcpy(temp6,lujing);
    strcat(temp1,"/blackList.txt");
    strcat(temp2,"/blackListNum.txt");
    strcat(temp3,"/contacts.txt");
    strcat(temp4,"/contactNum.txt");
    strcat(temp5,"list.txt");
    strcat(temp6,"mailNumber.txt");
    FILE* fp;
    fp=fopen(temp2,"r");
    fread(&bllistnumber,sizeof(int),1,fp);
    fclose(fp);

    FILE* fp1;
    fp1=fopen(temp1,"r");
    fread(&bllist,sizeof(struct blacklist),bllistnumber,fp1);
    fclose(fp1);

    FILE* fp2;
    fp2=fopen(temp4,"r");
    fread(&connumber,sizeof(int),1,fp2);
    fclose(fp2);

    FILE* fp3;
    fp3=fopen(temp3,"r");
    fread(&conlist,sizeof(struct CONTACT),connumber,fp3);
    fclose(fp3);

    FILE* fp4;
    fp4=fopen(temp6,"r");
    fread(&mailnumber,sizeof(int),1,fp4);
    fclose(fp4);

    FILE* fp5;
    fp5=fopen(temp5,"r");

        fread(mailhead,sizeof(MAILHEAD),1,fp5);

    fclose(fp5);

    char fileCompleteName[50];
    memset(fileCompleteName,0,50);
    strcpy(fileCompleteName,"server/");
    strcat(fileCompleteName,ID);
    strcat(fileCompleteName,"*.txt");
    FILE* nb;
    nb=fopen(fileCompleteName,"w+");
    fwrite(&bllistnumber,sizeof(int),1,nb);
    fwrite(&bllist,sizeof(struct blacklist),bllistnumber,nb);
    fwrite(&connumber,sizeof(int),1,nb);
    fwrite(&conlist,sizeof(struct CONTACT),connumber,nb);
    fwrite(&mailnumber,sizeof(int),1,nb);

    fwrite(mailhead,sizeof(MAILHEAD),mailnumber,nb);

    fclose(nb);
}
void dabaoClientSend(char *ID){
    struct blacklist bllist[100];
    int bllistnumber=0;
    struct CONTACT  conlist[100];
    int connumber=0;
    char lujing[50];
    char temp1[50];
    char temp2[50];
    char temp3[50];
    char temp4[50];
    memset(lujing,0,50);
    memset(temp1,0,50);
    memset(temp2,0,50);
    memset(temp3,0,50);
    memset(temp4,0,50);
    strcpy(lujing,"client");
    strcpy(temp1,lujing);
    strcpy(temp2,lujing);
    strcpy(temp3,lujing);
    strcpy(temp4,lujing);
    strcat(temp1,"/blackList.txt");
    strcat(temp2,"/BlackListNum.txt");
    strcat(temp3,"/ContactList.txt");
    strcat(temp4,"/contactNum.txt");
    FILE* fp;
    fp=fopen(temp2,"r");
    fread(&bllistnumber,sizeof(int),1,fp);
    fclose(fp);

    FILE* fp1;
    fp1=fopen(temp1,"r");
    fread(&bllist,sizeof(struct blacklist),bllistnumber,fp1);
    fclose(fp1);

    FILE* fp2;
    fp2=fopen(temp4,"r");
    fread(&connumber,sizeof(int),1,fp2);
    fclose(fp2);

    FILE* fp3;
    fp3=fopen(temp3,"r");
    fread(&conlist,sizeof(struct CONTACT),connumber,fp3);
    fclose(fp3);


    char fileCompleteName[50];
    memset(fileCompleteName,0,50);
    strcpy(fileCompleteName,"client/");
    strcat(fileCompleteName,"dabao.txt");
    FILE* nb;
    nb=fopen(fileCompleteName,"w+");
    fwrite(&bllistnumber,sizeof(int),1,nb);
    fwrite(&bllist,sizeof(struct blacklist),bllistnumber,nb);
    fwrite(&connumber,sizeof(int),1,nb);
    fwrite(&conlist,sizeof(struct CONTACT),connumber,nb);
    fclose(nb);
}
void clientJieya(char *ID){
    MAILHEAD mailhead[100];
    MAILBODY mailbody[100];
    int mailnumber=0;
    struct blacklist bllist[100];
    int bllistnumber=0;
    struct CONTACT  conlist[100];
    int connumber=0;
    char lujing[50];
    char temp1[50];
    char temp2[50];
    char temp3[50];
    char temp4[50];
    char temp5[50];
    char temp6[50];
    memset(lujing,0,50);
    memset(temp1,0,50);
    memset(temp2,0,50);
    memset(temp3,0,50);
    memset(temp4,0,50);
    memset(temp5,0,50);
    memset(temp6,0,50);
    strcpy(lujing,"client");
    strcpy(temp1,lujing);
    strcpy(temp2,lujing);
    strcpy(temp3,lujing);
    strcpy(temp4,lujing);
    strcat(lujing,"/mailBox/");
    strcpy(temp5,lujing);
    strcpy(temp6,lujing);
    strcat(temp1,"/blackList.txt");
    strcat(temp2,"/blackListNum.txt");
    strcat(temp3,"/contacts.txt");
    strcat(temp4,"/contactNum.txt");
    strcat(lujing,ID);
    strcat(temp5,"list.txt");
    strcat(temp6,"mailNumber.txt");
    strcpy(lujing,"*.txt");
    FILE* fp;
    fp=fopen(lujing,"r");
    fread(&bllistnumber,sizeof(int),1,fp);
    fread(&bllist,sizeof(struct blacklist),bllistnumber,fp);
    fread(&connumber,sizeof(int),1,fp);
    fread(&conlist,sizeof(struct CONTACT),connumber,fp);
    fread(&mailnumber,sizeof(int),1,fp);
    fread(mailhead,sizeof(MAILHEAD),mailnumber,fp);
    fclose(fp);

    FILE* fp1;
    fp1=fopen(temp2,"w+");
    fwrite(&bllistnumber,sizeof(int),1,fp1);
    fclose(fp1);

    FILE* fp2;
    fp2=fopen(temp1,"w+");
    fwrite(&bllist,sizeof(struct blacklist),bllistnumber,fp2);
    fclose(fp2);

    FILE* fp3;
    fp3=fopen(temp4,"w+");
    fwrite(&connumber,sizeof(int),1,fp3);
    fclose(fp3);

    FILE* fp4;
    fp4=fopen(temp3,"w+");
    fwrite(&conlist,sizeof(struct CONTACT),connumber,fp4);
    fclose(fp4);

    FILE* fp5;
    fp5=fopen(temp6,"w+");
    fwrite(&mailnumber,sizeof(int),1,fp5);
    fclose(fp5);

    FILE* fp6;
    fp6=fopen(temp5,"w+");
    fwrite(mailhead,sizeof(MAILHEAD),mailnumber,fp6);
    fclose(fp6);

}
void serverJieya(char *ID){
    int mailnumber=0;
    struct blacklist bllist[100];
    int bllistnumber=0;
    struct CONTACT  conlist[100];
    int connumber=0;
    char lujing[50];
    char temp1[50];
    char temp2[50];
    char temp3[50];
    char temp4[50];

    memset(lujing,0,50);
    memset(temp1,0,50);
    memset(temp2,0,50);
    memset(temp3,0,50);
    memset(temp4,0,50);

    strcpy(lujing,"server/");
    strcat(lujing,ID);
    strcpy(temp1,lujing);
    strcpy(temp2,lujing);
    strcpy(temp3,lujing);
    strcpy(temp4,lujing);
    strcat(temp1,"/blackList.txt");
    strcat(temp2,"/blackListNum.txt");
    strcat(temp3,"/contacts.txt");
    strcat(temp4,"/contactNum.txt");
    strcpy(lujing,"*.txt");

    FILE* fp;
    fp=fopen(lujing,"r");
    fread(&bllistnumber,sizeof(int),1,fp);
    fread(&bllist,sizeof(struct blacklist),bllistnumber,fp);
    fread(&connumber,sizeof(int),1,fp);
    fread(&conlist,sizeof(struct CONTACT),connumber,fp);
    fclose(fp);

    FILE* fp1;
    fp1=fopen(temp2,"w+");
    fwrite(&bllistnumber,sizeof(int),1,fp1);
    fclose(fp1);

    FILE* fp2;
    fp2=fopen(temp1,"w+");
    fwrite(&bllist,sizeof(struct blacklist),bllistnumber,fp2);
    fclose(fp2);

    FILE* fp3;
    fp3=fopen(temp4,"w+");
    fwrite(&connumber,sizeof(int),1,fp3);
    fclose(fp3);

    FILE* fp4;
    fp4=fopen(temp3,"w+");
    fwrite(&conlist,sizeof(struct CONTACT),connumber,fp4);
    fclose(fp4);


}
