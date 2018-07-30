#include "mySocket.h"
#include "client_fun.h"
#include "server.h"

int serverInit(){
    int sockfd = 0;				//用于储存服务端套接字

    unsigned short port = 23333; // 监听端口
    sockfd = new_server_sock(port); //初始化服务端套接字
    printf("TCP Server Started at port %d!\n", port);
    pthread_t thread_id;



    while(1)
    {
        int connfd = 0;             //用于暂存客户端套接字
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
            pthread_create(&thread_id, NULL, &client_fun, (void *)connfd);  //创建线程
            pthread_detach(thread_id); // 线程分离，结束时自动回收资源
        }
    }

    close(sockfd);

    return 0;
}

int serverRun(){
    serverInit();
}