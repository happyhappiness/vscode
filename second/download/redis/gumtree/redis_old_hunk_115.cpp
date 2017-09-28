#include "net.h"
#include "sds.h"

/* Defined in hiredis.c */
void __redisSetError(redisContext *c, int type, const char *str);

static void __redisSetErrorFromErrno(redisContext *c, int type, const char *prefix) {
    char buf[128];
    size_t len = 0;

    if (prefix != NULL)
        len = snprintf(buf,sizeof(buf),"%s: ",prefix);
    strerror_r(errno,buf+len,sizeof(buf)-len);
    __redisSetError(c,type,buf);
}

static int redisSetReuseAddr(redisContext *c, int fd) {
    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        close(fd);
        return REDIS_ERR;
    }
    return REDIS_OK;
}

static int redisCreateSocket(redisContext *c, int type) {
    int s;
    if ((s = socket(type, SOCK_STREAM, 0)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        return REDIS_ERR;
    }
    if (type == AF_INET) {
        if (redisSetReuseAddr(c,s) == REDIS_ERR) {
            return REDIS_ERR;
        }
    }
    return s;
}

static int redisSetBlocking(redisContext *c, int fd, int blocking) {
    int flags;

    /* Set the socket nonblocking.
     * Note that fcntl(2) for F_GETFL and F_SETFL can't be
     * interrupted by a signal. */
    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"fcntl(F_GETFL)");
        close(fd);
        return REDIS_ERR;
    }

    if (blocking)
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;

    if (fcntl(fd, F_SETFL, flags) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"fcntl(F_SETFL)");
        close(fd);
        return REDIS_ERR;
    }
    return REDIS_OK;
}

static int redisSetTcpNoDelay(redisContext *c, int fd) {
    int yes = 1;
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(TCP_NODELAY)");
        close(fd);
        return REDIS_ERR;
    }
    return REDIS_OK;
}

#define __MAX_MSEC (((LONG_MAX) - 999) / 1000)

static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *timeout) {
    struct pollfd   wfd[1];
    long msec;

    msec          = -1;
    wfd[0].fd     = fd;
    wfd[0].events = POLLOUT;

    /* Only use timeout when not NULL. */
    if (timeout != NULL) {
        if (timeout->tv_usec > 1000000 || timeout->tv_sec > __MAX_MSEC) {
            close(fd);
            return REDIS_ERR;
        }

        msec = (timeout->tv_sec * 1000) + ((timeout->tv_usec + 999) / 1000);

        if (msec < 0 || msec > INT_MAX) {
