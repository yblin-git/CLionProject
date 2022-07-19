extern "C"{

}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/socket.h>

#define CONTROLLEN CMSG_LEN(sizeof(int))

int send_fd(int fd, int fd_to_send) {
    struct iovec    iov[1];
    struct msghdr   msg;
    char        buf[1];
    struct cmsghdr  *cmptr = NULL;

    iov[0].iov_base = buf;
    iov[0].iov_len  = 1;
    msg.msg_iov = iov;
    msg.msg_iovlen  = 1;
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;

    cmptr = (cmsghdr  *)malloc(CONTROLLEN);
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type  = SCM_RIGHTS;
    cmptr->cmsg_len    = CONTROLLEN;
    msg.msg_control   = cmptr;
    msg.msg_controllen= CONTROLLEN;
    *(int*)CMSG_DATA(cmptr) = fd_to_send;
    buf[0] = 0;

    printf("[father]: fd_to_send %d\n", fd_to_send);
    if (sendmsg(fd, &msg, 0) != 1) {
        return -1;
    }
    return 0;
}

int recv_fd(int fd, int *fd_to_recv) {
    int         nr;
    char        buf[1];
    struct iovec    iov[1];
    struct msghdr   msg;
    struct cmsghdr  *cmptr = NULL;

    iov[0].iov_base = buf;
    iov[0].iov_len  = 1;
    msg.msg_iov = iov;
    msg.msg_iovlen  = 1;
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;

    cmptr =(cmsghdr  *) malloc(CONTROLLEN);
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;

    if(recvmsg(fd, &msg, 0) < 0) {
        printf("recvmsg error\n");
        return -1;
    }

    if(msg.msg_controllen < CONTROLLEN) {
        printf("recv_fd get invalid fd\n");
        return -1;
    }

    *fd_to_recv = *(int*)CMSG_DATA(cmptr);
    printf("[child]: fd_to_recv %d\n", *fd_to_recv);
    return 0;
}

int main() {
    int fd;
    pid_t   pid;
    int sockpair[2];
    int status;
    char    fname[256];

    status = socketpair(AF_UNIX, SOCK_DGRAM, 0, sockpair);
    if (status < 0) {
        printf("Call socketpair error, errno is %d\n", errno);
        return errno;
    }

    pid = fork();
    if (pid == 0) {
        close(sockpair[1]);

        status = recv_fd(sockpair[0], &fd);
        if (status != 0) {
            printf("[child]: recv error, errno is %d\n", status);
            return status;
        }
        printf("[child]:write fd %d\n", fd);
        status = write(fd, "123", sizeof("123") - 1);
        if (status < 0) {
            printf("[child]: write error, errno is %d\n", status);
            return -1;
        } else {
            printf("[child]: append logo successfully\n");
        }
        close(fd);

        exit(0);
    }

    printf("[father]: enter the filename:\n");
    scanf("%s", fname);

    fd = open(fname, O_RDWR | O_APPEND);
    if (fd < 0) {
        perror("[father]");
        return -1;
    }

    status = send_fd(sockpair[1], fd);
    if (status != 0) {
        perror("[father]");
        return -1;
    }
    close(fd);

    wait(NULL);
    return 0;
}
