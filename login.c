#include"Initialization.h"
#include "login.h"

/*********************************************
 * 登陆函数，通过用户id查找其密码，检查是否匹配，若匹配，检查其是否登陆
 * @param userScanfId 用户输入的id
 * @param scanfPassWord 用户输入密码
 * @return 0 登陆成功
 *        -1 文件打开失败
 *        -2 用户不存在
 *         -3 密码错误
 *         -4 用户以在别的设备上登陆
 */
int login(char* userScanfId,char*scanfPassWord){
    REGISTERINFOR temp;
    FILE* fp;
    fp=fopen(USERLIST,"r");
    if(fp==NULL)
        return -1;
    int i=0;
    for(i=0;i<=getUserNum()-1;i++){
        fread(&temp,sizeof(REGISTERINFOR),1,fp);
        if(strcmp(temp.userId,userScanfId)==0){
            if(strcmp(temp.passWord,scanfPassWord)==0){
                if(temp.state==1){
                    fclose(fp);
                    return -4;
                }
                else{
                    fclose(fp);
                    moState(userScanfId);
                    return 0;
                }
            }
            else{
                fclose(fp);
                return -3;
            }
        }
    }
    fclose(fp);
    return -2;



}
/******************************************
 * 修改用户登录状态
 * @param ID
 */
void moState(char* ID){
    REGISTERINFOR temp[100];
    FILE* fp;
    fp=fopen(USERLIST,"r");
    fread(temp,sizeof(REGISTERINFOR),getUserNum(),fp);
    fclose(fp);
    for(int i=0;i<=getUserNum()-1;i++){
        if(strcmp(temp[i].userId,ID)==0){
            if(temp[i].state==1)
                temp[i].state=0;
            else
                temp[i].state=1;
            break;

        }
    }
    FILE* fp1;
    fp1=fopen(USERLIST,"w+");
    fwrite(temp,sizeof(REGISTERINFOR),getUserNum(),fp1);
    fclose(fp1);
}
/**********************
 * 注销
 * @param ID
 */
void logout(char* ID){
    moState(ID);
}