/*
 * @Author: your name
 * @Date: 2021-01-27 11:24:56
 * @LastEditTime: 2021-02-04 14:58:01
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /skywalker/home/yblin/workspace/test/socket/server.cc
 */
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
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8071);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }

    if (listen(listenfd, 10) == -1) {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }

    printf("======waiting for client's request======\n");
    if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1) {
        printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
    }
    while (1) {
        n = recv(connfd, buff, MAXLINE, 0);
        if (n <= 0) {
            usleep(100 * 1000);
            printf("sleep: 100ms\n");
        } else {
            buff[n] = '\0';
            printf("recv msg from client: %s len:%d\n", buff, strlen(buff));
            if (send(connfd, buff, strlen(buff), 0) < 0) {
                printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
                // return 0;
            }
        }
    }
    close(connfd);
    close(listenfd);
    return 0;
}