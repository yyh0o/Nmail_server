#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

int new_server_sock(unsigned short port);
void *client_fun(void *arg);
struct sockaddr new_addr(unsigned int port, char* IP);



/*****************************************************************
 * 主函数,建立一个TCP并发服务器
 * @param argc 无
 * @param argv 无
 * @return 无
 */
int main(int argc, char *argv[])
{
    int sockfd = 0;				//用于储存服务端套接字
    int connfd = 0;             //用于暂存客户端套接字
    unsigned short port = 2333; // 监听端口
    sockfd = new_server_sock(port); //初始化服务端套接字
    printf("TCP Server Started at port %d!\n", port);
    pthread_t thread_id;



    while(1)
    {
        char cli_ip[INET_ADDRSTRLEN] = "";	   // 用于保存客户端IP地址
        struct sockaddr_in client_addr;		   // 用于保存客户端地址
        socklen_t cliaddr_len = sizeof(client_addr);   // 必须初始化!!!

        //获得一个已经建立的连接
        connfd = accept(sockfd, (struct sockaddr*)&client_addr, &cliaddr_len);
        if(connfd < 0)
        {
            perror("accept this time");
            continue;
        }

        // 打印客户端的 ip 和端口
        inet_ntop(AF_INET, &client_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
        printf("----------------------------------------------\n");
        printf("client ip=%s,port=%d\n", cli_ip,ntohs(client_addr.sin_port));

        if(connfd > 0)
        {
            //由于同一个进程内的所有线程共享内存和变量，因此在传递参数时需作特殊处理，值传递。
            pthread_create(&thread_id, NULL, (void *)client_fun, (void *)connfd);  //创建线程
            pthread_detach(thread_id); // 线程分离，结束时自动回收资源
        }
    }

    close(sockfd);

    return 0;
}

/***********************************************************************
 * 创建一个地址结构体
 * @param port 连接地址端口
 * @param IP 连接地址IP,若是服务端则传NULL
 * @return 返回一个struct sockaddr结构体
 */
struct sockaddr new_addr(unsigned int port, char* IP){
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (IP){
        inet_pton(AF_INET,IP,&addr.sin_addr);
    }
    else{
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    return *((struct sockaddr*)&addr);
}

/*************************************************************************
 * 创建一个服务器的sock
 * @param port 服务器端口
 * @return  返回一个绑定到端口的套接字
 */
int new_server_sock(unsigned short port){
    int sockfd;
    int err_log = 0;

    struct sockaddr addr = new_addr(port,NULL); //创建服务器地址结构体

//    struct sockaddr_in my_addr;	// 服务器地址结构体
//    bzero(&my_addr, sizeof(my_addr));	   // 初始化服务器地址
//    my_addr.sin_family = AF_INET;
//    my_addr.sin_port   = htons(port);
//    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);   // 创建TCP套接字
    if(sockfd < 0)
    {
        perror("socket error");
        exit(-1);
    }


    printf("Binding server to port %d\n", port);

    // 绑定
    err_log = bind(sockfd, &addr, sizeof(addr));
    if(err_log != 0)
    {
        perror("bind");
        close(sockfd);
        exit(-1);
    }

    // 监听，套接字变被动
    err_log = listen(sockfd, 10);
    if( err_log != 0)
    {
        perror("listen");
        close(sockfd);
        exit(-1);
    }

    printf("Waiting client...\n");
    return sockfd;
}


/************************************************************************
函数名称：	void *client_fun(void *arg)
函数功能：	线程函数,处理客户信息
函数参数：	已连接套接字
函数返回：	无
************************************************************************/
void *client_fun(void *arg)
{
    int recv_len = 0;
    char recv_buf[1024] = "";	// 接收缓冲区
    int connfd = (int)arg; // 传过来的已连接套接字

    // 接收数据
    while((recv_len = recv(connfd, recv_buf, sizeof(recv_buf), 0)) > 0)
    {
        printf("recv_buf: %s\n", recv_buf); // 打印数据
        send(connfd, recv_buf, recv_len, 0); // 给客户端回数据
    }

    printf("client closed!\n");
    close(connfd);	//关闭已连接套接字

    return 	NULL;
}
