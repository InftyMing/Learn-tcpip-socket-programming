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
    int str_len = 0;
    int idx = 0, read_len = 0;
    
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 创建 TCP 套接字，若前两个参数传递 PF_INET SOCK_STREAM，则第三个参数 IPPRPOTO_TCP 可省略
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error!");
    }

    // while 循环中反复调用 read 函数，每次读取 1 个字节。如果 read 返回 0，则循环条件为假，跳出循环
    while (read_len = read(sock, &message[idx++], 1)) {
        if (read_len == -1) {
            error_handling("read() error!");
        }
        // 执行该语句时，变量 read_len 的值始终为 1，因为 read 函数每次读取 1 个字节
        // 跳出循环后，str_len 中存有读取的总字节数
        str_len += read_len;
    }

    printf("Message from server : %s \n", message);
    printf("Function read call count: %d \n", str_len);
    close(sock);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}