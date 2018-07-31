
#include"Initialization.h"
/*********************************************
函数第一次运行时的初始化函数，负责建立用户注册列表文件
返回值：-2 创建目录失败
        0 成功
        -1 打开文件失败
 **************************************************/
int sysInitiallization() {
    int state = 0;

    state = mkdir("server", 0777);//建立服务器根目录
    if (state < 0)
        return -2;
    FILE *fp;
    fp = fopen(USERLIST, "w+");//建立用户注册星系文件
    if (fp==NULL)
        return -1;
    fclose(fp);
    int number=0;
    FILE *fp1;
    fp1 = fopen(USERNUMBER, "w+");//建立用户个数文件
    if (fp1==NULL)
        return -1;
    fwrite(&number,sizeof(int),1,fp1);
    fclose(fp1);
    state = mkdir("server/TemporaryStorage", 0777);
    if (state < 0)
        return -2;
    return 0;
}
/*********************************************
当一个新用户注册时的初始化函数，负责新建用户的邮箱，及其中的联系人文件，黑名单，与邮件加
返回值：-2 创建目录失败
        0 成功
        -1 打开文件失败
 **************************************************/
int selfInitiallization(char* userId,char*passWord){
    int state=0;
    char catlog[50];
    char temp1[50];
    char temp2[50];
    char temp3[50];
    char temp4[50];
    memset(catlog,0,50);
    memset(temp1,0,50);
    memset(temp2,0,50);
    memset(temp3,0,50);
    memset(temp4,0,50);
    strcpy(catlog,"server/");
    strcat(catlog,userId);
    strcpy(temp1,catlog);
    strcpy(temp2,catlog);
    strcpy(temp3,catlog);
    strcpy(temp4,catlog);
    state=mkdir(catlog,0777);
    if(state<0)
        return -2;
    strcat(temp1,"/contacts.txt");
    FILE *fp1;
    fp1 = fopen(temp1, "w+");
    if (fp1==NULL)
        return -1;
    fclose(fp1);
    strcat(temp2,"/selfInformation.txt");
    FILE *fp2;
    fp2 = fopen(temp2, "w+");
    if (fp2==NULL)
        return -1;
    fclose(fp2);
    strcat(temp3,"/blackList.txt");
    FILE *fp3;
    fp3 = fopen(temp3, "w+");
    if (fp3==NULL)
        return -1;
    fclose(fp3);
    strcat(temp4,"/mailBox");
    state=mkdir(temp4,0777);
    if(state<0)
        return -2;
    strcat(temp4,"/list.txt");
    FILE *fp4;
    fp4 = fopen(temp4, "w+");
    if (fp4==NULL)
        return -1;
    fclose(fp4);
    fwUser(userId,passWord);
    return 0;


}
/*********************************************
当一个新用户注册时,检查用户是否存在，若不存在，将其与密码存于用户注册性系表忠
返回值：-2 用户数量为副，usernum出错
        0 成功
        -1 打开文件失败
        -3用户已存在
 **************************************************/
int fwUser(char * userId,char* passWord){
    int userNum=getUserNum();
    if(userNum<0)
        return -2;
    FILE* fp;
    fp=fopen(USERLIST,"r");
    if(fp==NULL)
        return -1;
    REGISTERINFOR list[100];
    memset(list,0,100*sizeof(REGISTERINFOR));
    int i=0;
    if(userNum>0){
        fread(&list[0],sizeof(REGISTERINFOR),userNum,fp);
        for(i=0;i<=userNum-1;i++){
            if(strcmp(list[i].userId,userId)==0)
                return -3;
        }
    }
    fclose(fp);
    FILE* fp1;
    fp1=fopen(USERLIST,"w+");
    if(fp1==NULL)
        return -1;
    strcpy(list[i].userId,userId);
    strcpy(list[i].passWord,passWord);
    list[i].state=1;
    for(int k=0;k<=userNum;k++) {
        fwrite(&list[k], sizeof(REGISTERINFOR), 1, fp);
    }
    int state=setUserNum();
    if(state==-1)
        return -1;
    fclose(fp1);
    return 0;
}
/*********************************************
获得以注册用户个数
返回值：-1 打开文件失败
 **************************************************/
int getUserNum(){
    FILE* fp;
    fp=fopen(USERNUMBER,"r");
    if(fp==NULL)
        return -1;
    int number=0;
    fread(&number,sizeof(int),1,fp);
    fclose(fp);
    return number;
}
/*********************************************
当一个新用户注册时，数字加1
返回值：  0 成功
        -1 打开文件失败
 **************************************************/
int setUserNum(){
    FILE* fp;
    fp=fopen(USERNUMBER,"r");
    if(fp==NULL)
        return -1;
    int number=0;
    fread(&number,sizeof(int),1,fp);
    fclose(fp);
    number++;
    FILE* fp1;
    fp1=fopen(USERNUMBER,"w+");
    if(fp1==NULL)
        return -1;
    fwrite(&number,sizeof(int),1,fp1);
    fclose(fp1);
    return 0;
}
//int main(){
//    selfInitiallization("12234","frgrgrg");
//    printf("%d",getUserNum());
//
//}