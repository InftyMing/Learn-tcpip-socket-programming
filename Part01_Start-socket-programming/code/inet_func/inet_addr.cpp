#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    char* addr1 = "1.2.3.4";
    // 一个字节能表示的最大整数是255，addr2是错误的ip地址，通过该地址能验证inet_addr函数的错误检测能力
    char* addr2 = "1.2.3.256";

    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE) {
        printf("Error occured! \n");
    } else {
        printf("Nework order integer addr: %#lx \n", conv_addr);
    }

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE) {
        printf("Error occured! \n");
    } else {
        printf("Nework order integer addr: %#lx \n\n", conv_addr);
    }

    return 0;
}