#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(char* message);

int main(int argc, char* argv[]) {
    char* addr = "127.232.124.79";
    struct sockaddr_in addr_inet;
    
    /*
        转换后IP地址信息需保存在sockaddr_in的in_addr型变量才有意义，
        因此，inet_aton函数的第二个参数要求得到in_addr型的变量地址值，这就省去了手动保存IP地址信息的过程
    */
    if (!inet_aton(addr, &addr_inet.sin_addr)) {
        error_handling("Conversion error");
    } 
    else {
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);
    }

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}