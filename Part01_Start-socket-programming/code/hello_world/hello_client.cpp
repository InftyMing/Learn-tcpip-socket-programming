/*
stdio.h
    C语言为输入输出提供的标准库头文件
stdlib.h 
    C标准函数库的头文件, 声明了数值与字符串转换函数, 伪随机数生成函数, 
    动态内存分配函数, 进程控制函数等公共函数
    C++程序应调用等价的cstdlib头文件
unistd.h
    C和C++程序设计语言中提供对POSIX操作系统API的访问功能的头文件的名称,是Unix Standard的缩写
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 创建准备连接服务器端的套接字，此时创建的是TCP套接字
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    // 结构体变量serv_addr中初始化IP和端口信息。初始化值为目标服务器端套接字的IP和端口信息
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 调用connect函数向服务器端发送连接请求
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error!");
    }

    // 完成连接后，接收服务器端传输的数据
    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1) {
        error_handling("read() error!");
    }

    printf("Message from server : %s \n", message);
    // 接收数据后调用close函数关闭套接字，结束与服务器端的连接
    close(sock);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}