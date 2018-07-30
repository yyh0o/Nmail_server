//
// Created by yyh on 18-7-30.
//
#include "mySocket.h"

/***********************************************************************
 * 创建一个地址结构体
 * @param port 连接地址端口
 * @param IP 连接地址IP,若是服务端则传NULL
 * @return 返回一个struct sockaddr结构体
 */
struct sockaddr new_addr(unsigned short port, char *IP) {
    struct sockaddr_in addr;                        //新建一个sockaddr_in结构体
    bzero(&addr, sizeof(addr));                     //初始化
    addr.sin_family = AF_INET;                      //写入协议类型
    addr.sin_port = htons(port);                    //写入端口
    if (IP) {                                       //判断传入IP是否为NULL
        inet_pton(AF_INET, IP, &addr.sin_addr);     //IP不为空写入IP
    } else {
        addr.sin_addr.s_addr = htonl(INADDR_ANY);   //IP为空初始化为本机IP
    }

    return *((struct sockaddr *) &addr);            //返回sockaddr 结构体
}

/*************************************************************************
 * 创建一个服务器的sock
 * @param port 服务器端口
 * @return  返回一个绑定到端口的套接字
 */
int new_server_sock(unsigned short port) {
    int sockfd;
    int err_log = 0;
    struct sockaddr addr = new_addr(port, NULL); //创建并初始化服务器地址结构体
    sockfd = socket(AF_INET, SOCK_STREAM, 0);   // 创建TCP套接字
    if (sockfd < 0) {
        perror("socket error");
        exit(-1);
    }
    printf("Binding server to port %d\n", port);

    err_log = bind(sockfd, &addr, sizeof(addr));    //绑定端口
    if (err_log != 0) {
        perror("bind");
        close(sockfd);
        exit(-1);
    }

    err_log = listen(sockfd, 10);   //开始监听,套接字变被动
    if (err_log != 0) {
        perror("listen");
        close(sockfd);
        exit(-1);
    }
    printf("Waiting client...\n");

    return sockfd;                  //返回创建好的套接字
}

/**************************************************************
 * 创建一个连接到服务器的socket
 * @param ip 服务器ip
 * @param port 服务器端口
 * @return 返回以建立连接的套接字,失败则返回-1
 */
int new_connected_sock(const char* ip, unsigned short port) {
    int sockfd;     //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }
    struct sockaddr addr = new_addr(port,ip);   //初始化地址
    if (connect(sockfd, &addr, sizeof(addr)) == -1) {   //建立连接
        perror("connect");
        return -1;
    }
    return sockfd;  //返回以创建连接的套接字

}


/********************************************************************
 * 发送信息
 * @param sockfd 已建立连接的套接字
 * @param buf 发送数据缓冲区
 * @param len 发送数据长度
 * @param type 发送数据类型
 * @return 返回接收数据长度
 */
int mySendMsg(int sockfd, char *buf, int len, char type) {
    myMsgHead msgHead;                              //创建数据头
    msgHead.type = type;                            //初始化数据头
    msgHead.len = len;

    send(sockfd, &msgHead, sizeof(myMsgHead), 0);   //发送数据头
    return send(sockfd, buf, len, 0);               //发送数据返回数据发送数据长度
}

/***********************************************************
 * 接收信息
 * @param sockdf 已建立连接的套接字
 * @param buf 接收数据的缓冲区
 * @param type 用于储存接受文件的数据类型
 * @return 返回接收文件的大小
 */
int  myRecvMsg(int sockdf, char *buf, char* type) {
    myMsgHead head;                                         //创建一个数据头
    char* buffer = (char*)malloc(sizeof(myMsgHead)+1);      //创建一个缓冲区
    recv(sockdf, buffer, sizeof(myMsgHead), 0);             //接收一个数据头大小的数据
    memcpy(&head, buffer, sizeof(myMsgHead));               //将接收的数据写进数据头
    recv(sockdf,buf,head.len,0);                            //接受数据
    free(buffer);                                           //释放冲区内存
    buffer = NULL;
    *type = head.type;                                      //返回数据类型
    return head.len;                                        //返回接收消息长度
}


/***********************************************************************
 * 发送文件
 * @param sockdf 以建立连接的套接字
 * @param fileName 文件名
 * @param nameLen 文件名长度
 * @param fp 文件指针
 * @return 成功返回0 失败返回-1
 */
int mySendFile(int sockdf, const char* fileName,int nameLen, FILE* fp){
    char type;
    mySendMsg(sockdf, fileName, nameLen, MY_MSG_FILE);      //发送文件名
    char buffer[BUFFER_SIZE];                               //新建缓冲区
    bzero(buffer, sizeof(buffer));                          //初始化缓冲区
    myRecvMsg(sockdf, buffer, &type);                 //接受返回数据
    if (strcmp(buffer,"OK") == 0){                          //判断是否可发文件
        bzero(buffer, sizeof(buffer));
        int fileBlockLen = 0;                               //记录文件块长度
        while ((fileBlockLen = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0){ //读取一块文件到缓冲区
            if (mySendMsg(sockdf, buffer, fileBlockLen, MY_MSG_FILE) < 0){  //发送一块文件
                perror("文件发送失败");                       //发送失败
                return -1;
            }
            bzero(buffer, sizeof(buffer));
        }
    }
    else {
        perror("对方拒绝接收此文件");        //对方拒绝文件
        return -1;
    }
    return 0;
}


/************************************************************
 * 接收文件
 * @param sockdf 以建立连接的套接字
 * @param path 文件路径
 * @param pathlen 文件路径长度
 * @return 文件成功接收返回0,接收失败返回-1
 */
int myRecvFile(int sockdf, const char* path, int pathlen) {
    char fileName[FILE_NAME_MAX_SIZE];                      //记录文件名
    char type;                                              //记录数据类型
    bzero(fileName, sizeof(fileName));                      //初始化文件名数组
    int fileNameLen = myRecvMsg(sockdf, fileName, &type);   //接收文件名
    if (type != MY_MSG_FILE){                               //校验数据类型是否匹配
        perror("数据类型不匹配");
        return -1;
    }
    char* filePath = (char*)malloc(pathlen+fileNameLen+1);  //生成文件储存路径
    bzero(filePath,pathlen+fileNameLen+1);
    strcpy(filePath,path);
    strcat(filePath,fileName);
    FILE* fp;
    fp = fopen(filePath,"w+");                              //创建文件
    if (!fp){                                               //等待对方端口确认是否可以开始发送文件
        mySendMsg(sockdf, "NO", 3, MY_MSG_FILE);
        return -1;
    }
    else{
        mySendMsg(sockdf, "OK", 3,MY_MSG_FILE);
    }

    char buffer[BUFFER_SIZE];                               //创建文件读取缓冲区
    bzero(buffer,BUFFER_SIZE);
    int fileBlocklen;                                       //记录接收文件缓冲大小
    while ((fileBlocklen = myRecvMsg(sockdf, buffer, &type)) > 0){      //接收一块文件到缓冲区
        int writelen = fwrite(buffer, sizeof(char), fileBlocklen, fp);  //将缓冲区的数据写入文件
        if (writelen < fileBlocklen){                                   //判断是否将缓冲区数据全部写入
            perror("文件写入失败");
            return -1;
        }
        if (fileBlocklen < BUFFER_SIZE)                                 //判断文件传输是否结束
            break;
        bzero(buffer, BUFFER_SIZE);                         //清空缓冲区
    }
    fclose(fp);                                             //关闭文件
    return 0;
}