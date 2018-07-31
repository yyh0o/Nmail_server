#include"mailGoToBox.h"
/******************************
 *
 * 分发邮件
 * @param filename只穿入文件名自己可，函数中会补齐路径,并修改邮件状态为是否发送成功
 * @return 0 分发成功
 *         -1 文件打开失败
 *
 */
int sfRecieve(char* filename){
    char fileCompleteName[50];
    memset(fileCompleteName,0,50);
    strcpy(fileCompleteName,"server/TemporaryStorage/");
    strcat(fileCompleteName,filename);
    MAILHEAD  temphead;
    MAILBODY  tempbody;
    struct blacklist temp1;
    FILE* fp;
    fp=fopen(fileCompleteName,"r");
    if(fp==NULL)
        return -1;
    fread(&temphead,sizeof(MAILHEAD),1,fp);
    fread(&tempbody,sizeof(MAILBODY),1,fp);
    fclose(fp);
    char targetIdBlackList[25]; //目标邮箱号
    memset(targetIdBlackList,0,25);
    strcat(targetIdBlackList,"server/");
    strcat(targetIdBlackList,temphead.targetID);
    strcat(targetIdBlackList,"/blackList.txt");
    FILE* fp1;
    fp1=fopen(targetIdBlackList,"r");
    if(fp==NULL)
        return -1;
    for(int i=0;i<=getBlackListNum()-1;i++){
        fread(&temp1,sizeof(struct blacklist),1,fp1);
        if(strcmp(temp1.ID,temphead.originID)==0){
            temphead.sendstate=2;
            FILE* fp2;
            fp2=fopen(fileCompleteName,"w+");
            if(fp1==NULL)
                return -1;
            fwrite(&temphead,sizeof(MAILHEAD),1,fp2);
            fwrite(&tempbody,sizeof(MAILBODY),1,fp2);
            fclose(fp2);

        }
    }
    fclose(fp1);
    temphead.sendstate=1;
    FILE* fp3;
    fp3=fopen(fileCompleteName,"w+");
    if(fp3==NULL)
        return -1;
    fwrite(&temphead,sizeof(MAILHEAD),1,fp3);
    fwrite(&tempbody,sizeof(MAILBODY),1,fp3);
    fclose(fp3);
    if(temphead.sendstate==1) {
        int i = throwMail(filename);
        if (i == -1) {
            return -1;
        }
    }
    fcopy(fileCompleteName,filename);
    return 0;
}
/**************************
 * 投递函数，负责将邮件投递到目标邮箱且发送一份回到个人邮箱,将邮件头存入邮件列表中
 * @param filename 邮件名字
 *
 * @return -1 打开文件错误
 *         0 投递成功
 */
int throwMail(char* filename){
    char fileCompleteName[50];
    memset(fileCompleteName,0,50);
    strcpy(fileCompleteName,"server/TemporaryStorage/");
    strcat(fileCompleteName,filename);
    MAILHEAD  temp;
    FILE* fp;
    fp=fopen(fileCompleteName,"r");
    if(fp==NULL)
        return -1;
    fread(&temp,sizeof(MAILHEAD),1,fp);
    fclose(fp);
    char targetDir[50];
    memset(targetDir,0,50);
    strcpy(targetDir,"server/");
    strcat(targetDir, temp.targetID);
    strcat(targetDir,"/mailBox/");
    char listAdress[50];
    strcpy(listAdress,"list.txt");
    strcat(targetDir,filename);
    rename(fileCompleteName, targetDir);
    FILE* fp1;
    fp1=fopen(listAdress,"a+");
    if(fp1==NULL)
        return -1;
    fwrite(&temp,sizeof(MAILHEAD),1,fp1);
    fclose(fp1);
    return 0;
}
int fcopy(char* fileCompleteName,char* filename){
    MAILHEAD  temp;
    MAILBODY  tempbody;
    FILE* fp;
    fp=fopen(fileCompleteName,"r");
    if(fp==NULL)
        return -1;
    fread(&temp,sizeof(MAILHEAD),1,fp);
    fread(&tempbody,sizeof(MAILBODY),1,fp);
    fclose(fp);
    char targetDir[50];
    memset(targetDir,0,50);
    strcpy(targetDir,"server/");
    strcat(targetDir, temp.originID);
    strcat(targetDir,"/mailBox/");
    strcat(targetDir,filename);
    FILE* fp1;
    fp1=fopen(targetDir,"w+");
    if(fp1==NULL)
        return -1;
    fwrite(&temp,sizeof(MAILHEAD),1,fp1);
    fwrite(&tempbody,sizeof(MAILBODY),1,fp1);
    fclose(fp1);

}