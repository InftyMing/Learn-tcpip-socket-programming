#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // 服务器端实现过程中先要创建套接字。此套接字不是真正的服务器端套接字
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    // 未完成套接字地址分配，初始化结构体变量并调用bind函数
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    // 调用listen函数进入等待连接请求状态。连接请求队列长度设置为5，此时的套接字才是服务器端套接字
    if (listen(serv_sock, 5) == 1) {
        error_handling("listen() error");
    }

    // 调用accept函数从队头取1个连接请求与客户端建立连接，并返回创建的套接字文件描述符
    // 另外，调用accept函数时若等待队列为空，则accept函数不会返回，直到队列中出现新的客户端连接
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    }

    // 调用write函数向客户端传输数据，调用close函数关闭连接
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}