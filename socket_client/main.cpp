/*
 * @Author: your name
 * @Date: 2021-01-27 11:25:20
 * @LastEditTime: 2021-02-01 15:40:07
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /skywalker/home/yblin/workspace/test/socket/client.cc
 */
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXLINE 4096

int main(int argc, char** argv) {
    int sockfd, n;
    char recvline[4096], sendline[4096];
    struct sockaddr_in servaddr;

    if (argc != 2) {
        printf("usage: ./client <ipaddress>\n");
        return 0;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8071);
    if (inet_aton(argv[1], &servaddr.sin_addr) <= 0) {
        printf("inet_pton error for %s\n", argv[1]);
        return 0;
    }

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }
    while (1) {
        printf("send msg to server: \n");
        fgets(sendline, 4096, stdin);
        if (send(sockfd, sendline, strlen(sendline), 0) < 0) {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            // return 0;
        }
        n = recv(sockfd, recvline, MAXLINE, 0);
        if (n <= 0) {
            usleep(100 * 1000);
            printf("sleep: 100ms\n");
        } else {
            recvline[n] = '\0';
            printf("recv msg from client: %s\n", recvline);
        }
    }

    close(sockfd);
    return 0;
}